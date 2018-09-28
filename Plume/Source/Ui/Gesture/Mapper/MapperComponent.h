/*
  ==============================================================================

    Mapper.h
    Created: 24 Jul 2018 8:44:18pm
    Author:  Alex

  ==============================================================================
*/

#pragma once

#include "../../../../JuceLibraryCode/JuceHeader.h"
#include "Wrapper/PluginWrapper.h"
#include "Gesture/Gesture.h"
#include "Ui/Gesture/Mapper/MappedParameterComponent.h"

//==============================================================================
/*
*/
class MapperComponent    : public Component,
                           private Button::Listener,
                           private ChangeListener,
                           private ChangeBroadcaster
{
public:
    //==============================================================================
    MapperComponent(Gesture& gest, GestureArray& gestArr, PluginWrapper& wrap);
    ~MapperComponent();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    void buttonClicked (Button* bttn) override;
    
    //==============================================================================
    void updateDisplay();
    void initializeParamCompArray();
    void addAndMakeArrayVisible();
    void resizeArray();
    
    //==============================================================================
    void changeListenerCallback(ChangeBroadcaster* source) override;
    
    //==============================================================================
    bool mapModeOn;

private:
    //==============================================================================
    Gesture& gesture;
    GestureArray& gestureArray;
    PluginWrapper& wrapper;
    
    //==============================================================================
    ScopedPointer<TextButton> mapButton;
    ScopedPointer<TextButton> clearMapButton;
    
    OwnedArray<MappedParameterComponent> paramCompArray;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MapperComponent)
};