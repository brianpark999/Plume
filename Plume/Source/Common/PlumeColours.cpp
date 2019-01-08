/*
  ==============================================================================

    PlumeColours.cpp
    Created: 20 Dec 2018 11:35:43am
    Author:  Alex

  ==============================================================================
*/

#include "PlumeColours.h"

using namespace PLUME::colour;
        
PlumeTheme::~PlumeTheme()
{
}

Colour PlumeTheme::operator[] (const int index) const noexcept
{
    // bright red means there's an issue for that colour.. Most likely there wasn't enough colours in the constructor
    return (index < numColours && index > -1) ? palette[index] : Colour (0xffff0000);
}

Colour PlumeTheme::getColour (PlumeColourID colourId)
{
    return palette[colourId];
}

void PlumeTheme::setColour (PlumeColourID colourId, Colour newColour)
{
    palette[colourId] = newColour;
}
            
PlumeTheme PlumeTheme::createPlumeTheme (ThemeId themeToCreate)
{
    switch (themeToCreate)
    {
        case red:
            return createRedTheme();
            
		default:
            return createDefaultTheme();
    }
}

PlumeTheme PlumeTheme::createDefaultTheme()
{
    return (PlumeTheme({ // SideBar
                         0xff323232, //sideBarBackground
                         0xffffffff, //sideBarMainText
                         0xffffffff, //sideBarSubText
                         0x05ffffff, //sideBarSeparatorOut
                         0x40ffffff, //sideBarSeparatorIn
                         0xffffffff, //sideBarButtonFill
						 0xaaffffff, //sideBarButtonFillHighlighted
						 0xaaaaaaff, //sideBarButtonFillClicked
            
                         // Preset Box
                         0xff232323, //presetsBoxBackground
                         0xffffffff, //presetsBoxStandartText
                         0xffa0a0a0, //presetsBoxHighlightedBackground
                         0xff000000, //presetsBoxHighlightedText
                         0xffffffff, //presetsBoxOutlineTop
                         0xffffffff, //presetsBoxOutlineBottom
            
                         // Info Panel
                         0xff606060, //infoPanelBackground
                         0xffffffff, //infoPanelMainText
                         0xffffffff, //infoPanelSubText
            
                         // Header
                         0xfff8f8f8, //headerBackground
                         0xffa5a5a5, //headerSeparatorTop
                         0xffe1e1e1, //headerSeparatorBottom
                         0xff393939, //headerStandartText
                         0xaa393939, //headerHighlightedText
            
                         // Gesture Base Panel
                         0xffd0d0d0, //basePanelBackground
                         0xff606060, //basePanelGestureBackground
                         0xff000000, //basePanelGestureOutline
                         0xffa0a0a0, //basePanelGestureHighlightedBackground
                         0xff000000, //basePanelGestureHighlightedOutline
                         0xffffffff, //basePanelMainText
                         0xffffffff, //basePanelSubText
                
                         // Gesture detail window
                         0xffa0a0a0, //detailPanelBackground
                         0xfff0f0f0, //detailPanelHighlightedBackground
                         0xffffffff, //detailPanelMainText
                         0xffffffff, //detailPanelSubText
                         0xffffffff, //detailPanelHighlightedMainText
                         0xffffffff, //detailPanelHighlightedSubText
                         0xff000000, //detailPanelSubComponentsOutline
                         0xff943cb0  //detailPanelActiveMapping
                       }));
}

PlumeTheme PlumeTheme::createRedTheme()
{
    return (PlumeTheme({ // SideBar
                         0xff461d1d, //sideBarBackground
                         0xffffffff, //sideBarMainText
                         0xffffffff, //sideBarSubText
                         0x05ffffff, //sideBarSeparatorOut
                         0x40ffffff, //sideBarSeparatorIn
						 0xffffffff, //sideBarButtonFill
						 0xaaffffff, //sideBarButtonFillHighlighted
						 0xaaaaaaff, //sideBarButtonFillClicked
            
                         // Preset Box
                         0xff232323, //presetsBoxBackground
                         0xffffffff, //presetsBoxStandartText
                         0xffa0a0a0, //presetsBoxHighlightedBackground
                         0xff000000, //presetsBoxHighlightedText
                         0xffffffff, //presetsBoxOutlineTop
                         0xffffffff, //presetsBoxOutlineBottom
            
                         // Info Panel
                         0xff606060, //infoPanelBackground
                         0xffffffff, //infoPanelMainText
                         0xffffffff, //infoPanelSubText
            
                         // Header
                         0xfff8f8f8, //headerBackground
                         0xff927575, //headerSeparatorTop
                         0xffdbaaaa, //headerSeparatorBottom
                         0xff532323, //headerStandartText
                         0xffa84646, //headerHighlightedText
            
                         // Gesture Base Panel
                         0xffd0d0d0, //basePanelBackground
                         0xff606060, //basePanelGestureBackground
                         0xff000000, //basePanelGestureOutline
                         0xffa0a0a0, //basePanelGestureHighlightedBackground
                         0xff000000, //basePanelGestureHighlightedOutline
                         0xffffffff, //basePanelMainText
                         0xffffffff, //basePanelSubText
                
                         // Gesture detail window
                         0xffa0a0a0, //detailPanelBackground
                         0xfff0f0f0, //detailPanelHighlightedBackground
                         0xffffffff, //detailPanelMainText
                         0xffffffff, //detailPanelSubText
                         0xffffffff, //detailPanelHighlightedMainText
                         0xffffffff, //detailPanelHighlightedSubText
                         0xff000000, //detailPanelSubComponentsOutline
                         0xff943cb0  //detailPanelActiveMapping
                       }));
}