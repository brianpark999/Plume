/*
  ==============================================================================

    HeaderComponent.cpp
    Created: 12 Dec 2018 4:53:18pm
    Author:  Alex

  ==============================================================================
*/

#include "HeaderComponent.h"

//==============================================================================
HeaderComponent::HeaderComponent (PlumeProcessor& proc, Component& newPrst)  : processor (proc),
                                                                               newPresetPanel (newPrst)
{
    setName ("Header");
    setComponentID ("header");
    
    // Plugin Name
    pluginNameLabel.reset (new Label ("Plugin Name Label", processor.getWrapper().getWrappedPluginName()));
    addAndMakeVisible (*pluginNameLabel);
    pluginNameLabel->setFont (PLUME::font::plumeFont.withHeight (PLUME::font::HEADER_LABEL_FONT_H));
    pluginNameLabel->setJustificationType (Justification::centred);
    pluginNameLabel->setEditable (false, false, false);
    pluginNameLabel->setColour (Label::backgroundColourId, Colour (0));
    pluginNameLabel->setColour (Label::textColourId, getPlumeColour (headerText));
    pluginNameLabel->addMouseListener (this, false);
    
    // Preset Name
    presetNameLabel.reset (new Label ("Preset Name Label", processor.getPresetHandler().getCurrentPresetName()));
    addAndMakeVisible (*presetNameLabel);
    presetNameLabel->setFont (PLUME::font::plumeFont.withHeight (PLUME::font::HEADER_LABEL_FONT_H));
    presetNameLabel->setJustificationType (Justification::centred);
    presetNameLabel->setEditable (false, false, false);
    presetNameLabel->setColour (Label::backgroundColourId, Colour (0));
    presetNameLabel->setColour (Label::textColourId, getPlumeColour (headerText));
    
    createButtons();
    
	// Plugin List menu
    createPluginMenu (KnownPluginList::sortByManufacturer);
    
    processor.getParameterTree().addParameterListener ("track_arm", this);
}

HeaderComponent::~HeaderComponent()
{
    processor.getParameterTree().removeParameterListener ("track_arm", this);
    pluginNameLabel = nullptr;
    presetNameLabel = nullptr;
    pluginListButton = nullptr;
    savePresetButton = nullptr;
}

//==============================================================================
const String HeaderComponent::getInfoString()
{
    return "Header :\n\n"
           "- Click on the arrow to display all the available plugins to use.\n"
           "- Click on the plugin name to open its interface.\n";
}

void HeaderComponent::update()
{
    pluginNameLabel->setText (processor.getWrapper().getWrappedPluginName(), dontSendNotification);
    presetNameLabel->setText (processor.getPresetHandler().getCurrentPresetName(), dontSendNotification);
    createPluginMenu (KnownPluginList::sortByManufacturer);
}

//==============================================================================
void HeaderComponent::paint (Graphics& g)
{
    using namespace PLUME::UI;
    
    // Background
    g.setColour (getPlumeColour (headerBackground));
    g.fillRoundedRectangle (getLocalBounds().reduced (MARGIN_SMALL).toFloat(), 15.0f);

    g.setColour (getPlumeColour (presetDisplayBackground));

    // Preset Name Area
    g.fillRoundedRectangle (presetNameLabel->getBounds().reduced (0, 6)
                                                        .withLeft (leftArrowButton->getX())
                                                        .withRight (rightArrowButton->getX() +
                                                                    rightArrowButton->getWidth())
                                                        .toFloat(),
                            presetNameLabel->getHeight()/3.0f);

    // Arrow buttons background
    g.saveState();
    g.excludeClipRegion (juce::Rectangle<int> (1, getHeight())
                             .withLeft (leftArrowButton->getBounds().getRight())
                             .withRight (rightArrowButton->getBounds().getX()));

    g.setColour (getPlumeColour (presetDisplayArrowsBackground));
    g.fillRoundedRectangle (presetNameLabel->getBounds().reduced (0, 6)
                                                        .withLeft (leftArrowButton->getX())
                                                        .withRight (rightArrowButton->getX() +
                                                                    rightArrowButton->getWidth())
                                                        .toFloat(),
                            presetNameLabel->getHeight()/3.0f);

    g.restoreState();

    // Plugin Name Area
    g.saveState();
    g.reduceClipRegion (getLocalBounds().withLeft (pluginNameLabel->getX()));
    g.setColour (getPlumeColour (pluginDisplayBackground));

    g.fillRoundedRectangle (getLocalBounds().reduced (MARGIN_SMALL).toFloat(), 15.0f);
    g.restoreState();

    // Ring Path
    g.setColour (getPlumeColour (headerText).withAlpha (0.9f));
    Path ringPath = PLUME::path::createPath (PLUME::path::ring);

    g.fillPath (ringPath,
                ringPath.getTransformToScaleToFit (juce::Rectangle<float> (16.0f, 16.0f)
                                                        .withCentre ({float (trackArmButton->getBounds().getRight()) + 15.0f,
                                                                     float (trackArmButton->getBounds().getCentreY())}),
                                                   true));
}

void HeaderComponent::resized()
{
    using namespace PLUME::UI;
    
    auto area = getLocalBounds();

    // Automation Area
    {
        auto automArea = area.removeFromLeft (60).reduced (2*MARGIN, 3*MARGIN_SMALL)
                                                 .translated (MARGIN_SMALL, 0);
        trackArmButton->setBounds (automArea);
    }

    // Plugin Area
    {
        auto pluginArea = area.removeFromRight (getWidth()/4);

        pluginListButton->setBounds (pluginArea.removeFromRight (getHeight()).reduced (MARGIN));
    
        pluginNameLabel->setBounds (pluginArea.reduced (0, MARGIN_SMALL));
    }

    // Preset Area
    {
        auto presetArea = getLocalBounds().withSizeKeepingCentre (250, area.getHeight());
        
        leftArrowButton->setBounds (presetArea.removeFromLeft (HEADER_HEIGHT).reduced (MARGIN));
        rightArrowButton->setBounds (presetArea.removeFromRight (HEADER_HEIGHT).reduced (MARGIN));
        presetNameLabel->setBounds (presetArea.reduced (0, MARGIN_SMALL));
        savePresetButton->setBounds (presetArea.removeFromRight (20).reduced (0, MARGIN));
    }

}

//==============================================================================
void HeaderComponent::mouseUp (const MouseEvent &event)
{
	if (event.eventComponent == pluginNameLabel.get())
	{
		if (processor.getWrapper().isWrapping())
		{
			if (auto* editor = getParentComponent())
			{
				processor.getWrapper().createWrapperEditor(editor);
			}
        }
	}
}


void HeaderComponent::mouseEnter (const MouseEvent &event)
{
    if (event.eventComponent == pluginNameLabel.get() && processor.getWrapper().isWrapping())
	{
        pluginNameLabel->setColour (Label::textColourId,
                                    getPlumeColour (headerText).withAlpha (0.5f));
	}
}

void HeaderComponent::mouseExit (const MouseEvent &event)
{
    if (event.eventComponent == pluginNameLabel.get())
	{
        pluginNameLabel->setColour (Label::textColourId,
                                    getPlumeColour (headerText));
	}
}

void HeaderComponent::buttonClicked (Button* bttn) 
{
    if (bttn == pluginListButton.get())
    {
        if (processor.getWrapper().getList().getNumTypes() == 0)
        {
            processor.sendActionMessage (PLUME::commands::scanRequired);
        }
        else
        {
            pluginListMenu.showMenuAsync (PopupMenu::Options().withParentComponent (getParentComponent())
                                                              .withMinimumWidth (100)
                                                              .withMaximumNumColumns (3)
                                                              .withPreferredPopupDirection
                                                                  (PopupMenu::Options::PopupDirection::downwards)
                                                              .withTargetScreenArea
                                                                  (juce::Rectangle<int> (getScreenX() + getWidth()-2,
                                                                                         getScreenY() + getHeight(),
                                                                                         1, 1)),
                                          ModalCallbackFunction::forComponent (pluginMenuCallback, this));
        }
    }
    else if (bttn == savePresetButton.get())
    {
        newPresetPanel.setVisible (true);
    }
    else if (bttn == leftArrowButton.get())
    {
        setPreviousPreset();
    }
    else if (bttn == rightArrowButton.get())
    {
        setNextPreset();
    }
}


void HeaderComponent::parameterChanged (const String &parameterID, float newValue)
{
    trackArmButton->setToggleState (newValue == 1.0f);
}

void HeaderComponent::pluginMenuCallback (int result, HeaderComponent* header)
{
    if (header != nullptr)
    {
		header->handlePluginChoice (result);
    }
}

void HeaderComponent::handlePluginChoice (int chosenId)
{
    if (chosenId == 0)
    {   
        // resets the button colour if no choice was made
        pluginListButton->setOutline (getPlumeColour (headerText), 2.0f);
    }
    else
    {
        // Removes the window in case it's opened
        processor.getWrapper().clearWrapperEditor();


        if (processor.getWrapper().wrapPlugin (chosenId))
        {
            pluginNameLabel->setText (processor.getWrapper().getWrappedPluginName(), dontSendNotification);

            // Creates the wrapper editor object as a child of the editor
            createPluginWindow();
        }
    }
}

void HeaderComponent::createPluginMenu (KnownPluginList::SortMethod sort)
{
	pluginListMenu.clear();
	pluginListMenu.addSectionHeader ("Plugins:");
    processor.getWrapper().addPluginsToMenu (pluginListMenu, sort);
}

void HeaderComponent::createPluginWindow()
{
    if (auto* editor = getParentComponent())
    {
        processor.getWrapper().createWrapperEditor (editor);
    }
}

void HeaderComponent::createButtons()
{
    // Plugin List Button
    Path arrowDown;
    arrowDown.startNewSubPath (PLUME::UI::MARGIN, 2*PLUME::UI::MARGIN);
    arrowDown.lineTo (PLUME::UI::HEADER_HEIGHT/2, PLUME::UI::HEADER_HEIGHT - PLUME::UI::MARGIN);
    arrowDown.lineTo (PLUME::UI::HEADER_HEIGHT - PLUME::UI::MARGIN, 2*PLUME::UI::MARGIN);
    
    pluginListButton.reset (new PlumeShapeButton ("Plugin List Button",
                                                                Colour(0),
                                                                getPlumeColour (headerButtonStroke)));
    addAndMakeVisible (*pluginListButton);
    pluginListButton->setShape (arrowDown, false, false, false);
    pluginListButton->addListener (this);

    // Save Preset Button
    savePresetButton.reset (new PlumeShapeButton ("Save Preset Button",
                                                                Colour(0),
                                                                getPlumeColour (headerButtonStroke)));
    addAndMakeVisible (*savePresetButton);


    savePresetButton->setShape (PLUME::path::createPath (PLUME::path::floppyDisk), false, true, false);
    savePresetButton->setPaintMode (PlumeShapeButton::fill);
    savePresetButton->addListener (this);

    // Preset Change buttons
    Path arrowLeft;
    arrowLeft.startNewSubPath (5.0f, 0.0f);
    arrowLeft.lineTo (0.0f, 5.0f);
    arrowLeft.lineTo (5.0f, 10.0f);

    Path arrowRight;
    arrowRight.startNewSubPath (0.0f, 0.0f);
    arrowRight.lineTo (5.0f, 5.0f);
    arrowRight.lineTo (0.0f, 10.0f);

    leftArrowButton.reset (new PlumeShapeButton ("Change Preset Left Button",
                                                                Colour(0),
                                                                getPlumeColour (headerButtonStroke)));
    addAndMakeVisible (*leftArrowButton);


    leftArrowButton->setShape (arrowLeft, false, true, false);
    leftArrowButton->addListener (this);

    rightArrowButton.reset (new PlumeShapeButton ("Change Preset Right Button",
                                                                Colour(0),
                                                                getPlumeColour (headerButtonStroke)));
    addAndMakeVisible (*rightArrowButton);


    rightArrowButton->setShape (arrowRight, false, true, false);
    rightArrowButton->addListener (this);

    trackArmButton.reset (new DualTextToggle ("Gesture Automation", "Gesture Automation",
                                              getPlumeColour (presetDisplayBackground),
                                              getPlumeColour (headerText).withAlpha (0.9f),
                                              DualTextToggle::toggle));
    addAndMakeVisible (*trackArmButton);
    trackArmButton->setToggleState (processor.getParameterTree().getParameter ("track_arm")->getValue() == 1.0f);
    trackArmButton->setStateIndependentTextColour (getPlumeColour (headerText));
    trackArmButton->setToggleThumbColour (getPlumeColour (tunerSliderBackground));
    trackArmButton->onStateChange = [this]()
    {
        RangedAudioParameter* trackArmParameter = processor.getParameterTree().getParameter("track_arm");

        if (trackArmParameter != nullptr)
        {
            trackArmParameter->beginChangeGesture();
            trackArmParameter->setValueNotifyingHost(trackArmButton->getToggleState() ? 1.0f : 0.0f);
            trackArmParameter->endChangeGesture();
        }
    };
}

void HeaderComponent::setPreviousPreset()
{
    setPresetWithOffset (-1);
}

void HeaderComponent::setNextPreset()
{
    setPresetWithOffset (1);
}

void HeaderComponent::setPresetWithOffset (const int offset)
{
    if (offset == 0)
    {
        // Does nothing if the offset is 0...
        jassertfalse;
        return;
    }

    PresetHandler& presetHandler = processor.getPresetHandler();

    // Invalid preset / no current preset / current preset not in search list
    // Loads first or last preset in list
    if (presetHandler.getCurrentPresetIdInSearchList() == -1 && presetHandler.getNumSearchedPresets() > 0)
    {
        if (offset < 0) prepareGesturePanelAndLoadPreset (presetHandler.getNumSearchedPresets() - 1);
        else            prepareGesturePanelAndLoadPreset (0);
    }

    // Valid preset in search list. Loads preset depending on offset
    else if (presetHandler.getNumSearchedPresets() > std::abs (offset))
    {
        int newPresetId = presetHandler.getCurrentPresetIdInSearchList() + offset;

        if (newPresetId >= 0 && newPresetId < presetHandler.getNumSearchedPresets())
        {
            prepareGesturePanelAndLoadPreset (newPresetId);
        }
    }
    
}


void HeaderComponent::prepareGesturePanelAndLoadPreset (const int presetId)
{
    // Prepares GesturePanel For Preset Change
    if (GesturePanel* gesturePanel = dynamic_cast<GesturePanel*> ( getParentComponent()
                                                                       ->findChildWithID("gesturePanel")))
    {
        gesturePanel->stopTimer();
        gesturePanel->removeListenerForAllParameters();
    }

    // Sets Preset

    // Gets the preset Xml and loads it using the processor
    if (std::unique_ptr<XmlElement> presetXml = processor.getPresetHandler().getPresetXmlToLoad (presetId))
    {

        PLUME::log::writeToLog ("Loading preset (using top arrows) : " + processor.getPresetHandler().getPresetForId (presetId).getName(), PLUME::log::presets);

        MemoryBlock presetData;
        AudioProcessor::copyXmlToBinary (*presetXml, presetData);

        processor.getWrapper().removeAllChangeListeners();

        // Calls the plugin's setStateInformation method to load the preset
        processor.setStateInformation (presetData.getData(), int (presetData.getSize()));
        presetXml->deleteAllChildElements(); // frees the memory
    }
    else // failed to get preset xml somehow
    {
        processor.getPresetHandler().resetPreset();
    }
}