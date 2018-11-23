/*
  ==============================================================================

    Tilt.cpp
    Created: 9 Jul 2018 2:57:36pm
    Author:  Alex

  ==============================================================================
*/

#include "Tilt.h"
using namespace PLUME;

Tilt::Tilt (String gestName, int gestId, AudioProcessorValueTreeState& plumeParameters, float lowValue, float highValue)
    : Gesture (gestName, Gesture::tilt, gestId, NormalisableRange<float> (TILT_MIN, TILT_MAX, 0.1f),
		       *(plumeParameters.getParameter (String(gestId) + param::paramIds[param::value])),
		       *(plumeParameters.getParameter (String(gestId) + param::paramIds[param::on])),
		       *(plumeParameters.getParameter (String(gestId) + param::paramIds[param::midi_on])),
		       *(plumeParameters.getParameter (String(gestId) + param::paramIds[param::midi_cc])),
		       *(plumeParameters.getParameter (String(gestId) + param::paramIds[param::midi_low])),
		       *(plumeParameters.getParameter (String(gestId) + param::paramIds[param::midi_high]))),
    
      rangeLow  (*(plumeParameters.getParameter (String (gestId) + param::paramIds[param::tilt_low]))),
      rangeHigh (*(plumeParameters.getParameter (String (gestId) + param::paramIds[param::tilt_high])))
{
    rangeLow.beginChangeGesture();
	rangeLow.setValueNotifyingHost (rangeLow.convertTo0to1 (lowValue));
    rangeLow.endChangeGesture();
    
    rangeHigh.beginChangeGesture();
	rangeHigh.setValueNotifyingHost (rangeHigh.convertTo0to1 (highValue));
    rangeHigh.endChangeGesture();
}

Tilt::~Tilt()
{
}
    
//==============================================================================
void Tilt::addGestureMidi (MidiBuffer& midiMessages, MidiBuffer& plumeBuffer)
{
    // Checks if Gesture is on and if value is within the right range
    if (on.getValue() == 0.0f || value >= 120.0f || value <= -120.0f)
    {
        return;
    }
    
    if (isMidiMapped())
    {
        addMidiModeSignalToBuffer (midiMessages, plumeBuffer, getMidiValue(), 0, 127, 1);
    }
    else
    {
        addEventAndMergeCCToBuffer (midiMessages, plumeBuffer, getMidiValue(), 1, 1);
    }
}

int Tilt::getMidiValue()
{
    return Gesture::normalizeMidi (rangeLow.convertFrom0to1 (rangeLow.getValue()), rangeHigh.convertFrom0to1 (rangeHigh.getValue()), value);
}

void Tilt::updateMappedParameters()
{
    // Checks if Gesture is on and if value is within the right range
    if (on.getValue() == 0.0f || value >= 120.0f || value <= -120.0f)
    {
        return;
    }
    
    // Goes through the parameterArray to update each value
    for (auto* param : parameterArray)
    {   
        param->parameter.setValueNotifyingHost (getValueForMappedParameter (param->range, param->reversed));
    }
}

float Tilt::getValueForMappedParameter (Range<float> paramRange, bool reversed = false)
{
	return Gesture::mapParameter (value, rangeLow.convertFrom0to1 (rangeLow.getValue()), rangeHigh.convertFrom0to1 (rangeHigh.getValue()), paramRange, reversed);
}
    
//==============================================================================
void Tilt::updateValue (const Array<float> rawData)
{
    value = rawData[4];
}