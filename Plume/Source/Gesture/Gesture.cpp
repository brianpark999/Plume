/*
==============================================================================

Gesture.cpp
Created: 10 Apr 2019 3:06:34pm
Author:  Alex

==============================================================================
*/

#include "Gesture.h"

Gesture::Gesture (String gestName, int gestType, int gestId, const NormalisableRange<float> maxRange,
         		  AudioProcessorValueTreeState& plumeParameters, String gestureDescription,
         		  float defaultValue, int defaultCc, Range<float> defaultMidiRange)
        
         		  : name (gestName), type (gestType), id (gestId), range (maxRange), description (gestureDescription),
	       		  value    (*(plumeParameters.getParameter (String(gestId) + PLUME::param::paramIds[PLUME::param::value]))),
	       		  on       (*(plumeParameters.getParameter (String(gestId) + PLUME::param::paramIds[PLUME::param::on]))),
	       		  midiOnParameterOff  (*(plumeParameters.getParameter (String(gestId) + PLUME::param::paramIds[PLUME::param::midi_on]))),
 	       		  cc       (*(plumeParameters.getParameter (String(gestId) + PLUME::param::paramIds[PLUME::param::midi_cc]))),
 	       		  midiLow  (*(plumeParameters.getParameter (String(gestId) + PLUME::param::paramIds[PLUME::param::midi_low]))),
	       		  midiHigh (*(plumeParameters.getParameter (String(gestId) + PLUME::param::paramIds[PLUME::param::midi_high]))),
	       		  valueRef (plumeParameters.getRawParameterValue (String(gestId) + PLUME::param::paramIds[PLUME::param::value]))
{
    TRACE_IN;
    mapped = false;
    setGestureValue (defaultValue);
    setMidiLow (defaultMidiRange.getStart(), false);
    setMidiHigh (defaultMidiRange.getEnd(), false);
    setGeneratesMidi (false);
	setCc (defaultCc);
}

Gesture::~Gesture()
{
    removeAllChangeListeners();
    clearAllParameters();
}


//==============================================================================
// Static Methods to merge messages in a MidiBuffer

void Gesture::addEventAndMergePitchToBuffer (MidiBuffer& midiMessages, MidiBuffer& plumeBuffer,
										   	 int midiValue, int channel)
{
    MidiBuffer newBuff;
    int time;
    MidiMessage m;
    
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        if (m.isPitchWheel()) // checks for pitch wheel events
        {   
            int newVal = m.getPitchWheelValue() - 8192 + midiValue;
            if (newVal < 0) newVal = 0;
            else if (newVal > 16383) newVal = 16383;
            
            m = MidiMessage::pitchWheel (m.getChannel(), newVal);
        }
        
        newBuff.addEvent (m, time);
    }
    
    // Adds gesture's initial midi message
    newBuff.addEvent (MidiMessage::pitchWheel (channel, midiValue), 1);
    plumeBuffer.addEvent (MidiMessage::pitchWheel (channel, midiValue), 1);
    
    midiMessages.swapWith (newBuff);
}

void Gesture::addEventAndMergeCCToBuffer (MidiBuffer& midiMessages, MidiBuffer& plumeBuffer,
												 int midiValue, int ccValue, int channel)
{
    MidiBuffer newBuff;
    int time;
    MidiMessage m;
    
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        if (m.isAftertouch()) // checks if right event
        {
            // Creates a cc message with the new value
            int newVal = m.getControllerValue() + midiValue;
            if (newVal > 127) newVal = 127;
            
            m = MidiMessage::controllerEvent (m.getChannel(), ccValue, newVal);
        }
        
        newBuff.addEvent (m, time);
    }
    
    // Adds gesture's initial cc message
    newBuff.addEvent (MidiMessage::controllerEvent (channel, ccValue, midiValue), 1);
    plumeBuffer.addEvent (MidiMessage::controllerEvent (channel, ccValue, midiValue), 1);
    
    midiMessages.swapWith (newBuff);
}

void Gesture::addEventAndMergeAfterTouchToBuffer (MidiBuffer& midiMessages, MidiBuffer& plumeBuffer,
										                 int midiValue, int channel)
{
    MidiBuffer newBuff;
    int time;
    MidiMessage m;
    
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    { 
        // AfterTouchMessage
        if (m.isAftertouch())
        {
            // Creates a cc message with the new value
            int newVal = m.getAfterTouchValue() + midiValue;
            if (newVal > 127) newVal = 127;
            
            m = MidiMessage::aftertouchChange (m.getChannel(), m.getNoteNumber(), newVal);
        }
        
        // Channel pressure message (ie AT for all every note)
        if (m.isChannelPressure())
        {
            // Creates a cc message with the new value
            int newVal = m.getChannelPressureValue()  + midiValue;
            if (newVal > 127) newVal = 127;
            
            m = MidiMessage::channelPressureChange (m.getChannel(), newVal);
        }
        
        newBuff.addEvent (m, time);
    }
    
    // Adds gesture's initial cc message
    newBuff.addEvent (MidiMessage::channelPressureChange (channel, midiValue), 1);
    plumeBuffer.addEvent (MidiMessage::channelPressureChange (channel, midiValue), 1);
    
    midiMessages.swapWith (newBuff);
}

//==============================================================================
// Getter to the midiValue taking the midi mode range into account

int Gesture::getRescaledMidiValue()
{
    if (midiType == Gesture::pitch)
    {
        return mapInt (getMidiValue(), 0, 16383, map (midiLow.getValue(), 0.0f, 1.0f, 0, 16383),
                                      map (midiHigh.getValue(),   0.0f, 1.0f, 0, 16383));
    }
       
    else
    {
        return mapInt (getMidiValue(), 0, 127, map (midiLow.getValue(), 0.0f, 1.0f, 0, 127),
                                      map (midiHigh.getValue(),   0.0f, 1.0f, 0, 127));
    }                          
}

//==============================================================================
// Getters and setters to the value and range of the gesture. Used by the display among others.

void Gesture::setGestureValue (float newVal)
{
	if (isActive()) value.setValueNotifyingHost (range.convertTo0to1 (newVal));
}

float Gesture::getGestureValue() const
{
	return range.convertFrom0to1 (value.getValue());
}

float& Gesture::getValueReference()
{
	return *valueRef;
}

NormalisableRange<float> Gesture::getRangeReference()
{
    return range.getRange();
}

//==============================================================================
// Getters and setters for various parameters

void Gesture::setActive (bool shouldBeOn)
{
    on.beginChangeGesture();
    on.setValueNotifyingHost (shouldBeOn ? 1.0f : 0.0f);
    on.endChangeGesture();
}

void Gesture::setMapped (bool shouldBeMapped)
{
    mapped = shouldBeMapped;
}

void Gesture::setGeneratesMidi (bool shouldGenerateMidi)
{
    if (type != Gesture::pitchBend && type != Gesture::vibrato)
    {
        midiOnParameterOff.beginChangeGesture();
    	midiOnParameterOff.setValueNotifyingHost (shouldGenerateMidi ? 1.0f : 0.0f);
    	midiOnParameterOff.endChangeGesture();
    }
}

void Gesture::setCc (int ccValue)
{
    cc.beginChangeGesture();
    cc.setValueNotifyingHost (cc.convertTo0to1 (float (ccValue)));
    cc.endChangeGesture();
}

int Gesture::getCc() const
{
    return int (cc.convertFrom0to1 (cc.getValue()));
}

bool Gesture::isMapped() const
{
    return mapped;
}

bool Gesture::generatesMidi() const
{
    return (midiOnParameterOff.getValue() < 0.5f ? false : true);
}

void Gesture::setMidiLow (float newValue, bool checkOtherValue)
{
    if (newValue > midiHigh.getValue() && checkOtherValue) newValue = midiHigh.getValue();
    else if (newValue < 0.0f) newValue = 0.0f; 
    
    midiLow.beginChangeGesture();
    midiLow.setValueNotifyingHost (newValue);
    midiLow.endChangeGesture();
}

void Gesture::setMidiHigh (float newValue, bool checkOtherValue)
{
    if (newValue < midiLow.getValue() && checkOtherValue)  newValue = midiLow.getValue();
    else if (newValue > 1.0f) newValue = 1.0f; 
    
    midiHigh.beginChangeGesture();
    midiHigh.setValueNotifyingHost (newValue);
    midiHigh.endChangeGesture();
}

bool Gesture::isActive() const
{
    return (on.getValue() < 0.5f ? false : true);
}

String Gesture::getName() const
{
    return name;
}

void Gesture::setName (String nameToSet)
{
    if (!nameToSet.trimEnd().isEmpty())
    {
        name = nameToSet.trimEnd();
    }
}

String Gesture::getDescription() const
{
    return description;
}

void Gesture::setDescription (String descrptionToSet)
{
    description = descrptionToSet;
}

String Gesture::getTypeString (bool capitalized) const
{
    return Gesture::getTypeString (type, capitalized);
}

String Gesture::getTypeString (int gestureType, bool capitalized)
{
    switch (gestureType)
    {
        case (int) Gesture::vibrato:
            return capitalized ? "Vibrato" : "vibrato";
            break;
            
        case (int) Gesture::pitchBend:
            return capitalized ? "Pitch Bend" : "pitchBend";
            break;
            
        case (int) Gesture::tilt:
            return capitalized ? "Tilt" : "tilt";
            break;
            
        case (int) Gesture::wave:
            return capitalized ? "Wave" : "wave";
            break;
            
        case (int) Gesture::roll:
            return capitalized ? "Roll" : "roll";
            break;
        
        default:
            return "unknown";
    }
}

String Gesture::getGestureTypeDescription() const
{
    return Gesture::getGestureTypeDescription (type);
}

String Gesture::getGestureTypeDescription (int gestureType)
{
    switch (gestureType)
    {
        case (int) Gesture::vibrato:
            return "Quickly move your finger back and forth "
                   "to change the pitch in a sine shape.\n";
            break;
            
        case (int) Gesture::pitchBend:
            return "Lean your hand to either side "
                   "to change the pitch of your note\n";
            break;
            
        case (int) Gesture::tilt:
            return "Tilt your hand upwards or downwards to modulate your sound.\n";
            break;
            
        case (int) Gesture::wave:
            return "TBD.\n";
            break;
            
        case (int) Gesture::roll:
            return "Rotate your hand sideways to modulate your sound.\n";
            break;
        
        default:
            return "-";
    }
}

Colour Gesture::getHighlightColour() const
{
    return getHighlightColour (type);
}

Colour Gesture::getHighlightColour (int gestureType)
{
    switch (gestureType)
    {
        case (int) Gesture::tilt:
            return getPlumeColour (tiltHighlight);
        case (int) Gesture::roll:
            return getPlumeColour (rollHighlight);
        case (int) Gesture::wave:
            return getPlumeColour (waveHighlight);
        case (int) Gesture::vibrato:
            return getPlumeColour (vibratoHighlight);
        case (int) Gesture::pitchBend:
            return getPlumeColour (pitchBendHighlight);
        default:
            return Colour (0xffffffff);
    }
}

bool Gesture::affectsPitch()
{
    // vibrato/pitchBend or any gesture with a pitch midi mode return true
    if (type == Gesture::vibrato || type == Gesture::pitchBend ||
        (generatesMidi() && midiType == Gesture::pitch))
    {
        return true;
    }
    
    return false;
}

//==============================================================================
// Parameter related methods

void Gesture::addParameter (AudioProcessorParameter& param, Range<float> r, bool rev)
{
    TRACE_IN;
    ScopedLock paramlock (parameterArrayLock);
    
    if (parameterArray.size() < PLUME::MAX_PARAMETER)
    {
        parameterArray.add ( new MappedParameter (param, r, rev));
        mapped = true;
    }
    
    sendChangeMessage(); // Alerts the gesture's mapperComponent to update it's Ui
}

void Gesture::deleteParameter (int paramId)
{
    TRACE_IN;
    ScopedLock paramlock (parameterArrayLock);
    
    parameterArray.remove (paramId);
    
    if (parameterArray.isEmpty()) mapped = false;
    
    sendChangeMessage(); // Alerts the gesture's mapperComponent to update it's Ui
}

void Gesture::replaceParameter (int paramId,
                                AudioProcessorParameter& param,
                                Range<float> r, bool rev)
{
    TRACE_IN;
    ScopedLock paramlock (parameterArrayLock);
    
    parameterArray.set (paramId, new MappedParameter (param, r, rev));
    
    sendChangeMessage(); // Alerts the gesture's mapperComponent to update it's Ui
}

void Gesture::clearAllParameters()
{
    TRACE_IN;
    ScopedLock paramlock (parameterArrayLock);
    
	mapped = false;
    parameterArray.clear();
    sendChangeMessage(); // Alerts the gesture's mapperComponent to update it's Ui
}

int Gesture::getNumParameters() const
{
    return parameterArray.size();
}

/**
 *  \brief Gets a reference to the parameter array.
 */
OwnedArray<Gesture::MappedParameter>& Gesture::getParameterArray()
{
    return parameterArray;
}

bool Gesture::parameterIsMapped (int parameterId)
{
    ScopedLock paramlock (parameterArrayLock);
    
    for (auto* param : parameterArray)
    {
        if (param->parameter.getParameterIndex() == parameterId) return true;
    }
    
    return false;
}

void Gesture::swapParametersWithOtherGesture (Gesture& other)
{
    clearAllParameters();

    for (auto* otherMappedParam : other.getParameterArray())
    {
        addParameter (otherMappedParam->parameter, otherMappedParam->range, otherMappedParam->reversed);
    }

    /*
    parameterArray.swapWith (other.getParameterArray());

    mapped = parameterArray.isEmpty();
    */

    sendChangeMessage(); // Alerts the gesture's mapperComponent to update it's Ui
}

int Gesture::normalizeMidi (float val, float minVal, float maxVal, bool is14BitMidi)
{
    if (minVal == maxVal && val == minVal) return 0;
    
    return Gesture::map (val, minVal, maxVal, 0, is14BitMidi ? 16383 : 127);
}

int Gesture::map (float val, float minVal, float maxVal, int minNew, int maxNew)
{
    if (minVal == maxVal && val == minVal) return minNew;

    if (val < minVal) return minNew;
    if (val > maxVal) return maxNew;

    return (minNew + int ((maxNew - minNew)*(val - minVal)/(maxVal-minVal)));
}

int Gesture::mapInt (int val, int minVal, int maxVal, int minNew, int maxNew)
{
    if (minVal == maxVal && val == minVal) return minNew;
    else if (minVal == minNew && maxVal == maxNew) return val;

    if (val < minVal) return minNew;
    if (val > maxVal) return maxNew;

    return (minNew + (maxNew - minNew)*(val - minVal)/(maxVal-minVal));
}

float Gesture::mapParameter (float val, float minVal, float maxVal, Range<float> paramRange, bool reversed)
{   
    // Prevents dividing by 0
    if (minVal == maxVal && val == minVal) return paramRange.getStart();
    
    // Forces the interval to [0.0f 1.0f]
    if (paramRange.getStart() < 0.0f) paramRange.setStart (0.0f);
    if (paramRange.getEnd() > 1.0f)   paramRange.setEnd (1.0f);
    
    // Checks out of bounds values
    if (val < minVal) return reversed ? paramRange.getEnd() : paramRange.getStart();
    if (val > maxVal) return reversed ? paramRange.getStart() : paramRange.getEnd();
    
    // normal case
    if (!reversed) return (paramRange.getStart() + paramRange.getLength()*(val - minVal)/(maxVal - minVal));
    // reversed parameter
    else           return (paramRange.getStart() + paramRange.getLength()*(maxVal - val)/(maxVal - minVal));
}

void Gesture::addRightMidiSignalToBuffer (MidiBuffer& midiMessages, MidiBuffer& plumeBuffer, int channel)
{
	if (!generatesMidi()) return; //Does nothing if not in default midi mode

    int newMidi;
    int val = getMidiValue();
    
    if (val != lastMidi) // Prevents to send the same message twice in a row
    {
        // Assigns the right midi value depending on the signal and
        // the midiRange parameter, then adds message to the buffers
        switch (midiType)
        {
    		case (Gesture::pitch):
                newMidi = mapInt (val, 0, 16383,
                                  map (midiLow.getValue(), 0.0f, 1.0f, 0, 16383),
                                  map (midiHigh.getValue(),   0.0f, 1.0f, 0, 16383));
                                  
                addEventAndMergePitchToBuffer (midiMessages, plumeBuffer, newMidi, channel);
                break;
            
    		case (Gesture::controlChange):
                newMidi = mapInt (val, 0, 127,
                                  map (midiLow.getValue(), 0.0f, 1.0f, 0, 127),
                                  map (midiHigh.getValue(),   0.0f, 1.0f, 0, 127));
                                  
                addEventAndMergeCCToBuffer (midiMessages, plumeBuffer, newMidi, getCc(), channel);
                break;
            
    		case (Gesture::afterTouch):
                newMidi = mapInt (val, 0, 127,
                                  map (midiLow.getValue(), 0.0f, 1.0f, 0, 127),
                                  map (midiHigh.getValue(),   0.0f, 1.0f, 0, 127));
                                  
                addEventAndMergeAfterTouchToBuffer (midiMessages, plumeBuffer, newMidi, channel);
                break;
            
            default:
                break;
        }

        lastMidi = val;
    }
}