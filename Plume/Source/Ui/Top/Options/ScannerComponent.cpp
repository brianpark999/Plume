/*
  ==============================================================================

    ScannerComponent.cpp
    Created: 31 Jan 2019 11:42:32am
    Author:  Alex

  ==============================================================================
*/

#include "ScannerComponent.h"

//==============================================================================
ScannerComponent::ScannerComponent (PlumeProcessor& proc, int buttonWidth)   : processor (proc),
                                                                               buttonW (buttonWidth),
                                                                               scanButton (new TextButton ("Scan Button"))
{
    // Scan Button
    addAndMakeVisible (scanButton);
    scanButton->setButtonText ("Scan");
    scanButton->addListener (this);
	
	addAndMakeVisible (bar = new PlumeProgressBar (processor.getWrapper().getScanner().getProgressRef(),
                                                   processor.getWrapper().getScanner().getPluginStringRef(),
                                                   "Scanning :"));
}

ScannerComponent::~ScannerComponent()
{
	scanButton = nullptr;
	bar = nullptr;
}

void ScannerComponent::paint (Graphics&)
{
}

void ScannerComponent::resized()
{
    if (getWidth() != 0 && (buttonW < 10 || buttonW > getWidth()*2/3)) buttonW = jmax (10, getWidth()/5);

    auto area = getLocalBounds();

    scanButton->setBounds (area.removeFromLeft (buttonW));
    bar->setBounds (area.reduced (PLUME::UI::MARGIN, 0));
}

void ScannerComponent::buttonClicked (Button* bttn)
{
    if (bttn == scanButton)
    {
        if (processor.getWrapper().getScanner().isScanRunning())
        {
            cancelScan();
        }

        else
        {
            scanPlugins (ModifierKeys::currentModifiers.isAltDown());
        }
    }
}

void ScannerComponent::timerCallback()
{
    if (processor.getWrapper().getScanner().isScanRunning())
    {
		bar->repaint();
    }
    else
    {
        if (processor.getWrapper().getScanner().hasScanFinished())
        {
            bar->repaint();
            stopTimer();
            
            scanFinished();
        }
    }
}

void ScannerComponent::scanPlugins (bool clearList)
{
    //if (!isCurrentlyModal()) enterModalState (false, nullptr, false);

    DBG ("Scan Start");
    
    if (clearList)
    {
        processor.getWrapper().getList().clear();
        processor.getWrapper().resetDeadsManPedalFile();
        processor.getWrapper().getList().clearBlacklistedFiles();
    }

    scanButton->setButtonText ("Cancel");
    processor.getWrapper().startScanProcess (true);
    
    startTimer (20);
}

void ScannerComponent::cancelScan()
{
    processor.getWrapper().getScanner().cancelScan();

    stopTimer();
    bar->repaint();
    scanButton->setButtonText ("Scan");

    if (auto* header = dynamic_cast<PlumeComponent*> (getParentComponent()
                                                    ->getParentComponent()
                                                    ->findChildWithID ("header")))
    {
        header->update();
    }

    //exitModalState (0);
}

void ScannerComponent::scanFinished()
{
    scanButton->setButtonText ("Scan");
    processor.getWrapper().handleScanFinished();
    bar->repaint();

    if (auto* header = dynamic_cast<PlumeComponent*> (getParentComponent() // FileSubPanel
                                                        ->getParentComponent() // TabbedPanel
                                                        ->getParentComponent() // OptionsPanel
                                                        ->getParentComponent() // Editor
                                                        ->findChildWithID ("header")))
    {
        header->update();
    }
        
    //exitModalState (1);
}