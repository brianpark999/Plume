/*
  ==============================================================================

    GesturePanel.cpp
    Created: 11 Jul 2018 3:42:22pm
    Author:  Alex

  ==============================================================================
*/

#include "Gesture/GestureArray.h"
#include "Ui/Gesture/GesturePanel.h"
#include "Ui/Gesture/Tuner/GesturesTuner.h"
#include "Ui/Gesture/SettingsTabs/MapperComponent.h"
#include "GestureSettingsComponent.h"

//==============================================================================
GesturePanel::GesturePanel (GestureArray& gestArray, PluginWrapper& wrap,
                            AudioProcessorValueTreeState& params, NewGesturePanel& newGest,
                            int freqHz)
                            : gestureArray (gestArray), wrapper (wrap),
                              parameters (params), newGesturePanel (newGest),
                              freq (freqHz)
{
    TRACE_IN;
    setComponentID ("gesturePanel");
    setWantsKeyboardFocus (true);

    initialiseGestureSlots();
    createAndAddCloseButton();

    startTimerHz (freq);
}

GesturePanel::~GesturePanel()
{
    TRACE_IN;
    stopTimer();
    unselectCurrentGesture();
    newGesturePanel.hidePanel (true);
    removeListenerForAllParameters();
}

//==============================================================================
const String GesturePanel::getInfoString()
{
    return "Gesture Panel: \n\n"
           "- Click on a gesture to access to its settings.\n"
           "- Click on a \"+\" button to add a gesture in a slot.";
}

void GesturePanel::update()
{
    if (newGesturePanel.isVisible())
    {
        int lastSlot = newGesturePanel.getLastSelectedSlot();

        updateSlotIfNeeded (lastSlot);
        newGesturePanel.hidePanel();

        renameGestureInSlot (lastSlot);
    }

    stopTimer();

    for (int i=0; i<PLUME::NUM_GEST; i++)
    {
        updateSlotIfNeeded (i);
    }

    if (selectedGesture != -1)
    {
        gestureSettings->update();
        gestureSettings->updateMappedParameters();
    }

    startTimerHz (freq);
}

//==============================================================================
void GesturePanel::paint (Graphics& g)
{
}

void GesturePanel::resized()
{
    using namespace PLUME::UI;

    auto area = getLocalBounds().reduced (2*MARGIN, 4*MARGIN);
    resizeSlotsAndTrimAreaAccordingly (area, MARGIN);
    
    if (settingsVisible)
    {
        gestureSettings->setBounds (area.reduced (MARGIN)); //.removeFromRight (jmax (getWidth()/2, getWidth() - SIDEBAR_WIDTH*3/2)));
        closeButton->setBounds (juce::Rectangle<int> (30, 30).withX (gestureSettings->getRight() - MARGIN - 30)
                                                             .withY (gestureSettings->getY() + MARGIN)
                                                             .reduced (7));
    }
}

void GesturePanel::timerCallback()
{
    if (gestureSettings != nullptr)
    {
        gestureSettings->updateDisplay();
    }
}

void GesturePanel::buttonClicked (Button* bttn)
{
    if (bttn == closeButton)
    {
        unselectCurrentGesture();
    }
}

void GesturePanel::mouseUp (const MouseEvent &event)
{
    if (event.eventComponent != this)
    {
        if (event.mods.isLeftButtonDown())
        {
            if (dragMode) endDragMode();

			handleLeftClickUp (event);
        }

        else if (event.mods.isPopupMenu())
        {
            if (auto* gestureComponent = dynamic_cast<GestureComponent*> (event.eventComponent))
            {
                createMenuForGestureId (gestureComponent->id);
            }
        }
    }
}

void GesturePanel::mouseDrag (const MouseEvent& event)
{
    auto relativeEvent = event.getEventRelativeTo (this);

    if (relativeEvent.mods.isLeftButtonDown())
    {
        if (auto* gestureComponent = dynamic_cast<GestureComponent*> (relativeEvent.originalComponent))
        {
            if (!dragMode)
            {
                startDragMode (gestureComponent->id);
            }

			int formerDraggedOverId = draggedOverSlotId;

            if (Component* componentUnderMouse = getComponentAt (relativeEvent.getPosition()))
            {
                if (auto* otherGesture = dynamic_cast<GestureComponent*> (componentUnderMouse))
                {
					if (otherGesture->id != draggedGestureComponentId)
					{
						draggedOverSlotId = otherGesture->id;
						otherGesture->repaint();
					}
				}
                else if (auto* emptySlot = dynamic_cast<EmptyGestureSlotComponent*> (componentUnderMouse))
                {
                    draggedOverSlotId = emptySlot->id;
					emptySlot->repaint();
                }
				else
				{
					draggedOverSlotId = -1;
				}
            }
            else
            {
                draggedOverSlotId = -1;
            }

			if (formerDraggedOverId != -1 && formerDraggedOverId != draggedOverSlotId)
				gestureSlots[formerDraggedOverId]->repaint();
        }
    }
}

void GesturePanel::handleLeftClickUp (const MouseEvent& event)
{
    if (auto* gestureComponent = dynamic_cast<GestureComponent*> (event.eventComponent))
    {
        // Mouse didn't leave the component it clicked in the first place
        if (getComponentAt (event.getEventRelativeTo (this).getPosition()) == event.eventComponent)
        {
            if (!gestureComponent->isSelected())
            {
                selectGestureExclusive (*gestureComponent);
            }
        }
        else // Mouse was dragged to another component
        {
            if (Component* componentUnderMouse = getComponentAt (event.getEventRelativeTo (this).getPosition()))
            {
                if (auto* slotUnderMouse = dynamic_cast<EmptyGestureSlotComponent*> (componentUnderMouse))
                {
                    DBG ("Moving gesture " << gestureComponent->id << " to slot " << slotUnderMouse->id);
                    moveGestureToId (gestureComponent->id, slotUnderMouse->id);
                }
                else if (auto* gestureComponentUnderMouse = dynamic_cast<GestureComponent*> (componentUnderMouse))
                {
                    DBG ("Swapping gestures " << gestureComponent->id << " and " << gestureComponentUnderMouse->id);
                    swapGestures (gestureComponent->id, gestureComponentUnderMouse->id);
                }
            }
        }
    }

    else if (auto* emptySlot = dynamic_cast<EmptyGestureSlotComponent*> (event.eventComponent))
    {
        newGesturePanel.showPanelForGestureID (emptySlot->id);
    }
}

void GesturePanel::handleLeftClickDrag (const MouseEvent& event)
{
    
}

bool GesturePanel::keyPressed (const KeyPress &key)
{
    if (hasSelectedGesture() && key.isValid())
    {
        if (key.getKeyCode() == KeyPress::deleteKey || key.getKeyCode() == KeyPress::backspaceKey)
        {
            removeGestureAndGestureComponent (selectedGesture);
        }

        else if (key.getTextCharacter() == 'r')
        {
			if (key.getModifiers().isAltDown())
			{
				renameGestureInSlot (selectedGesture);
			}
        }
    }

	return false;
}

void GesturePanel::initialiseGestureSlots()
{
    for (int i=0; i<PLUME::NUM_GEST; i++)
    {
        if (Gesture* gestureToCreateComponentFor = gestureArray.getGesture (i))
        {
            gestureSlots.add (new GestureComponent (*gestureToCreateComponentFor, dragMode,
                                                                                  draggedGestureComponentId,
                                                                                  draggedOverSlotId));
            addParameterListenerForGestureId (i);
        }
        else
        {
            gestureSlots.add (new EmptyGestureSlotComponent (i, dragMode,
                                                                draggedGestureComponentId,
                                                                draggedOverSlotId));
        }

        addAndMakeVisible (gestureSlots.getLast());
        gestureSlots.getLast()->addMouseListener (this, false);
    }
}

void GesturePanel::resizeSlotsAndTrimAreaAccordingly (juce::Rectangle<int>& area, int margin)
{
    using namespace PLUME::UI;
    if (PLUME::NUM_GEST == 0 || gestureSlots.size() == 0) return;

    // There should be an even number of gestures for the grid of gesture slots to make sense...
    jassert (PLUME::NUM_GEST%2 == 0);
    int numRows = PLUME::NUM_GEST/2;

    int tempWidth = area.getWidth()/4;

    if (!settingsVisible)
    {
        area.reduce (tempWidth, 0);
    }

    auto column1 = area.removeFromLeft (tempWidth);
    auto column2 = area.removeFromRight (tempWidth);

    int slotHeight = area.getHeight()/numRows;

    // sets bounds depending on the value in the array
    for (int i=0; i<gestureSlots.size(); i++)
    {
        gestureSlots[i]->setBounds (i < numRows ? column1.removeFromTop (slotHeight).reduced (margin)
                                                : column2.removeFromTop (slotHeight).reduced (margin));
    }
}

void GesturePanel::updateSlotIfNeeded (int slotToCheck)
{
    // 1st check, if a gesture was deleted (slot is GestureComponent but should be empty)
    if (auto* gestureComponent = dynamic_cast<GestureComponent*> (gestureSlots[slotToCheck]))
    {
        if (gestureArray.getGesture (slotToCheck) == nullptr)
        {
            removeParameterListenerForGestureId (slotToCheck);
            gestureSlots.set (slotToCheck, new EmptyGestureSlotComponent (slotToCheck, 
                                                                          dragMode,
                                                                          draggedGestureComponentId,
                                                                          draggedOverSlotId),
                                           true);

            addAndMakeVisible (gestureSlots[slotToCheck]);
            gestureSlots[slotToCheck]->addMouseListener (this, false);
            resized();
            repaint();
        }
    }
    // 2nd check, if a gesture was created (slot is empty but should be a gestureComponent)
    else if (auto* emptySlot = dynamic_cast<EmptyGestureSlotComponent*> (gestureSlots[slotToCheck]))
    {
        if (auto* gestureThatWasCreated = gestureArray.getGesture (slotToCheck))
        {
            addParameterListenerForGestureId (slotToCheck);

            gestureSlots.set (slotToCheck, new GestureComponent (*gestureThatWasCreated,
                                                                 dragMode,
                                                                 draggedGestureComponentId,
                                                                 draggedOverSlotId),
                                           true);

            addAndMakeVisible (gestureSlots[slotToCheck]);
            gestureSlots[slotToCheck]->addMouseListener (this, false);

			if (newGesturePanel.getLastSelectedSlot() == slotToCheck)
			{
				newGesturePanel.hidePanel(true);
				selectGestureExclusive(*dynamic_cast<GestureComponent*> (gestureSlots[slotToCheck]));
			}

            resized();
            repaint();
        }
    }
}


void GesturePanel::moveGestureToId (int idToMoveFrom, int idToMoveTo)
{
    bool mustChangeSelection = (selectedGesture == idToMoveFrom);
    
    if (mustChangeSelection) unselectCurrentGesture();

    gestureArray.moveGestureToId (idToMoveFrom, idToMoveTo);
	update();

    if (mustChangeSelection)
    {
        selectGestureExclusive (idToMoveTo);
    }
}

void GesturePanel::swapGestures (int firstId, int secondId)
{
    bool mustChangeSelection = (selectedGesture == firstId || selectedGesture == secondId);
    int idToSelect;

    if (mustChangeSelection)
    {
        idToSelect = (selectedGesture == firstId ? secondId : firstId);
        unselectCurrentGesture();
    }

    // Deletes GestureComponents for the 2 slots
    gestureSlots.set (firstId, new EmptyGestureSlotComponent (firstId, dragMode,
                                                                       draggedGestureComponentId,
                                                                       draggedOverSlotId), true);
    gestureSlots.set (secondId, new EmptyGestureSlotComponent (secondId, dragMode,
                                                                         draggedGestureComponentId,
                                                                         draggedOverSlotId), true);

    gestureArray.swapGestures (firstId, secondId);
    update();
    
    if (mustChangeSelection) selectGestureExclusive (idToSelect);
}

void GesturePanel::renameGestureInSlot (int slotNumber)
{
    if (auto* gestureComponent = dynamic_cast<GestureComponent*> (gestureSlots[slotNumber]))
    {
        gestureComponent->startNameEntry();
    }
    else
    {
        /* Tried to rename a gesture, but the selected dlot was empty...
        */
        jassertfalse;
    }
}

void GesturePanel::removeGestureAndGestureComponent (int gestureId)
{
    if (gestureId < 0 || gestureId > PLUME::NUM_GEST) return;
    stopTimer();

    if (gestureId == selectedGesture)
    {
        unselectCurrentGesture();
        gestureSettings.reset (nullptr);
    }

    removeParameterListenerForGestureId (gestureId);
    gestureArray.removeGesture (gestureId);
    updateSlotIfNeeded (gestureId);

    if (!isTimerRunning()) startTimerHz (freq);
}

bool GesturePanel::hasSelectedGesture()
{
    return selectedGesture != -1;
}

void GesturePanel::switchGestureSelectionState (GestureComponent& gestureComponentToSwitch)
{
    if (gestureComponentToSwitch.isSelected())
    {
        gestureComponentToSwitch.setSelected (false);
        selectedGesture = -1;
        setSettingsVisible (false);
    }
    else
    {
        selectGestureExclusive (gestureComponentToSwitch);
    }
}

void GesturePanel::selectGestureExclusive (GestureComponent& gestureComponentToSelect)
{
    gestureComponentToSelect.setSelected (true);

    for (auto* slot : gestureSlots)
    {
        if (auto* gestureComponent = dynamic_cast<GestureComponent*> (slot))
        {
            if (gestureComponent != &gestureComponentToSelect && gestureComponent->isSelected())
            {
                gestureComponent->setSelected (false);
                gestureArray.getGesture (gestureComponent->id)->removeAllChangeListeners();
            }
        }
    }

    gestureSettings.reset (new GestureSettingsComponent (gestureComponentToSelect.getGesture(),
                                                         gestureArray, wrapper));
    selectedGesture = gestureComponentToSelect.id;
    setSettingsVisible (true);
}

void GesturePanel::selectGestureExclusive (const int idToSelect)
{
    if (idToSelect < 0 || idToSelect >= gestureSlots.size()) return;

    if (auto* gestureComponent = dynamic_cast<GestureComponent*> (gestureSlots[idToSelect]))
    {
        selectGestureExclusive (*gestureComponent);
    }
}

void GesturePanel::unselectCurrentGesture()
{
	// Can't unselect if nothing is selected..
	if (selectedGesture == -1) return;

    if (auto* gestureComponentToUnselect = dynamic_cast<GestureComponent*> (gestureSlots[selectedGesture]))
    {
        if (!gestureComponentToUnselect->isSelected())
        {
            // Plume tried to unselect an already unselected gesture...
            jassertfalse;
            return;
        }

        gestureComponentToUnselect->setSelected (false);

        if (auto* gestureToUnselect = gestureArray.getGesture (selectedGesture))
            gestureToUnselect->removeAllChangeListeners();

        selectedGesture = -1;
        setSettingsVisible (false);
        gestureSettings.reset (nullptr);

        return;
    }

    /* Hitting this assert means that Plume tried to unselect a gesture, but the slot
       it tried to access is an empty slot. That might either mean that an emptySlot failed
       to be updated to a GestureComponent, or that Plume failed to keep track of the actual
       selected Gesture.
    */
    jassertfalse;
}

void GesturePanel::createMenuForGestureId (int id)
{
    PopupMenu gestureMenu;

    gestureMenu.addItem (1, "Rename", true);
    gestureMenu.addItem (2, "Duplicate", true);
    gestureMenu.addItem (3, "Delete", true);
    
    handleMenuResult (id,
                      gestureMenu.showMenu (PopupMenu::Options().withParentComponent (getParentComponent())
                                                                .withMaximumNumColumns (3)
                                                                .withPreferredPopupDirection (PopupMenu::Options::PopupDirection::downwards)
                                                                .withStandardItemHeight (20)));
}

void GesturePanel::handleMenuResult (int gestureId, const int menuResult)
{
    switch (menuResult)
    {
        case 0: // No choice
            break;
            
        case 1: // Rename gesture
            renameGestureInSlot (gestureId);
            break;
            
        case 2: // Duplicate
            gestureArray.duplicateGesture (gestureId);
            update();
            selectGestureExclusive (gestureId);
            break;

        case 3: // Delete gesture
            removeGestureAndGestureComponent (gestureId);
            update();
    }
}

void GesturePanel::setSettingsVisible (bool shouldBeVisible)
{
    if (!shouldBeVisible)
    {
        gestureSettings->setVisible (false);
        closeButton->setVisible (false);
        settingsVisible = false;
        resized();
        repaint();

        return;
    }

    if (shouldBeVisible && gestureSettings != nullptr)
    {
        addAndMakeVisible (gestureSettings, 0);
        closeButton->setVisible (true);
        settingsVisible = true;
        resized();
        repaint();

        return;
    }

    /* Plume attempted to show the gesture settings panel when it was not instanciated!
       There should be a call similar to the following one before calling this method if you want
       to display the settings panel:
            gestureSettings.reset ( [gesture that was selected] , gestureArray, wrapper); 
    */
    jassertfalse;
}

void GesturePanel::createAndAddCloseButton()
{
    addAndMakeVisible (closeButton = new ShapeButton ("Close Settings Button", Colour(0x00000000),
                                                                               Colour(0x00000000),
                                                                               Colour(0x00000000)),
                      -1);

    Path p;
    p.startNewSubPath (0, 0);
    p.lineTo (3*PLUME::UI::MARGIN, 3*PLUME::UI::MARGIN);
    p.startNewSubPath (0, 3*PLUME::UI::MARGIN);
    p.lineTo (3*PLUME::UI::MARGIN, 0);

    closeButton->setShape (p, false, true, false);
    closeButton->setOutline (Colour (0xff101010), 1.0f);
    closeButton->addMouseListener (this, false);
    closeButton->addListener (this);
}

void GesturePanel::removeListenerForAllParameters()
{
    for (auto* gesture : gestureArray.getArray())
    {
		removeParameterListenerForGestureId (gesture->id);
    }
}

void GesturePanel::addParameterListenerForGestureId (const int id)
{
    for (int i = 0; i<PLUME::param::numParams; i++)
    {
        parameters.addParameterListener (String (id) + PLUME::param::paramIds[i], this);
    }
}

void GesturePanel::removeParameterListenerForGestureId (const int id)
{
    for (int i = 0; i<PLUME::param::numParams; i++)
    {
        parameters.removeParameterListener (String (id) + PLUME::param::paramIds[i], this);
    }
}

void GesturePanel::parameterChanged (const String& parameterID, float)
{
    // if the ID is "x_value" or "x_vibrato_intensity": doesn't update
    // (only the MovingCursor object in the the GestureTunerComponent is updated)
    if (parameterID.endsWith ("ue") || parameterID.endsWith ("y") || !PLUME::UI::ANIMATE_UI_FLAG) return;
    
    const int gestureId = parameterID.substring(0,1).getIntValue();
    
    if (auto* gestureComponentToUpdate = dynamic_cast<GestureComponent*> (gestureSlots[gestureId]))
    {
        if (gestureComponentToUpdate->id == gestureId)
        {
			const MessageManagerLock mmLock;

			gestureComponentToUpdate->update();

            if (gestureSettings != nullptr)
            {
                if (gestureSettings->getGestureId() == gestureId)
                {
                    gestureSettings->update();
                }
            }
        }
    }
}


void GesturePanel::startDragMode (int slotBeingDragged)
{
    dragMode = true;
    draggedGestureComponentId = slotBeingDragged;
    draggedOverSlotId = -1;

    for (auto* slot : gestureSlots)
    {
        slot->repaint();
    }


}

void GesturePanel::endDragMode()
{
    dragMode = false;
    draggedGestureComponentId = -1;
    draggedOverSlotId = -1;

    for (auto* slot : gestureSlots)
    {
        slot->repaint();
    }
}