/*
  ==============================================================================

    GestureSettingsComponent.cpp
    Created: 28 Mar 2019 2:09:04pm
    Author:  Alex

  ==============================================================================
*/

#include "Ui/Gesture/Tuner/GesturesTuner.h"
#include "Ui/Gesture/SettingsTabs/MapperComponent.h"
#include "GestureSettingsComponent.h"

//==============================================================================
GestureSettingsComponent::GestureSettingsComponent (Gesture& gest, GestureArray& gestArray,
                                                    PluginWrapper& wrap, PlumeShapeButton& closeBttn)
                            : gesture (gest), gestureArray (gestArray),
                              wrapper (wrap), closeButton (closeBttn), gestureId (gest.id)
{
    TRACE_IN;
    setComponentID ("Gesture Settings");

    createTuner();
    createPanels();
    createToggles();
}

GestureSettingsComponent::~GestureSettingsComponent()
{
    TRACE_IN;
    gestureArray.cancelMapMode();
    disabled = true;
    gestTuner = nullptr;
    midiParameterToggle = nullptr;
    descriptionPanel = nullptr;
}

//==============================================================================
const String GestureSettingsComponent::getInfoString()
{
    return "Gesture settings:\n\n"
           "- Use this panel to configure the selected gesture.";
}

void GestureSettingsComponent::update()
{
    if (disabled) return;

	retractablePanel->update();
    descriptionPanel->update();
    gestTuner->setColour (gesture.getHighlightColour());
    gestTuner->updateComponents();
    muteButton->setToggleState (gesture.isActive(), dontSendNotification);
    midiParameterToggle->setToggleState (gesture.generatesMidi());
}


void GestureSettingsComponent::update (const String& parameterThatChanged)
{
    if (disabled) return;

    if (parameterThatChanged.startsWith ("_midi"))
    {
        if (parameterThatChanged.endsWith ("n"))
        {
            midiParameterToggle->setToggleState (gesture.generatesMidi());
            retractablePanel->update();
        }
        else if (parameterThatChanged.endsWith ("w"))
        {
            retractablePanel->updateMidiRange (MidiRangeTuner::lowThumb);
        }
        else if (parameterThatChanged.endsWith ("h"))
        {
            retractablePanel->updateMidiRange (MidiRangeTuner::highThumb);
        }
    }
    else if (parameterThatChanged.compare ("_on") == 0)
    {
        update();
    }
    else
    {
        if (auto* oneRangeTuner = dynamic_cast<OneRangeTuner*> (gestTuner.get()))
        {
            if (parameterThatChanged.endsWith ("_low"))
            {
                oneRangeTuner->updateComponents (OneRangeTuner::lowThumb);
            }
            else if (parameterThatChanged.endsWith ("_high"))
            {
                oneRangeTuner->updateComponents (OneRangeTuner::highThumb);
            }
        }

        else if (auto* twoRangeTuner = dynamic_cast<TwoRangeTuner*> (gestTuner.get()))
        {
            if (parameterThatChanged.endsWith ("_leftLow"))
            {
                twoRangeTuner->updateComponents (TwoRangeTuner::leftLowThumb);
            }
            else if (parameterThatChanged.endsWith ("_leftHigh"))
            {
                twoRangeTuner->updateComponents (TwoRangeTuner::leftHighThumb);
            }
            else if (parameterThatChanged.endsWith ("_rightLow"))
            {
                twoRangeTuner->updateComponents (TwoRangeTuner::rightLowThumb);
            }
            else if (parameterThatChanged.endsWith ("_rightHigh"))
            {
                twoRangeTuner->updateComponents (TwoRangeTuner::rightHighThumb);
            }
        }
        else
        {
            gestTuner->updateComponents();
        }
    }
}

//==============================================================================
void GestureSettingsComponent::paint (Graphics& g)
{
    using namespace PLUME::UI;

    // Enhancia Text

    // Background
    paintBackground (g);

    // HeaderText
    auto headerArea = getLocalBounds().removeFromTop (this->HEADER_HEIGHT);

    //Advanced Settings text
    g.setColour (getPlumeColour (detailPanelSubText));
    g.setFont (PLUME::font::plumeFont.withHeight (10.0f));
    g.drawText ("ADVANCED PANEL",
                headerArea.removeFromLeft (getWidth()/3).reduced (MARGIN, MARGIN_SMALL),
                Justification::bottomLeft, false);

    // Gesture Name text
    g.setColour (getPlumeColour (detailPanelMainText));                    
    g.setFont (PLUME::font::plumeFontBold.withHeight (15.0f));
    g.drawText (gesture.getName().toUpperCase(),
                headerArea.removeFromLeft (getWidth()/3).reduced (MARGIN, 0),
                Justification::centred, false);
}

void GestureSettingsComponent::paintBackground (Graphics& g)
{
    using namespace PLUME::UI;
    auto area = getLocalBounds().withBottom (retractablePanel->getBottom());

    // MidiMap Background
    g.setColour (getPlumeColour (midiMapBodyBackground));
    g.fillRoundedRectangle (area.withTop (retractablePanel->getY()).toFloat(), 10.0f);

    // Tuner backGround
    g.setColour (getPlumeColour (tunerBackground));
    g.fillRoundedRectangle (area.withBottom (retractablePanel->getY() + retractablePanel->bannerHeight)
                                .toFloat(),
                            10.0f);

    Path tile;
    tile.addEllipse (0, 0, 2, 2);

    PLUME::UI::paintTiledPath (g, tile,
                               area.withBottom (retractablePanel->getY() + retractablePanel->bannerHeight)
                                   .toFloat(),
                               15.0f, 15.0f, getPlumeColour (midiMapBodyBackground), Colour (0), 0.0f);

    g.saveState();

    //Header Fill
    g.reduceClipRegion (0, 0, getWidth(), 30);
    g.setColour (getPlumeColour (detailPanelHeaderFill));
    g.fillRoundedRectangle (area.withBottom (retractablePanel->getY() + retractablePanel->bannerHeight)
                                .toFloat(),
                            10.0f);

    g.restoreState();
    g.saveState();

    //MidiMap banner fill
    g.reduceClipRegion (0, retractablePanel->getY(), getWidth(), retractablePanel->bannerHeight);
    g.setColour (getPlumeColour (midiMapBannerBackground));
    g.fillRoundedRectangle (area.withBottom (retractablePanel->getY() + retractablePanel->bannerHeight)
                                .toFloat(),
                            10.0f);

    g.restoreState();
}

void GestureSettingsComponent::resized()
{
    using namespace PLUME::UI;

    auto area = getLocalBounds();
    auto headerArea = area.removeFromTop (HEADER_HEIGHT).reduced (MARGIN_SMALL);

    closeButton.setBounds (getBoundsInParent().removeFromTop (HEADER_HEIGHT)
                                              .reduced (MARGIN_SMALL)
                                              .removeFromRight (25)
                                              .withSizeKeepingCentre (18, 18));
    headerArea.removeFromRight (25);

    muteButton->setBounds (headerArea.removeFromRight (30).withSizeKeepingCentre (18, 18));

    retractablePanel->setBounds (area.removeFromBottom (getHeight()/2 - HEADER_HEIGHT));
    area.removeFromBottom (MARGIN);
    gestTuner->setBounds (area);

    if (gesture.type != Gesture::pitchBend && gesture.type != Gesture::vibrato)
    {
        midiParameterToggle->setBounds (retractablePanel->getBounds()
                                            .withHeight (retractablePanel->bannerHeight)
                                            .withLeft (getWidth() - 50)
                                            .reduced (3*MARGIN_SMALL, MARGIN));
    }
}

//==============================================================================
void GestureSettingsComponent::buttonClicked (Button*)
{
}
    

//==============================================================================
const int GestureSettingsComponent::getGestureId()
{
    return gesture.id;
}

Tuner& GestureSettingsComponent::getTuner()
{
    return *gestTuner;
}

void GestureSettingsComponent::updateDisplay()
{
    if (!disabled) disableIfGestureWasDeleted();

    if (!disabled)
    {
        if (gesture.isActive()) gestTuner->updateDisplay();
        
        retractablePanel->updateDisplay();
    }
}

void GestureSettingsComponent::updateMappedParameters()
{
    retractablePanel->initializeParamCompArray();
}

void GestureSettingsComponent::disableIfGestureWasDeleted()
{
    if (gestureArray.getGesture (gestureId) == nullptr)
    {
        disabled = true;
    }
}

void GestureSettingsComponent::createTuner()
{
	if (gesture.type == Gesture::vibrato)
    {
        Vibrato& vib = dynamic_cast<Vibrato&> (gesture);
        addAndMakeVisible (gestTuner = new VibratoTuner (vib));
    }
    
    else if (gesture.type == Gesture::pitchBend)
    {
        PitchBend& pitchBend = dynamic_cast<PitchBend&> (gesture);
        addAndMakeVisible (gestTuner = new PitchBendTuner (pitchBend));
    }
    
    else if (gesture.type == Gesture::tilt)
    {
        Tilt& tilt = dynamic_cast<Tilt&> (gesture);
        addAndMakeVisible (gestTuner = new TiltTuner (tilt));
    }
    /*  Un-comment when the wave gesture is implemented
    else if (gesture.type == Gesture::wave)
    {
        Wave& wave = dynamic_cast<Wave&> (gesture);
        addAndMakeVisible (gestTuner = new WaveTuner (wave));
    }
    */
    else if (gesture.type == Gesture::roll)
    {
        Roll& roll = dynamic_cast<Roll&> (gesture);
        addAndMakeVisible (gestTuner = new RollTuner (roll));
    }
    else
    {
        DBG ("Unknown Gesture type. No tuner was created.");
    }

    gestTuner->setColour (gesture.getHighlightColour());
}

void GestureSettingsComponent::createToggles()
{
    addAndMakeVisible (midiParameterToggle = new DualTextToggle ("MIDI", "MIDI",
                                                                 getPlumeColour (plumeBackground),
                                                                 gesture.getHighlightColour()));
    midiParameterToggle->setStyle (DualTextToggle::toggleWithTopText);
    midiParameterToggle->setToggleState (gesture.generatesMidi());
    midiParameterToggle->setStateUndependentTextColour (getPlumeColour (detailPanelMainText));
    midiParameterToggle->setToggleThumbColour (getPlumeColour (tunerSliderBackground));
    midiParameterToggle->onStateChange = [this] ()
    {
        gesture.setGeneratesMidi (midiParameterToggle->getToggleState());
        showAppropriatePanel();
        getParentComponent()->repaint();
    };

    addAndMakeVisible (muteButton = new PlumeShapeButton ("Mute Button",
                                                          getPlumeColour (plumeBackground),
                                                          getPlumeColour (mutedHighlight),
                                                          Gesture::getHighlightColour (gesture.type)));

    muteButton->setShape (PLUME::path::createPath (PLUME::path::onOff), false, true, false);
    muteButton->setToggleState (gesture.isActive(), dontSendNotification);
    muteButton->setClickingTogglesState (true);
    muteButton->onClick = [this] ()
    {
        gesture.setActive (muteButton->getToggleState());
        closeButton.setToggleState (gesture.isActive(), dontSendNotification);
    };

    closeButton.setStrokeOffAndOnColours (getPlumeColour (mutedHighlight),
                                          Gesture::getHighlightColour(gesture.type));
    closeButton.setToggleState (gesture.isActive(), dontSendNotification);
}

void GestureSettingsComponent::createPanels()
{
    addAndMakeVisible (descriptionPanel = new DescriptionPanel (gesture));
    addAndMakeVisible (retractablePanel = new RetractableMapAndMidiPanel (gesture, gestureArray,
																		  wrapper, gestTuner->getColour()));
	showAppropriatePanel();
}

void GestureSettingsComponent::showAppropriatePanel()
{
    retractablePanel->setPanelMode (gesture.generatesMidi() ? RetractableMapAndMidiPanel::midiMode
                                                            : RetractableMapAndMidiPanel::parameterMode);
}