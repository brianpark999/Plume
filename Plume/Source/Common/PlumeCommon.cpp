/*
  ==============================================================================

    PlumeCommon.cpp
    Created: 15 Nov 2018 9:55:45am
    Author:  Alex

  ==============================================================================
*/

#include "Common/PlumeCommon.h"

namespace PLUME
{
    namespace UI
    {
        bool ANIMATE_UI_FLAG = false;
        
		using namespace PLUME::colour;
		PlumeTheme currentTheme = PlumeTheme::createPlumeTheme (PlumeTheme::plumeDefault);
    }
    
    namespace font
    {
        const Font getPlumeFont (PlumeFontId type = regular)
        {
          /*
            // Anodina
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::AnodinaRegular_otf,
                                                                PlumeData::AnodinaRegular_otfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::AnodinaRegular_otf,
                                                                PlumeData::AnodinaRegular_otfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::AnodinaBold_otf,
                                                                PlumeData::AnodinaBold_otfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::AnodinaLight_otf,
                                                                PlumeData::AnodinaLight_otfSize));
            
            // Avenir Next
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::AvenirNextLTProRegular_otf,
                                                                PlumeData::AvenirNextLTProRegular_otfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::AvenirNextLTProRegular_otf,
                                                                PlumeData::AvenirNextLTProRegular_otfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::AvenirNextLTProBold_otf,
                                                                PlumeData::AvenirNextLTProRegular_otfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::AvenirNextLTProRegular_otf,
                                                                PlumeData::AvenirNextLTProRegular_otfSize));

            */
            
            // Halis Grotesque
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::Ahmet_Altun__HalisGRRegular_otf,
                                                                PlumeData::Ahmet_Altun__HalisGRRegular_otfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::Ahmet_Altun__HalisGRBook_otf,
                                                                PlumeData::Ahmet_Altun__HalisGRBook_otfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::Ahmet_Altun__HalisGRBold_otf,
                                                                PlumeData::Ahmet_Altun__HalisGRBold_otfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::Ahmet_Altun__HalisGRLight_otf,
                                                                PlumeData::Ahmet_Altun__HalisGRLight_otfSize));
            
            /*
            // Brandon Grotesque
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::Brandon_reg_otf,
                                                                PlumeData::Brandon_reg_otfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::Brandon_reg_otf,
                                                                PlumeData::Brandon_reg_otfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::Brandon_bld_otf,
                                                                PlumeData::Brandon_bld_otfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::Brandon_light_otf,
                                                                PlumeData::Brandon_light_otfSize));

            // CocoGothic
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::CocoGothic_trial_ttf,
                                                                PlumeData::CocoGothic_trial_ttfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::CocoGothic_trial_ttf,
                                                                PlumeData::CocoGothic_trial_ttfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::CocoGothicBold_trial_ttf,
                                                                PlumeData::CocoGothicBold_trial_ttfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::CocoGothicLight_trial_ttf,
                                                                PlumeData::CocoGothicLight_trial_ttfSize));


            // FF Marselis Pro
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::FF_Marselis_Pro_otf,
                                                                PlumeData::FF_Marselis_Pro_otfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::FF_Marselis_Pro_otf,
                                                                PlumeData::FF_Marselis_Pro_otfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::FF_Marselis_Pro_Bold_otf,
                                                                PlumeData::FF_Marselis_Pro_Bold_otfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::FF_Marselis_Pro_Light_otf,
                                                                PlumeData::FF_Marselis_Pro_Light_otfSize));

            // Lack
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::LackRegular_otf,
                                                                PlumeData::LackRegular_otfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::LackRegular_otf,
                                                                PlumeData::LackRegular_otfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::LackRegular_otf,
                                                                PlumeData::LackRegular_otfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::LackRegular_otf,
                                                                PlumeData::LackRegular_otfSize));
            // Pangram
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::PangramRegular_otf,
                                                                PlumeData::PangramRegular_otfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::PangramRegular_otf,
                                                                PlumeData::PangramRegular_otfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::PangramBlack_otf,
                                                                PlumeData::PangramBlack_otfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::PangramExtraLight_otf,
                                                                PlumeData::PangramExtraLight_otfSize));

            // Roboto
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::RobotoRegular_ttf,
                                                                PlumeData::RobotoRegular_ttfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::RobotoLight_ttf,
                                                                PlumeData::RobotoLight_ttfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::RobotoBold_ttf,
                                                                PlumeData::RobotoBold_ttfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::RobotoThin_ttf,
                                                                PlumeData::RobotoThin_ttfSize));

            // TTNorms
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::TTNormsRegular_otf,
                                                                PlumeData::TTNormsRegular_otfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::TTNormsLight_otf,
                                                                PlumeData::TTNormsLight_otfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::TTNormsBold_otf,
                                                                PlumeData::TTNormsBold_otfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::TTNormsThin_otf,
                                                                PlumeData::TTNormsThin_otfSize));

          
            // ValioOmnes
            if (type == regular)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::ValioOmnesRegular_ttf,
                                                                PlumeData::ValioOmnesRegular_ttfSize));
            else if (type == book)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::ValioOmnesRegular_ttf,
                                                                PlumeData::ValioOmnesRegular_ttfSize));
            else if (type == bold)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::ValioOmnesSemibold_ttf,
                                                                PlumeData::ValioOmnesSemibold_ttfSize));
            else if (type == light)
                return Font (Typeface::createSystemTypefaceFor (PlumeData::ValioOmnesRegular_ttf,
                  
                                                          PlumeData::ValioOmnesRegular_ttfSize));
														  */
              
            return Font();
        }
        
        const Font plumeFont = getPlumeFont();
        const Font plumeFontBold = getPlumeFont (bold);
        const Font plumeFontBook = getPlumeFont (book);
        const Font plumeFontLight = getPlumeFont (light);
        
    }

	GlobalPointers globalPointers;
	
  #if JUCE_WINDOWS
    LRESULT CALLBACK messageHook (int nCode, WPARAM wParam, LPARAM lParam)
    {
		if (nCode == HC_ACTION)
		{
			if (auto* cwpStructPtr = reinterpret_cast<CWPSTRUCT*> (lParam))
			{
				uint64 message = cwpStructPtr->message;
				char name[30];
				GetWindowTextA (cwpStructPtr->hwnd, name, 30);

                if (PLUME::globalPointers.isPlumeHWND (cwpStructPtr->hwnd))
                {
    				if (message == uint64 (877))
    				{
    					DBG ("Ableton mysterious message...");
    				}
					/*
    				if (message != uint64 (13) && message != uint64 (20) && message != uint64 (32) && message != uint64 (132))
    					DBG ("Window : " << name << " (Address: 0x" << String::toHexString((uint32) cwpStructPtr->hwnd) << ")"
                                         << "\n    Message : " << String (message)
    						             << " (0x" << String::toHexString (message) << ")");*/

    				if (message == uint64 (71))
    				{
    					if (auto* windowPosPtr = reinterpret_cast<WINDOWPOS*> (cwpStructPtr->lParam))
    					{
    						DBG ("flags: 0x" << String::toHexString (windowPosPtr->flags));

                            if ((windowPosPtr->flags >> 7 & 1) == 1) // Flag SWP_HIDEWINDOW (bit 7) is active
                            {
                                DBG ("Hide " << name);
                                using namespace PLUME;

                                if (ComponentPeer* peer = globalPointers.getWrappedEditorPeer (cwpStructPtr->hwnd))
                                {
                                    peer->setMinimised (true);
                                }
                            }

                            else if ((windowPosPtr->flags >> 6 & 1) == 1) // Flag SWP_SHOWWINDOW (bit 6) is active
                            {
                                DBG ("Show " << name);
                                using namespace PLUME;

                                if (ComponentPeer* peer = globalPointers.getWrappedEditorPeer(cwpStructPtr->hwnd))
                                {
                                    peer->setMinimised (false);
                                }
                            }
    					}
    				}
                }

				return 0;
			}
		}
		else
		{
			DBG ("Unprocessable window event! Tread : " + (wParam == 0 ? String("Other")
                                                                       : String("Current")));
		}

        return CallNextHookEx (NULL, nCode, wParam, lParam);
    }
    
    bool GlobalPointers::isPlumeHWND (HWND HWNDToCheck)
    {
        ScopedLock hwndlock (hwndArrayLock);

        for (auto* handle : plumeWindowArray)
        {
            if (handle == HWNDToCheck) return true;
        }

        return false;
    }

    const int GlobalPointers::findPlumeHWNDindex (HWND HWNDToCheck)
    {
        ScopedLock hwndlock (hwndArrayLock);

        for (int i = 0; i<plumeWindowArray.size(); i++)
        {
            if (plumeWindowArray[i] == HWNDToCheck) return i;
        }

        return -1;
    }

    void GlobalPointers::addPlumeHWND (HWND newHWND)
    {
        ScopedLock hwndlock (hwndArrayLock);

        plumeWindowArray.add (newHWND);
        wrappedEditorPeerArray.add (nullptr);

		setActiveHWND (newHWND);
    
      #if JUCE_DEBUG
        DBG ("Adding HWND Global PTR!");
      #endif
    }

    void GlobalPointers::removePlumeHWND (HWND HWNDToRemove)
    {
        jassert (HWNDToRemove != NULL);
        jassert (plumeWindowArray.size() == wrappedEditorPeerArray.size());

        ScopedLock hwndlock (hwndArrayLock);

        int index = findPlumeHWNDindex (HWNDToRemove);

        if (index >= 0 && index < plumeWindowArray.size())
        {
            plumeWindowArray.remove (index);
            wrappedEditorPeerArray.remove (index);

			if (activePlumeWindow == HWNDToRemove || plumeWindowArray.size() == 0)
			{
				activePlumeWindow == NULL;
			}
        }
    }

    void GlobalPointers::clearPlumeAndWrappedWindows()
    {
        ScopedLock hwndlock (hwndArrayLock);

        plumeWindowArray.clear();
        wrappedEditorPeerArray.clear();
    }

    void GlobalPointers::setActiveHWND (HWND HWNDToSetActive)
    {
        jassert (HWNDToSetActive != NULL);

        if (isPlumeHWND (HWNDToSetActive))
        {
            activePlumeWindow = HWNDToSetActive;
        }
    }

    HWND GlobalPointers::getActiveHWND()
    {
        jassert (activePlumeWindow != NULL);

       return activePlumeWindow;
    }

    ComponentPeer* const GlobalPointers::getWrappedEditorPeer (HWND correspondingHWND)
    {
        jassert (correspondingHWND != NULL);
        jassert (plumeWindowArray.size() == wrappedEditorPeerArray.size());

        ScopedLock hwndlock (hwndArrayLock);

        int index = findPlumeHWNDindex (correspondingHWND);

        if (index >= 0 && index < plumeWindowArray.size())
        {
            return wrappedEditorPeerArray[index];
        }
    }

    void GlobalPointers::setWrappedEditorPeer (HWND correspondingHWND, ComponentPeer* newPeerPtr)
    {
        jassert (correspondingHWND != NULL);
        jassert (plumeWindowArray.size() == wrappedEditorPeerArray.size());

        ScopedLock hwndlock (hwndArrayLock);

        int index = findPlumeHWNDindex (correspondingHWND);

        if (index >= 0 && index < wrappedEditorPeerArray.size())
        {
            jassert (wrappedEditorPeerArray[index] == nullptr);
            wrappedEditorPeerArray.set (index, newPeerPtr);
        }
    }

    void GlobalPointers::resetWrappedEditorPeer (HWND correspondingHWND)
    {
        jassert (correspondingHWND != NULL);
        jassert (plumeWindowArray.size() == wrappedEditorPeerArray.size());

        ScopedLock hwndlock (hwndArrayLock);

        int index = findPlumeHWNDindex (correspondingHWND);

        if (index >= 0 && index < plumeWindowArray.size())
        {
            jassert (wrappedEditorPeerArray[index] != nullptr);
            wrappedEditorPeerArray.set (index, nullptr);
        }

          #if JUCE_DEBUG
            DBG ("Modifying Component Peer Global PTR!");
          #endif
    }
    
  #endif
    

    void GlobalPointers::addWrappedEditorPeer (ComponentPeer* newPeerPtr)
    {
        if (ComponentPeer::isValidPeer(newPeerPtr))
        {
            wrappedEditorPeerArray.add (newPeerPtr);
        
          #if JUCE_DEBUG
            DBG ("Adding Component Peer Global PTR!");
          #endif
        }
    }

    const int GlobalPointers::findComponentPeerIndex (ComponentPeer* componentPeerToCheck)
    {
        return wrappedEditorPeerArray.indexOf (componentPeerToCheck);
    }

    void GlobalPointers::resetWrappedEditorPeer (ComponentPeer* peerToReset)
    {
        int index = findComponentPeerIndex (peerToReset);

        if (index != -1)
        {
            wrappedEditorPeerArray.set (index, nullptr);
        }
    }


    namespace path
    {
        const Path createGearPath()
        {
            const unsigned char pathData[] = { 110,109,0,99,211,66,160,67,70,68,108,0,99,211,66,64,93,78,68,108,0,99,211,66,64,93,78,68,108,251,192,201,66,10,179,78,68,108,88,68,192,66,31,24,79,68,108,41,243,182,66,65,140,79,68,108,100,211,173,66,36,15,80,68,108,222,234,164,66,117,160,80,68,108,0,
                                               90,157,66,128,42,81,68,108,0,90,157,66,128,42,81,68,108,0,4,95,66,128,111,75,68,108,0,8,171,65,96,7,84,68,108,0,62,49,66,0,195,89,68,108,2,62,49,66,0,195,89,68,108,204,103,39,66,149,217,90,68,108,128,115,30,66,174,247,91,68,108,220,102,22,66,149,28,93,
                                               68,108,2,71,15,66,142,71,94,68,108,134,24,9,66,218,119,95,68,108,2,130,4,66,160,131,96,68,108,0,130,4,66,160,131,96,68,108,0,128,49,63,160,131,96,68,108,0,128,49,63,192,170,108,68,108,0,98,4,66,192,170,108,68,108,2,98,4,66,192,170,108,68,108,32,190,9,
                                               66,3,223,109,68,108,10,15,16,66,154,14,111,68,108,180,80,23,66,195,56,112,68,108,122,126,31,66,191,92,113,68,108,32,147,40,66,211,121,114,68,108,252,51,49,66,0,108,115,68,108,0,52,49,66,0,108,115,68,108,0,8,171,65,0,39,121,68,108,0,4,95,66,112,223,128,
                                               68,108,0,94,157,66,96,3,124,68,108,0,94,157,66,96,3,124,68,108,166,18,166,66,195,160,124,68,108,114,3,175,66,8,48,125,68,108,168,42,184,66,210,176,125,68,108,112,130,193,66,208,34,126,68,108,208,4,203,66,183,133,126,68,108,255,98,211,66,32,207,126,68,
                                               108,0,99,211,66,32,207,126,68,108,0,99,211,66,96,117,131,68,108,128,78,26,67,96,117,131,68,108,128,78,26,67,32,209,126,68,108,128,78,26,67,32,209,126,68,108,130,31,31,67,87,123,126,68,108,211,221,35,67,65,22,126,68,108,106,134,40,67,31,162,125,68,108,
                                               76,22,45,67,60,31,125,68,108,142,138,49,67,235,141,124,68,108,0,83,53,67,223,3,124,68,108,0,83,53,67,223,3,124,68,108,0,63,76,67,112,223,128,68,108,0,159,110,67,0,39,121,68,108,128,176,87,67,96,107,115,68,108,128,176,87,67,96,107,115,68,108,13,38,90,
                                               67,203,84,114,68,108,32,99,92,67,178,54,113,68,108,73,102,94,67,203,17,112,68,108,63,46,96,67,210,230,110,68,108,222,185,97,67,134,182,109,68,108,128,223,98,67,192,170,108,68,108,128,223,98,67,192,170,108,68,108,64,167,129,67,192,170,108,68,108,64,167,
                                               129,67,160,131,96,68,108,128,231,98,67,160,131,96,68,108,128,231,98,67,160,131,96,68,108,121,144,97,67,94,79,95,68,108,63,252,95,67,199,31,94,68,108,214,43,94,67,158,245,92,68,108,100,32,92,67,163,209,91,68,108,60,219,89,67,143,180,90,68,108,0,179,87,
                                               67,96,194,89,68,108,0,179,87,67,96,194,89,68,108,0,159,110,67,96,7,84,68,108,0,63,76,67,128,111,75,68,108,0,81,53,67,0,43,81,68,108,0,81,53,67,0,43,81,68,108,172,246,48,67,157,141,80,68,108,71,126,44,67,88,254,79,68,108,171,234,39,67,142,125,79,68,108,
                                               198,62,35,67,144,11,79,68,108,151,125,30,67,168,168,78,68,108,128,78,26,67,64,95,78,68,108,128,78,26,67,64,95,78,68,108,128,78,26,67,160,67,70,68,108,0,99,211,66,160,67,70,68,99,109,0,0,2,67,0,247,89,68,108,0,0,2,67,0,247,89,68,108,42,134,4,67,10,251,
                                               89,68,108,182,10,7,67,38,7,90,68,108,8,140,9,67,76,27,90,68,108,134,8,12,67,111,55,90,68,108,152,126,14,67,125,91,90,68,108,172,236,16,67,94,135,90,68,108,51,81,19,67,248,186,90,68,108,164,170,21,67,40,246,90,68,108,129,247,23,67,201,56,91,68,108,79,
                                               54,26,67,176,130,91,68,108,159,101,28,67,175,211,91,68,108,10,132,30,67,144,43,92,68,108,55,144,32,67,28,138,92,68,108,213,136,34,67,23,239,92,68,108,161,108,36,67,64,90,93,68,108,103,58,38,67,81,203,93,68,108,254,240,39,67,4,66,94,68,108,78,143,41,67,
                                               12,190,94,68,108,78,20,43,67,25,63,95,68,108,4,127,44,67,217,196,95,68,108,138,206,45,67,246,78,96,68,108,7,2,47,67,25,221,96,68,108,184,24,48,67,229,110,97,68,108,234,17,49,67,255,3,98,68,108,253,236,49,67,6,156,98,68,108,102,169,50,67,152,54,99,68,
                                               108,171,70,51,67,85,211,99,68,108,105,196,51,67,214,113,100,68,108,79,34,52,67,182,17,101,68,108,32,96,52,67,144,178,101,68,108,182,125,52,67,252,83,102,68,108,128,128,52,67,32,151,102,68,108,128,128,52,67,32,151,102,68,108,128,128,52,67,32,151,102,68,
                                               108,93,112,52,67,171,56,103,68,108,243,63,52,67,206,217,103,68,108,98,239,51,67,35,122,104,68,108,220,126,51,67,66,25,105,68,108,172,238,50,67,199,182,105,68,108,43,63,50,67,76,82,106,68,108,204,112,49,67,111,235,106,68,108,17,132,48,67,204,129,107,68,
                                               108,147,121,47,67,3,21,108,68,108,251,81,46,67,184,164,108,68,108,8,14,45,67,140,48,109,68,108,136,174,43,67,40,184,109,68,108,92,52,42,67,52,59,110,68,108,118,160,40,67,93,185,110,68,108,217,243,38,67,81,50,111,68,108,151,47,37,67,195,165,111,68,108,
                                               209,84,35,67,106,19,112,68,108,183,100,33,67,255,122,112,68,108,135,96,31,67,65,220,112,68,108,138,73,29,67,240,54,113,68,108,24,33,27,67,210,138,113,68,108,145,232,24,67,179,215,113,68,108,97,161,22,67,97,29,114,68,108,254,76,20,67,175,91,114,68,108,
                                               229,236,17,67,117,146,114,68,108,156,130,15,67,145,193,114,68,108,173,15,13,67,228,232,114,68,108,170,149,10,67,85,8,115,68,108,41,22,8,67,208,31,115,68,108,195,146,5,67,70,47,115,68,108,19,13,3,67,173,54,115,68,108,1,0,2,67,96,55,115,68,108,0,0,2,67,
                                               96,55,115,68,108,0,0,2,67,96,55,115,68,108,172,243,254,66,86,51,115,68,108,148,234,249,66,58,39,115,68,108,240,231,244,66,20,19,115,68,108,245,238,239,66,241,246,114,68,108,209,2,235,66,227,210,114,68,108,170,38,230,66,2,167,114,68,108,157,93,225,66,
                                               104,115,114,68,108,186,170,220,66,56,56,114,68,108,1,17,216,66,151,245,113,68,108,102,147,211,66,176,171,113,68,108,198,52,207,66,178,90,113,68,108,239,247,202,66,208,2,113,68,108,150,223,198,66,68,164,112,68,108,90,238,194,66,73,63,112,68,108,194,38,
                                               191,66,33,212,111,68,108,54,139,187,66,15,99,111,68,108,8,30,184,66,93,236,110,68,108,104,225,180,66,85,112,110,68,108,104,215,177,66,72,239,109,68,108,250,1,175,66,136,105,109,68,108,238,98,172,66,106,223,108,68,108,242,251,169,66,71,81,108,68,108,144,
                                               206,167,66,123,191,107,68,108,44,220,165,66,97,42,107,68,108,5,38,164,66,90,146,106,68,108,52,173,162,66,199,247,105,68,108,168,114,161,66,11,91,105,68,108,44,119,160,66,137,188,104,68,108,97,187,159,66,169,28,104,68,108,191,63,159,66,207,123,103,68,
                                               108,148,4,159,66,99,218,102,68,108,255,254,158,66,33,151,102,68,108,0,255,158,66,32,151,102,68,108,255,254,158,66,32,151,102,68,108,84,31,159,66,149,245,101,68,108,52,128,159,66,114,84,101,68,108,100,33,160,66,30,180,100,68,108,122,2,161,66,254,20,100,
                                               68,108,232,34,162,66,122,119,99,68,108,245,129,163,66,245,219,98,68,108,192,30,165,66,211,66,98,68,108,66,248,166,66,119,172,97,68,108,74,13,169,66,64,25,97,68,108,132,92,171,66,140,137,96,68,108,117,228,173,66,185,253,95,68,108,128,163,176,66,30,118,
                                               95,68,108,227,151,179,66,18,243,94,68,108,184,191,182,66,235,116,94,68,108,252,24,186,66,248,251,93,68,108,138,161,189,66,134,136,93,68,108,32,87,193,66,225,26,93,68,108,92,55,197,66,77,179,92,68,108,196,63,201,66,13,82,92,68,108,197,109,205,66,95,247,
                                               91,68,108,178,190,209,66,126,163,91,68,108,198,47,214,66,158,86,91,68,108,43,190,218,66,242,16,91,68,108,246,102,223,66,166,210,90,68,108,45,39,228,66,225,155,90,68,108,196,251,232,66,198,108,90,68,108,165,225,237,66,117,69,90,68,108,173,213,242,66,6,
                                               38,90,68,108,178,212,247,66,140,14,90,68,108,128,219,252,66,24,255,89,68,108,112,243,0,67,178,247,89,68,108,0,0,2,67,0,247,89,68,108,0,0,2,67,0,247,89,68,99,101,0,0 };

		    Path p;
            p.loadPathFromData (pathData, sizeof (pathData));
            
            return p;
        }
        
        const Path createPianoPath()
        {
             const unsigned char pathData[] = { 110,109,0,0,64,63,0,0,0,0,108,0,0,64,63,0,0,0,0,108,47,103,54,63,0,184,118,58,108,134,212,44,63,0,18,118,59,108,35,78,35,63,192,45,10,60,108,32,218,25,63,0,54,117,60,108,138,126,16,63,96,44,191,60,108,91,65,7,63,160,79,9,61,108,255,80,252,62,0,95,58,
                                                61,108,144,115,234,62,16,165,114,61,108,216,245,216,62,216,254,152,61,108,10,227,199,62,48,32,188,61,108,16,70,183,62,24,160,226,61,108,140,41,167,62,244,50,6,62,108,206,151,151,62,124,171,28,62,108,204,154,136,62,56,171,52,62,108,56,120,116,62,208,34,
                                                78,62,108,228,9,89,62,248,1,105,62,108,40,252,62,62,195,155,130,62,108,176,95,38,62,177,88,145,62,108,56,68,15,62,90,174,160,62,108,32,113,243,61,237,146,176,62,108,240,148,203,61,65,252,192,62,108,112,13,167,61,211,223,209,62,108,0,242,133,61,216,50,
                                                227,62,108,128,175,80,61,55,234,244,62,108,96,163,28,61,78,125,3,63,108,192,193,223,60,59,172,12,63,108,96,9,149,60,3,252,21,63,108,128,154,50,60,176,102,31,63,108,0,207,178,59,61,230,40,63,108,0,150,245,58,149,116,50,63,108,0,112,40,57,155,11,60,63,
                                                108,0,0,0,0,255,255,63,63,108,0,0,0,0,0,0,64,63,108,0,0,0,0,255,31,79,65,108,0,0,0,0,255,31,79,65,108,0,184,118,58,140,185,79,65,108,0,19,118,59,183,82,80,65,108,0,46,10,60,29,235,80,65,108,128,54,117,60,93,130,81,65,108,192,44,191,60,23,24,82,65,108,
                                                224,79,9,61,234,171,82,65,108,96,95,58,61,120,61,83,65,108,128,165,114,61,99,204,83,65,108,32,255,152,61,81,88,84,65,108,144,32,188,61,232,224,84,65,108,136,160,226,61,208,101,85,65,108,56,51,6,62,180,230,85,65,108,200,171,28,62,66,99,86,65,108,144,171,
                                                52,62,42,219,86,65,108,44,35,78,62,31,78,87,65,108,88,2,105,62,216,187,87,65,108,241,155,130,62,15,36,88,65,108,225,88,145,62,129,134,88,65,108,139,174,160,62,239,226,88,65,108,32,147,176,62,30,57,89,65,108,116,252,192,62,214,136,89,65,108,9,224,209,
                                                62,229,209,89,65,108,14,51,227,62,27,20,90,65,108,110,234,244,62,80,79,90,65,108,106,125,3,63,92,131,90,65,108,88,172,12,63,30,176,90,65,108,32,252,21,63,122,213,90,65,108,206,102,31,63,88,243,90,65,108,91,230,40,63,165,9,91,65,108,179,116,50,63,82,24,
                                                91,65,108,184,11,60,63,86,31,91,65,108,1,0,64,63,255,31,91,65,108,0,0,64,63,255,31,91,65,108,0,84,207,65,255,31,91,65,108,0,84,207,65,255,31,91,65,108,199,160,207,65,36,28,91,65,108,92,237,207,65,158,16,91,65,108,143,57,208,65,115,253,90,65,108,47,133,
                                                208,65,177,226,90,65,108,12,208,208,65,105,192,90,65,108,245,25,209,65,175,150,90,65,108,188,98,209,65,160,101,90,65,108,50,170,209,65,90,45,90,65,108,41,240,209,65,1,238,89,65,108,116,52,210,65,190,167,89,65,108,232,118,210,65,191,90,89,65,108,90,183,
                                                210,65,51,7,89,65,108,161,245,210,65,81,173,88,65,108,149,49,211,65,82,77,88,65,108,16,107,211,65,116,231,87,65,108,236,161,211,65,247,123,87,65,108,8,214,211,65,33,11,87,65,108,65,7,212,65,58,149,86,65,108,120,53,212,65,141,26,86,65,108,143,96,212,65,
                                                104,155,85,65,108,107,136,212,65,29,24,85,65,108,243,172,212,65,1,145,84,65,108,14,206,212,65,105,6,84,65,108,168,235,212,65,174,120,83,65,108,175,5,213,65,43,232,82,65,108,16,28,213,65,60,85,82,65,108,190,46,213,65,63,192,81,65,108,173,61,213,65,148,
                                                41,81,65,108,211,72,213,65,156,145,80,65,108,42,80,213,65,182,248,79,65,108,172,83,213,65,70,95,79,65,108,0,84,213,65,255,31,79,65,108,0,84,213,65,255,31,79,65,108,0,84,213,65,0,0,64,63,108,0,84,213,65,255,255,63,63,108,19,82,213,65,47,103,54,63,108,
                                                80,76,213,65,134,212,44,63,108,187,66,213,65,36,78,35,63,108,90,53,213,65,34,218,25,63,108,53,36,213,65,140,126,16,63,108,89,15,213,65,94,65,7,63,108,209,246,212,65,7,81,252,62,108,174,218,212,65,152,115,234,62,108,2,187,212,65,226,245,216,62,108,224,
                                                151,212,65,20,227,199,62,108,96,113,212,65,26,70,183,62,108,155,71,212,65,150,41,167,62,108,170,26,212,65,216,151,151,62,108,170,234,211,65,214,154,136,62,108,187,183,211,65,76,120,116,62,108,253,129,211,65,248,9,89,62,108,145,73,211,65,56,252,62,62,
                                                108,158,14,211,65,192,95,38,62,108,71,209,210,65,72,68,15,62,108,181,145,210,65,56,113,243,61,108,15,80,210,65,8,149,203,61,108,129,12,210,65,128,13,167,61,108,53,199,209,65,8,242,133,61,108,88,128,209,65,144,175,80,61,108,22,56,209,65,112,163,28,61,
                                                108,159,238,208,65,224,193,223,60,108,32,164,208,65,96,9,149,60,108,203,88,208,65,128,154,50,60,108,206,12,208,65,0,207,178,59,108,92,192,207,65,0,150,245,58,108,163,115,207,65,0,112,40,57,108,0,84,207,65,0,0,0,0,108,0,84,207,65,0,0,0,0,108,0,0,64,63,
                                                0,0,0,0,99,109,0,0,192,63,0,0,192,63,108,0,160,182,64,0,0,192,63,108,0,160,182,64,0,176,237,64,108,0,160,182,64,0,176,237,64,108,181,167,182,64,27,227,238,64,108,194,190,182,64,112,21,240,64,108,23,229,182,64,61,70,241,64,108,155,26,183,64,190,116,242,
                                                64,108,44,95,183,64,49,160,243,64,108,159,178,183,64,215,199,244,64,108,190,20,184,64,242,234,245,64,108,75,133,184,64,202,8,247,64,108,252,3,185,64,165,32,248,64,108,130,144,185,64,210,49,249,64,108,130,42,186,64,162,59,250,64,108,153,209,186,64,107,
                                                61,251,64,108,94,133,187,64,135,54,252,64,108,92,69,188,64,87,38,253,64,108,25,17,189,64,66,12,254,64,108,18,232,189,64,180,231,254,64,108,191,201,190,64,34,184,255,64,108,142,181,191,64,131,62,0,65,108,232,170,192,64,240,154,0,65,108,50,169,193,64,31,
                                                241,0,65,108,199,175,194,64,215,64,1,65,108,0,190,195,64,230,137,1,65,108,48,211,196,64,29,204,1,65,108,166,238,197,64,81,7,2,65,108,173,15,199,64,93,59,2,65,108,139,53,200,64,32,104,2,65,108,132,95,201,64,124,141,2,65,108,217,140,202,64,90,171,2,65,
                                                108,203,188,203,64,167,193,2,65,108,150,238,204,64,84,208,2,65,108,119,33,206,64,88,215,2,65,108,0,160,206,64,0,216,2,65,108,0,160,206,64,0,216,2,65,108,0,208,246,64,0,216,2,65,108,0,208,246,64,0,216,2,65,108,26,3,248,64,37,212,2,65,108,112,53,249,64,
                                                159,200,2,65,108,60,102,250,64,117,181,2,65,108,188,148,251,64,179,154,2,65,108,47,192,252,64,106,120,2,65,108,213,231,253,64,177,78,2,65,108,240,10,255,64,161,29,2,65,108,99,20,0,65,91,229,1,65,108,81,160,0,65,3,166,1,65,108,232,40,1,65,192,95,1,65,
                                                108,207,173,1,65,192,18,1,65,108,179,46,2,65,53,191,0,65,108,65,171,2,65,83,101,0,65,108,41,35,3,65,84,5,0,65,108,31,150,3,65,235,62,255,64,108,216,3,4,65,242,103,254,64,108,15,108,4,65,69,134,253,64,108,129,206,4,65,119,154,252,64,108,239,42,5,65,28,
                                                165,251,64,108,30,129,5,65,211,166,250,64,108,214,208,5,65,62,160,249,64,108,229,25,6,65,5,146,248,64,108,28,92,6,65,212,124,247,64,108,80,151,6,65,94,97,246,64,108,93,203,6,65,88,64,245,64,108,31,248,6,65,123,26,244,64,108,123,29,7,65,130,240,242,64,
                                                108,89,59,7,65,44,195,241,64,108,166,81,7,65,58,147,240,64,108,83,96,7,65,111,97,239,64,108,88,103,7,65,143,46,238,64,108,0,104,7,65,0,176,237,64,108,0,104,7,65,0,176,237,64,108,0,104,7,65,0,0,192,63,108,1,224,63,65,0,0,192,63,108,1,224,63,65,0,176,237,
                                                64,108,1,224,63,65,0,176,237,64,108,220,227,63,65,27,227,238,64,108,98,239,63,65,112,21,240,64,108,141,2,64,65,61,70,241,64,108,79,29,64,65,190,116,242,64,108,152,63,64,65,49,160,243,64,108,81,105,64,65,215,199,244,64,108,97,154,64,65,242,234,245,64,
                                                108,167,210,64,65,202,8,247,64,108,0,18,65,65,165,32,248,64,108,66,88,65,65,210,49,249,64,108,66,165,65,65,162,59,250,64,108,206,248,65,65,107,61,251,64,108,176,82,66,65,135,54,252,64,108,176,178,66,65,87,38,253,64,108,142,24,67,65,66,12,254,64,108,11,
                                                132,67,65,180,231,254,64,108,225,244,67,65,34,184,255,64,108,200,106,68,65,131,62,0,65,108,118,229,68,65,240,154,0,65,108,154,100,69,65,31,241,0,65,108,229,231,69,65,215,64,1,65,108,2,111,70,65,230,137,1,65,108,154,249,70,65,29,204,1,65,108,85,135,71,
                                                65,81,7,2,65,108,216,23,72,65,93,59,2,65,108,199,170,72,65,32,104,2,65,108,195,63,73,65,124,141,2,65,108,110,214,73,65,90,171,2,65,108,103,110,74,65,167,193,2,65,108,76,7,75,65,84,208,2,65,108,189,160,75,65,88,215,2,65,108,1,224,75,65,0,216,2,65,108,
                                                1,224,75,65,0,216,2,65,108,0,0,96,65,0,216,2,65,108,0,0,96,65,0,216,2,65,108,141,153,96,65,37,212,2,65,108,183,50,97,65,159,200,2,65,108,29,203,97,65,117,181,2,65,108,94,98,98,65,179,154,2,65,108,23,248,98,65,106,120,2,65,108,234,139,99,65,177,78,2,65,
                                                108,119,29,100,65,161,29,2,65,108,99,172,100,65,91,229,1,65,108,81,56,101,65,3,166,1,65,108,231,192,101,65,192,95,1,65,108,207,69,102,65,192,18,1,65,108,179,198,102,65,53,191,0,65,108,65,67,103,65,83,101,0,65,108,41,187,103,65,84,5,0,65,108,30,46,104,
                                                65,235,62,255,64,108,216,155,104,65,242,103,254,64,108,15,4,105,65,69,134,253,64,108,128,102,105,65,119,154,252,64,108,238,194,105,65,28,165,251,64,108,29,25,106,65,211,166,250,64,108,213,104,106,65,62,160,249,64,108,228,177,106,65,5,146,248,64,108,27,
                                                244,106,65,212,124,247,64,108,80,47,107,65,94,97,246,64,108,92,99,107,65,88,64,245,64,108,31,144,107,65,123,26,244,64,108,123,181,107,65,130,240,242,64,108,89,211,107,65,44,195,241,64,108,166,233,107,65,58,147,240,64,108,83,248,107,65,111,97,239,64,108,
                                                87,255,107,65,143,46,238,64,108,0,0,108,65,0,176,237,64,108,0,0,108,65,0,176,237,64,108,0,0,108,65,0,0,192,63,108,0,60,146,65,0,0,192,63,108,0,60,146,65,0,176,237,64,108,0,60,146,65,0,176,237,64,108,237,61,146,65,27,227,238,64,108,176,67,146,65,112,21,
                                                240,64,108,69,77,146,65,61,70,241,64,108,166,90,146,65,190,116,242,64,108,203,107,146,65,49,160,243,64,108,168,128,146,65,215,199,244,64,108,47,153,146,65,242,234,245,64,108,82,181,146,65,202,8,247,64,108,255,212,146,65,165,32,248,64,108,32,248,146,65,
                                                210,49,249,64,108,160,30,147,65,162,59,250,64,108,102,72,147,65,107,61,251,64,108,87,117,147,65,135,54,252,64,108,87,165,147,65,87,38,253,64,108,70,216,147,65,66,12,254,64,108,4,14,148,65,180,231,254,64,108,111,70,148,65,34,184,255,64,108,99,129,148,
                                                65,131,62,0,65,108,186,190,148,65,240,154,0,65,108,76,254,148,65,31,241,0,65,108,241,63,149,65,215,64,1,65,108,128,131,149,65,230,137,1,65,108,204,200,149,65,29,204,1,65,108,169,15,150,65,81,7,2,65,108,235,87,150,65,93,59,2,65,108,98,161,150,65,32,104,
                                                2,65,108,225,235,150,65,124,141,2,65,108,54,55,151,65,90,171,2,65,108,50,131,151,65,167,193,2,65,108,165,207,151,65,84,208,2,65,108,93,28,152,65,88,215,2,65,108,0,60,152,65,0,216,2,65,108,0,60,152,65,0,216,2,65,108,0,76,162,65,0,216,2,65,108,0,76,162,
                                                65,0,216,2,65,108,199,152,162,65,37,212,2,65,108,92,229,162,65,159,200,2,65,108,143,49,163,65,117,181,2,65,108,47,125,163,65,179,154,2,65,108,12,200,163,65,106,120,2,65,108,245,17,164,65,177,78,2,65,108,188,90,164,65,161,29,2,65,108,50,162,164,65,91,
                                                229,1,65,108,41,232,164,65,3,166,1,65,108,116,44,165,65,192,95,1,65,108,232,110,165,65,192,18,1,65,108,90,175,165,65,53,191,0,65,108,161,237,165,65,83,101,0,65,108,149,41,166,65,84,5,0,65,108,16,99,166,65,235,62,255,64,108,236,153,166,65,242,103,254,
                                                64,108,8,206,166,65,69,134,253,64,108,65,255,166,65,119,154,252,64,108,120,45,167,65,28,165,251,64,108,143,88,167,65,211,166,250,64,108,107,128,167,65,62,160,249,64,108,243,164,167,65,5,146,248,64,108,14,198,167,65,212,124,247,64,108,168,227,167,65,94,
                                                97,246,64,108,175,253,167,65,88,64,245,64,108,16,20,168,65,123,26,244,64,108,190,38,168,65,130,240,242,64,108,173,53,168,65,44,195,241,64,108,211,64,168,65,58,147,240,64,108,42,72,168,65,111,97,239,64,108,172,75,168,65,143,46,238,64,108,0,76,168,65,0,
                                                176,237,64,108,0,76,168,65,0,176,237,64,108,0,76,168,65,0,0,192,63,108,0,84,201,65,0,0,192,63,108,0,84,201,65,255,31,67,65,108,0,0,192,63,255,31,67,65,108,0,0,192,63,0,0,192,63,99,101,0,0 };

            Path p;
            p.loadPathFromData (pathData, sizeof (pathData));
            
            return p;
        }
        
        const Path createFolderPath()
        {
            const unsigned char pathData[] = { 110,109,190,198,225,67,136,228,99,66,108,190,198,225,67,136,228,99,66,108,241,193,225,67,127,229,99,66,108,40,189,225,67,97,232,99,66,108,101,184,225,67,43,237,99,66,108,171,179,225,67,220,243,99,66,108,253,174,225,67,110,252,99,66,108,94,170,225,67,
                                               220,6,100,66,108,210,165,225,67,32,19,100,66,108,90,161,225,67,50,33,100,66,108,251,156,225,67,8,49,100,66,108,182,152,225,67,152,66,100,66,108,143,148,225,67,216,85,100,66,108,136,144,225,67,187,106,100,66,108,163,140,225,67,52,129,100,66,108,228,136,
                                               225,67,52,153,100,66,108,77,133,225,67,171,178,100,66,108,223,129,225,67,138,205,100,66,108,157,126,225,67,192,233,100,66,108,138,123,225,67,58,7,101,66,108,166,120,225,67,229,37,101,66,108,245,117,225,67,174,69,101,66,108,119,115,225,67,129,102,101,
                                               66,108,46,113,225,67,72,136,101,66,108,29,111,225,67,238,170,101,66,108,67,109,225,67,93,206,101,66,108,163,107,225,67,126,242,101,66,108,61,106,225,67,57,23,102,66,108,18,105,225,67,120,60,102,66,108,35,104,225,67,35,98,102,66,108,112,103,225,67,33,
                                               136,102,66,108,251,102,225,67,91,174,102,66,108,195,102,225,67,183,212,102,66,108,190,102,225,67,136,228,102,66,108,190,102,225,67,136,228,102,66,108,190,102,225,67,136,4,110,66,108,190,102,225,67,68,177,139,66,108,190,102,225,67,68,177,139,66,108,220,
                                               102,225,67,117,196,139,66,108,57,103,225,67,155,215,139,66,108,210,103,225,67,168,234,139,66,108,168,104,225,67,144,253,139,66,108,186,105,225,67,71,16,140,66,108,8,107,225,67,193,34,140,66,108,145,108,225,67,243,52,140,66,108,83,110,225,67,208,70,140,
                                               66,108,77,112,225,67,78,88,140,66,108,128,114,225,67,97,105,140,66,108,232,116,225,67,254,121,140,66,108,132,119,225,67,26,138,140,66,108,83,122,225,67,172,153,140,66,108,83,125,225,67,169,168,140,66,108,130,128,225,67,8,183,140,66,108,222,131,225,67,
                                               191,196,140,66,108,101,135,225,67,198,209,140,66,108,20,139,225,67,20,222,140,66,108,233,142,225,67,162,233,140,66,108,226,146,225,67,104,244,140,66,108,253,150,225,67,95,254,140,66,108,54,155,225,67,129,7,141,66,108,138,159,225,67,199,15,141,66,108,
                                               248,163,225,67,46,23,141,66,108,124,168,225,67,175,29,141,66,108,20,173,225,67,72,35,141,66,108,188,177,225,67,243,39,141,66,108,113,182,225,67,175,43,141,66,108,49,187,225,67,121,46,141,66,108,248,191,225,67,78,48,141,66,108,195,196,225,67,47,49,141,
                                               66,108,190,198,225,67,68,49,141,66,108,190,198,225,67,68,49,141,66,108,190,69,232,67,68,49,141,66,108,190,113,236,67,68,49,141,66,108,190,113,236,67,68,49,141,66,108,139,118,236,67,200,48,141,66,108,84,123,236,67,88,47,141,66,108,23,128,236,67,242,44,
                                               141,66,108,209,132,236,67,154,41,141,66,108,127,137,236,67,81,37,141,66,108,30,142,236,67,26,32,141,66,108,170,146,236,67,248,25,141,66,108,34,151,236,67,239,18,141,66,108,129,155,236,67,4,11,141,66,108,198,159,236,67,60,2,141,66,108,237,163,236,67,156,
                                               248,140,66,108,244,167,236,67,42,238,140,66,108,216,171,236,67,238,226,140,66,108,152,175,236,67,238,214,140,66,108,47,179,236,67,50,202,140,66,108,157,182,236,67,195,188,140,66,108,223,185,236,67,168,174,140,66,108,242,188,236,67,235,159,140,66,108,
                                               214,191,236,67,150,144,140,66,108,135,194,236,67,177,128,140,66,108,5,197,236,67,72,112,140,66,108,78,199,236,67,100,95,140,66,108,95,201,236,67,17,78,140,66,108,57,203,236,67,90,60,140,66,108,217,204,236,67,73,42,140,66,108,63,206,236,67,235,23,140,
                                               66,108,106,207,236,67,76,5,140,66,108,89,208,236,67,119,242,139,66,108,12,209,236,67,119,223,139,66,108,129,209,236,67,91,204,139,66,108,185,209,236,67,45,185,139,66,108,190,209,236,67,68,177,139,66,108,190,209,236,67,68,177,139,66,108,190,209,236,67,
                                               136,4,110,66,108,190,209,236,67,136,4,110,66,108,160,209,236,67,37,222,109,66,108,67,209,236,67,218,183,109,66,108,170,208,236,67,193,145,109,66,108,212,207,236,67,241,107,109,66,108,194,206,236,67,131,70,109,66,108,116,205,236,67,142,33,109,66,108,235,
                                               203,236,67,42,253,108,66,108,41,202,236,67,112,217,108,66,108,47,200,236,67,116,182,108,66,108,252,197,236,67,78,148,108,66,108,148,195,236,67,21,115,108,66,108,248,192,236,67,220,82,108,66,108,41,190,236,67,184,51,108,66,108,41,187,236,67,190,21,108,
                                               66,108,250,183,236,67,1,249,107,66,108,158,180,236,67,146,221,107,66,108,24,177,236,67,133,195,107,66,108,104,173,236,67,232,170,107,66,108,147,169,236,67,205,147,107,66,108,154,165,236,67,65,126,107,66,108,127,161,236,67,83,106,107,66,108,71,157,236,
                                               67,15,88,107,66,108,242,152,236,67,129,71,107,66,108,132,148,236,67,180,56,107,66,108,0,144,236,67,177,43,107,66,108,104,139,236,67,129,32,107,66,108,192,134,236,67,42,23,107,66,108,11,130,236,67,178,15,107,66,108,75,125,236,67,31,10,107,66,108,132,120,
                                               236,67,116,6,107,66,108,185,115,236,67,178,4,107,66,108,190,113,236,67,136,4,107,66,108,190,113,236,67,136,4,107,66,108,190,165,232,67,136,4,107,66,108,190,165,232,67,136,228,102,66,108,190,165,232,67,136,228,102,66,108,160,165,232,67,37,190,102,66,108,
                                               67,165,232,67,218,151,102,66,108,170,164,232,67,193,113,102,66,108,212,163,232,67,241,75,102,66,108,194,162,232,67,131,38,102,66,108,116,161,232,67,142,1,102,66,108,235,159,232,67,42,221,101,66,108,41,158,232,67,112,185,101,66,108,47,156,232,67,116,150,
                                               101,66,108,252,153,232,67,78,116,101,66,108,148,151,232,67,21,83,101,66,108,248,148,232,67,220,50,101,66,108,41,146,232,67,184,19,101,66,108,41,143,232,67,190,245,100,66,108,250,139,232,67,1,217,100,66,108,158,136,232,67,146,189,100,66,108,24,133,232,
                                               67,133,163,100,66,108,104,129,232,67,232,138,100,66,108,147,125,232,67,205,115,100,66,108,154,121,232,67,65,94,100,66,108,127,117,232,67,83,74,100,66,108,71,113,232,67,15,56,100,66,108,242,108,232,67,129,39,100,66,108,132,104,232,67,180,24,100,66,108,
                                               0,100,232,67,177,11,100,66,108,104,95,232,67,129,0,100,66,108,192,90,232,67,42,247,99,66,108,11,86,232,67,178,239,99,66,108,75,81,232,67,31,234,99,66,108,132,76,232,67,116,230,99,66,108,185,71,232,67,178,228,99,66,108,190,69,232,67,136,228,99,66,108,
                                               190,69,232,67,136,228,99,66,108,190,198,225,67,136,228,99,66,99,109,190,38,226,67,136,228,105,66,108,190,229,231,67,136,228,105,66,108,190,229,231,67,136,4,110,66,108,190,229,231,67,136,4,110,66,108,220,229,231,67,235,42,110,66,108,57,230,231,67,54,81,
                                               110,66,108,210,230,231,67,79,119,110,66,108,168,231,231,67,31,157,110,66,108,186,232,231,67,142,194,110,66,108,8,234,231,67,130,231,110,66,108,145,235,231,67,230,11,111,66,108,83,237,231,67,161,47,111,66,108,77,239,231,67,156,82,111,66,108,128,241,231,
                                               67,194,116,111,66,108,232,243,231,67,252,149,111,66,108,132,246,231,67,53,182,111,66,108,83,249,231,67,88,213,111,66,108,83,252,231,67,82,243,111,66,108,130,255,231,67,16,16,112,66,108,222,2,232,67,126,43,112,66,108,101,6,232,67,140,69,112,66,108,20,
                                               10,232,67,40,94,112,66,108,233,13,232,67,68,117,112,66,108,226,17,232,67,207,138,112,66,108,253,21,232,67,189,158,112,66,108,54,26,232,67,1,177,112,66,108,138,30,232,67,143,193,112,66,108,248,34,232,67,92,208,112,66,108,124,39,232,67,95,221,112,66,108,
                                               20,44,232,67,144,232,112,66,108,188,48,232,67,231,241,112,66,108,113,53,232,67,94,249,112,66,108,49,58,232,67,241,254,112,66,108,248,62,232,67,157,2,113,66,108,195,67,232,67,94,4,113,66,108,190,69,232,67,136,4,113,66,108,190,69,232,67,136,4,113,66,108,
                                               190,17,236,67,136,4,113,66,108,190,17,236,67,68,49,138,66,108,190,69,232,67,68,49,138,66,108,190,38,226,67,68,49,138,66,108,190,38,226,67,136,4,110,66,108,190,38,226,67,136,228,105,66,99,101,0,0 };

            Path p;
            p.loadPathFromData (pathData, sizeof (pathData));
            
            return p;
        }
        
        const Path createMagnifyingGlassPath()
        {
            const unsigned char pathData[] = { 110,109,0,0,72,66,32,23,110,68,108,0,0,72,66,32,23,110,68,108,17,1,62,66,32,27,110,68,108,135,8,52,66,29,39,110,68,108,196,28,42,66,15,59,110,68,108,33,68,32,66,233,86,110,68,108,235,132,22,66,155,122,110,68,108,94,229,12,66,12,166,110,68,108,162,107,
                                               3,66,34,217,110,68,108,143,59,244,65,187,19,111,68,108,134,3,226,65,178,85,111,68,108,210,58,208,65,220,158,111,68,108,210,236,190,65,12,239,111,68,108,154,36,174,65,13,70,112,68,108,232,236,157,65,168,163,112,68,108,26,80,142,65,161,7,113,68,108,92,
                                               176,126,65,185,113,113,68,108,116,29,98,65,170,225,113,68,108,192,249,70,65,46,87,114,68,108,164,86,45,65,249,209,114,68,108,124,68,21,65,189,81,115,68,108,112,165,253,64,40,214,115,68,108,112,31,212,64,230,94,116,68,108,112,17,174,64,158,235,116,68,
                                               108,224,147,139,64,247,123,117,68,108,144,121,89,64,148,15,118,68,108,224,63,35,64,24,166,118,68,108,96,58,233,63,33,63,119,68,108,224,94,155,63,78,218,119,68,108,128,62,58,63,59,119,120,68,108,0,140,186,62,132,21,121,68,108,0,66,0,62,196,180,121,68,
                                               108,0,32,49,60,149,84,122,68,108,0,0,0,0,32,151,122,68,108,0,0,0,0,32,151,122,68,108,0,0,0,0,32,151,122,68,108,0,240,127,61,15,55,123,68,108,0,202,127,62,152,214,123,68,108,0,187,15,63,84,117,124,68,108,64,38,127,63,223,18,125,68,108,64,246,198,63,210,
                                               174,125,68,108,160,236,14,64,203,72,126,68,108,64,2,66,64,103,224,126,68,108,80,155,124,64,69,117,127,68,108,48,73,159,64,131,3,128,68,108,144,222,195,64,165,74,128,68,108,104,246,235,64,221,143,128,68,108,136,187,11,65,254,210,128,68,108,88,34,35,65,
                                               221,19,129,68,108,172,32,60,65,80,82,129,68,108,124,166,86,65,48,142,129,68,108,216,162,114,65,86,199,129,68,108,236,1,136,65,157,253,129,68,108,87,91,151,65,227,48,130,68,108,218,83,167,65,8,97,130,68,108,64,225,183,65,235,141,130,68,108,239,248,200,
                                               65,113,183,130,68,108,247,143,218,65,127,221,130,68,108,24,155,236,65,252,255,130,68,108,198,14,255,65,212,30,131,68,108,153,239,8,66,240,57,131,68,108,42,128,18,66,66,81,131,68,108,246,50,28,66,184,100,131,68,108,200,1,38,66,72,116,131,68,108,91,230,
                                               47,66,231,127,131,68,108,90,218,57,66,142,135,131,68,108,102,215,67,66,55,139,131,68,108,255,255,71,66,144,139,131,68,108,0,0,72,66,144,139,131,68,108,255,255,71,66,144,139,131,68,108,210,254,81,66,111,137,131,68,108,10,247,91,66,79,131,131,68,108,71,
                                               226,101,66,53,121,131,68,108,48,186,111,66,39,107,131,68,108,120,120,121,66,46,89,131,68,108,114,139,129,66,86,67,131,68,108,166,71,134,66,172,41,131,68,108,207,237,138,66,64,12,131,68,108,246,122,143,66,38,235,130,68,108,47,236,147,66,116,198,130,68,
                                               108,164,62,152,66,63,158,130,68,108,145,111,156,66,163,114,130,68,108,70,124,160,66,186,67,130,68,108,0,49,162,66,112,46,130,68,108,0,49,162,66,112,46,130,68,108,0,134,166,66,144,115,130,68,108,0,106,163,66,80,165,130,68,108,0,145,231,66,16,216,134,68,
                                               108,1,60,248,66,111,205,133,68,108,0,20,180,66,159,154,129,68,108,0,241,176,66,223,204,129,68,108,0,9,173,66,159,142,129,68,108,0,9,173,66,159,142,129,68,108,154,91,176,66,218,82,129,68,108,88,125,179,66,128,20,129,68,108,57,108,182,66,185,211,128,68,
                                               108,92,38,185,66,174,144,128,68,108,4,170,187,66,138,75,128,68,108,149,245,189,66,121,4,128,68,108,149,7,192,66,84,119,127,68,108,178,222,193,66,148,226,126,68,108,191,121,195,66,18,75,126,68,108,180,215,196,66,47,177,125,68,108,178,247,197,66,77,21,
                                               125,68,108,1,217,198,66,209,119,124,68,108,16,123,199,66,31,217,123,68,108,119,221,199,66,157,57,123,68,108,248,255,199,66,176,153,122,68,108,0,0,200,66,32,151,122,68,108,0,0,200,66,32,151,122,68,108,0,0,200,66,32,151,122,68,108,2,224,199,66,49,247,121,
                                               68,108,28,128,199,66,169,87,121,68,108,138,224,198,66,236,184,120,68,108,180,1,198,66,98,27,120,68,108,41,228,196,66,111,127,119,68,108,158,136,195,66,118,229,118,68,108,242,239,193,66,218,77,118,68,108,42,27,192,66,253,184,117,68,108,116,11,190,66,61,
                                               39,117,68,108,30,194,187,66,247,152,116,68,108,162,64,185,66,135,14,116,68,108,154,136,182,66,69,136,115,68,108,193,155,179,66,136,6,115,68,108,248,123,176,66,161,137,114,68,108,62,43,173,66,226,17,114,68,108,180,171,169,66,150,159,113,68,108,148,255,
                                               165,66,7,51,113,68,108,58,41,162,66,123,204,112,68,108,25,43,158,66,50,108,112,68,108,192,7,154,66,107,18,112,68,108,212,193,149,66,95,191,111,68,108,18,92,145,66,67,115,111,68,108,74,217,140,66,72,46,111,68,108,94,60,136,66,154,240,110,68,108,67,136,
                                               131,66,96,186,110,68,108,246,127,125,66,189,139,110,68,108,42,205,115,66,208,100,110,68,108,86,254,105,66,176,69,110,68,108,195,25,96,66,114,46,110,68,108,196,37,86,66,36,31,110,68,108,183,40,76,66,209,23,110,68,108,0,0,72,66,32,23,110,68,108,0,0,72,
                                               66,32,23,110,68,99,109,0,0,72,66,0,141,112,68,108,0,0,72,66,0,141,112,68,108,80,7,80,66,53,144,112,68,108,126,9,88,66,214,153,112,68,108,105,1,96,66,218,169,112,68,108,248,233,103,66,57,192,112,68,108,28,190,111,66,228,220,112,68,108,211,120,119,66,200,
                                               255,112,68,108,41,21,127,66,208,40,113,68,108,33,71,131,66,224,87,113,68,108,169,239,134,66,219,140,113,68,108,216,129,138,66,158,199,113,68,108,98,251,141,66,6,8,114,68,108,16,90,145,66,231,77,114,68,108,186,155,148,66,21,153,114,68,108,72,190,151,66,
                                               97,233,114,68,108,188,191,154,66,151,62,115,68,108,40,158,157,66,128,152,115,68,108,181,87,160,66,227,246,115,68,108,166,234,162,66,131,89,116,68,108,86,85,165,66,34,192,116,68,108,54,150,167,66,125,42,117,68,108,218,171,169,66,81,152,117,68,108,232,
                                               148,171,66,87,9,118,68,108,40,80,173,66,71,125,118,68,108,128,220,174,66,215,243,118,68,108,242,56,176,66,187,108,119,68,108,157,100,177,66,165,231,119,68,108,196,94,178,66,72,100,120,68,108,197,38,179,66,82,226,120,68,108,33,188,179,66,117,97,121,68,
                                               108,120,30,180,66,93,225,121,68,108,140,77,180,66,186,97,122,68,108,0,82,180,66,32,151,122,68,108,0,82,180,66,32,151,122,68,108,0,82,180,66,32,151,122,68,108,82,56,180,66,149,23,123,68,108,78,235,179,66,184,151,123,68,108,41,107,179,66,55,23,124,68,108,
                                               50,184,178,66,192,149,124,68,108,220,210,177,66,2,19,125,68,108,188,187,176,66,173,142,125,68,108,129,115,175,66,115,8,126,68,108,0,251,173,66,4,128,126,68,108,40,83,172,66,21,245,126,68,108,9,125,170,66,91,103,127,68,108,208,121,168,66,140,214,127,68,
                                               108,199,74,166,66,49,33,128,68,108,82,241,163,66,76,85,128,68,108,244,110,161,66,117,135,128,68,108,71,197,158,66,140,183,128,68,108,255,245,155,66,115,229,128,68,108,233,2,153,66,11,17,129,68,108,231,237,149,66,58,58,129,68,108,243,184,146,66,229,96,
                                               129,68,108,25,102,143,66,243,132,129,68,108,123,247,139,66,78,166,129,68,108,74,111,136,66,223,196,129,68,108,201,207,132,66,147,224,129,68,108,74,27,129,66,88,249,129,68,108,86,168,122,66,31,15,130,68,108,174,249,114,66,218,33,130,68,108,135,47,107,
                                               66,124,49,130,68,108,221,78,99,66,252,61,130,68,108,186,92,91,66,82,71,130,68,108,51,94,83,66,120,77,130,68,108,103,88,75,66,105,80,130,68,108,255,255,71,66,176,80,130,68,108,0,0,72,66,176,80,130,68,108,255,255,71,66,176,80,130,68,108,175,248,63,66,21,
                                               79,130,68,108,130,246,55,66,69,74,130,68,108,151,254,47,66,67,66,130,68,108,9,22,40,66,19,55,130,68,108,229,65,32,66,190,40,130,68,108,48,135,24,66,76,23,130,68,108,218,234,16,66,200,2,130,68,108,194,113,9,66,64,235,129,68,108,177,32,2,66,195,208,129,
                                               68,108,170,248,245,65,97,179,129,68,108,129,18,232,65,45,147,129,68,108,201,151,218,65,61,112,129,68,108,36,145,205,65,165,74,129,68,108,233,6,193,65,128,34,129,68,108,28,1,181,65,229,247,128,68,108,110,135,169,65,240,202,128,68,108,56,161,158,65,191,
                                               155,128,68,108,116,85,148,65,111,106,128,68,108,180,170,138,65,31,55,128,68,108,44,167,129,65,242,1,128,68,108,60,161,114,65,15,150,127,68,108,200,88,99,65,9,37,127,68,108,192,126,85,65,25,177,126,68,108,252,27,73,65,137,58,126,68,108,108,56,62,65,165,
                                               193,125,68,108,12,219,52,65,186,70,125,68,108,216,9,45,65,24,202,124,68,108,204,201,38,65,13,76,124,68,108,236,30,34,65,234,204,123,68,108,56,12,31,65,2,77,123,68,108,156,147,29,65,165,204,122,68,108,0,112,29,65,33,151,122,68,108,0,112,29,65,32,151,122,
                                               68,108,0,112,29,65,32,151,122,68,108,220,61,30,65,171,22,122,68,108,88,166,32,65,136,150,121,68,108,236,167,36,65,9,23,121,68,108,8,64,42,65,129,152,120,68,108,20,107,49,65,63,27,120,68,108,128,36,58,65,148,159,119,68,108,180,102,68,65,207,37,119,68,
                                               108,32,43,80,65,62,174,118,68,108,56,106,93,65,46,57,118,68,108,136,27,108,65,233,198,117,68,108,168,53,124,65,184,87,117,68,108,38,215,134,65,227,235,116,68,108,32,61,144,65,175,131,116,68,108,194,70,154,65,94,31,116,68,108,158,237,164,65,49,191,115,
                                               68,108,226,42,176,65,101,99,115,68,108,97,247,187,65,52,12,115,68,108,137,75,200,65,215,185,114,68,108,123,31,213,65,130,108,114,68,108,254,106,226,65,104,36,114,68,108,147,37,240,65,181,225,113,68,108,113,70,254,65,148,164,113,68,108,70,98,6,66,46,109,
                                               113,68,108,79,203,13,66,164,59,113,68,108,151,89,21,66,23,16,113,68,108,70,8,29,66,163,234,112,68,108,116,210,36,66,96,203,112,68,108,36,179,44,66,98,178,112,68,108,75,165,52,66,184,159,112,68,108,212,163,60,66,110,147,112,68,108,162,169,68,66,141,141,
                                               112,68,108,0,0,72,66,0,141,112,68,108,0,0,72,66,0,141,112,68,99,101,0,0 };
            
            Path p;
            p.loadPathFromData (pathData, sizeof (pathData));
            
            return p;
        }


        const Path createBurgerPath()
        {
            const unsigned char pathData[] = { 110,109,0,0,0,0,84,64,126,68,108,0,0,32,66,84,64,126,68,109,0,0,0,0,151,11,129,68,108,0,0,32,66,151,11,129,68,109,0,0,0,0,4,247,130,68,108,0,0,32,66,4,247,130,68,101,0,0 };

            Path p;
            p.loadPathFromData (pathData, sizeof (pathData));

            return p;
        }

        const Path createShortBurgerPath()
        {
            const unsigned char pathData[] = { 110,109,0,0,0,0,46,151,127,68,108,0,0,32,66,46,151,127,68,109,0,0,0,0,151,11,129,68,108,0,0,32,66,151,11,129,68,109,0,0,0,0,151,75,130,68,108,0,0,32,66,151,75,130,68,101,0,0 };
            Path p;
            p.loadPathFromData (pathData, sizeof (pathData));

            return p;
        }

        const Path createOptionsPath()
        {
            const unsigned char pathData[] = { 110,109,0,40,135,65,151,75,130,68,108,0,0,32,66,151,75,130,68,109,0,0,0,0,151,75,130,68,108,0,80,62,65,151,75,130,68,109,252,38,135,65,151,75,130,68,108,252,38,135,65,151,75,130,68,108,150,32,135,65,151,79,130,68,108,104,13,135,65,148,83,130,68,108,126,
                                               237,134,65,139,87,130,68,108,237,192,134,65,124,91,130,68,108,209,135,134,65,98,95,130,68,108,79,66,134,65,59,99,130,68,108,147,240,133,65,6,103,130,68,108,209,146,133,65,190,106,130,68,108,70,41,133,65,99,110,130,68,108,53,180,132,65,242,113,130,68,
                                               108,233,51,132,65,104,117,130,68,108,180,168,131,65,195,120,130,68,108,239,18,131,65,1,124,130,68,108,250,114,130,65,33,127,130,68,108,60,201,129,65,31,130,130,68,108,32,22,129,65,250,132,130,68,108,26,90,128,65,177,135,130,68,108,67,43,127,65,66,138,
                                               130,68,108,105,146,125,65,170,140,130,68,108,172,234,123,65,232,142,130,68,108,26,53,122,65,252,144,130,68,108,205,114,120,65,227,146,130,68,108,228,164,118,65,156,148,130,68,108,134,204,116,65,39,150,130,68,108,225,234,114,65,130,151,130,68,108,43,1,
                                               113,65,173,152,130,68,108,156,16,111,65,166,153,130,68,108,114,26,109,65,109,154,130,68,108,238,31,107,65,2,155,130,68,108,85,34,105,65,100,155,130,68,108,236,34,103,65,147,155,130,68,108,248,77,102,65,151,155,130,68,108,248,77,102,65,151,155,130,68,
                                               108,248,77,102,65,151,155,130,68,108,46,78,100,65,125,155,130,68,108,173,79,98,65,49,155,130,68,108,185,83,96,65,177,154,130,68,108,153,91,94,65,255,153,130,68,108,142,104,92,65,26,153,130,68,108,216,123,90,65,4,152,130,68,108,179,150,88,65,189,150,130,
                                               68,108,84,186,86,65,70,149,130,68,108,237,231,84,65,160,147,130,68,108,168,32,83,65,204,145,130,68,108,168,101,81,65,203,143,130,68,108,9,184,79,65,158,141,130,68,108,221,24,78,65,71,139,130,68,108,47,137,76,65,199,136,130,68,108,254,9,75,65,32,134,130,
                                               68,108,63,156,73,65,84,131,130,68,108,221,64,72,65,99,128,130,68,108,180,248,70,65,82,125,130,68,108,152,196,69,65,32,122,130,68,108,78,165,68,65,208,118,130,68,108,142,155,67,65,101,115,130,68,108,1,168,66,65,225,111,130,68,108,68,203,65,65,69,108,130,
                                               68,108,227,5,65,65,148,104,130,68,108,93,88,64,65,209,100,130,68,108,34,195,63,65,253,96,130,68,108,143,70,63,65,28,93,130,68,108,246,226,62,65,48,89,130,68,108,150,152,62,65,59,85,130,68,108,158,103,62,65,64,81,130,68,108,47,80,62,65,65,77,130,68,108,
                                               248,77,62,65,151,75,130,68,108,248,77,62,65,151,75,130,68,108,248,77,62,65,151,75,130,68,108,196,90,62,65,151,71,130,68,108,32,129,62,65,154,67,130,68,108,244,192,62,65,162,63,130,68,108,23,26,63,65,178,59,130,68,108,79,140,63,65,204,55,130,68,108,84,
                                               23,64,65,243,51,130,68,108,204,186,64,65,40,48,130,68,108,80,118,65,65,112,44,130,68,108,102,73,66,65,203,40,130,68,108,136,51,67,65,60,37,130,68,108,33,52,68,65,198,33,130,68,108,140,74,69,65,107,30,130,68,108,22,118,70,65,45,27,130,68,108,0,182,71,
                                               65,13,24,130,68,108,127,9,73,65,15,21,130,68,108,183,111,74,65,52,18,130,68,108,196,231,75,65,125,15,130,68,108,182,112,77,65,236,12,130,68,108,144,9,79,65,132,10,130,68,108,78,177,80,65,70,8,130,68,108,224,102,82,65,50,6,130,68,108,47,41,84,65,75,4,
                                               130,68,108,25,247,85,65,146,2,130,68,108,120,207,87,65,7,1,130,68,108,29,177,89,65,172,255,129,68,108,212,154,91,65,129,254,129,68,108,100,139,93,65,136,253,129,68,108,143,129,95,65,193,252,129,68,108,20,124,97,65,44,252,129,68,108,174,121,99,65,202,
                                               251,129,68,108,23,121,101,65,155,251,129,68,108,248,77,102,65,151,251,129,68,108,248,77,102,65,151,251,129,68,108,248,77,102,65,151,251,129,68,108,193,77,104,65,177,251,129,68,108,67,76,106,65,253,251,129,68,108,55,72,108,65,125,252,129,68,108,88,64,
                                               110,65,47,253,129,68,108,99,51,112,65,20,254,129,68,108,24,32,114,65,42,255,129,68,108,62,5,116,65,113,0,130,68,108,157,225,117,65,232,1,130,68,108,4,180,119,65,142,3,130,68,108,73,123,121,65,98,5,130,68,108,74,54,123,65,99,7,130,68,108,232,227,124,65,
                                               144,9,130,68,108,20,131,126,65,231,11,130,68,108,97,9,128,65,103,14,130,68,108,250,200,128,65,14,17,130,68,108,217,127,129,65,218,19,130,68,108,138,45,130,65,203,22,130,68,108,158,209,130,65,220,25,130,68,108,172,107,131,65,14,29,130,68,108,81,251,131,
                                               65,94,32,130,68,108,49,128,132,65,201,35,130,68,108,247,249,132,65,77,39,130,68,108,86,104,133,65,233,42,130,68,108,6,203,133,65,154,46,130,68,108,201,33,134,65,93,50,130,68,108,103,108,134,65,49,54,130,68,108,176,170,134,65,18,58,130,68,108,125,220,
                                               134,65,254,61,130,68,108,173,1,135,65,243,65,130,68,108,40,26,135,65,238,69,130,68,108,224,37,135,65,237,73,130,68,108,252,38,135,65,151,75,130,68,108,252,38,135,65,151,75,130,68,99,109,255,255,239,65,151,107,128,68,108,0,0,32,66,151,107,128,68,109,0,
                                               0,0,0,151,107,128,68,108,0,0,200,65,151,107,128,68,109,0,0,240,65,151,107,128,68,108,0,0,240,65,151,107,128,68,108,154,249,239,65,151,111,128,68,108,108,230,239,65,148,115,128,68,108,130,198,239,65,139,119,128,68,108,241,153,239,65,124,123,128,68,108,
                                               213,96,239,65,98,127,128,68,108,83,27,239,65,59,131,128,68,108,151,201,238,65,6,135,128,68,108,213,107,238,65,190,138,128,68,108,74,2,238,65,99,142,128,68,108,57,141,237,65,242,145,128,68,108,237,12,237,65,104,149,128,68,108,184,129,236,65,195,152,128,
                                               68,108,243,235,235,65,1,156,128,68,108,254,75,235,65,33,159,128,68,108,64,162,234,65,31,162,128,68,108,36,239,233,65,250,164,128,68,108,30,51,233,65,177,167,128,68,108,165,110,232,65,66,170,128,68,108,56,162,231,65,170,172,128,68,108,90,206,230,65,232,
                                               174,128,68,108,145,243,229,65,252,176,128,68,108,107,18,229,65,227,178,128,68,108,118,43,228,65,156,180,128,68,108,71,63,227,65,39,182,128,68,108,117,78,226,65,130,183,128,68,108,153,89,225,65,173,184,128,68,108,82,97,224,65,166,185,128,68,108,61,102,
                                               223,65,109,186,128,68,108,251,104,222,65,2,187,128,68,108,46,106,221,65,100,187,128,68,108,122,106,220,65,147,187,128,68,108,0,0,220,65,151,187,128,68,108,0,0,220,65,151,187,128,68,108,0,0,220,65,151,187,128,68,108,27,0,219,65,125,187,128,68,108,218,
                                               0,218,65,49,187,128,68,108,225,2,217,65,177,186,128,68,108,208,6,216,65,255,185,128,68,108,75,13,215,65,26,185,128,68,108,240,22,214,65,4,184,128,68,108,93,36,213,65,189,182,128,68,108,46,54,212,65,70,181,128,68,108,250,76,211,65,160,179,128,68,108,88,
                                               105,210,65,204,177,128,68,108,216,139,209,65,203,175,128,68,108,8,181,208,65,158,173,128,68,108,115,229,207,65,71,171,128,68,108,156,29,207,65,199,168,128,68,108,3,94,206,65,32,166,128,68,108,36,167,205,65,84,163,128,68,108,114,249,204,65,99,160,128,
                                               68,108,94,85,204,65,82,157,128,68,108,80,187,203,65,32,154,128,68,108,171,43,203,65,208,150,128,68,108,203,166,202,65,101,147,128,68,108,4,45,202,65,225,143,128,68,108,166,190,201,65,69,140,128,68,108,245,91,201,65,148,136,128,68,108,50,5,201,65,209,
                                               132,128,68,108,149,186,200,65,253,128,128,68,108,76,124,200,65,28,125,128,68,108,127,74,200,65,48,121,128,68,108,79,37,200,65,59,117,128,68,108,211,12,200,65,64,113,128,68,108,27,1,200,65,65,109,128,68,108,0,0,200,65,151,107,128,68,108,0,0,200,65,151,
                                               107,128,68,108,0,0,200,65,151,107,128,68,108,102,6,200,65,151,103,128,68,108,148,25,200,65,154,99,128,68,108,126,57,200,65,162,95,128,68,108,15,102,200,65,178,91,128,68,108,43,159,200,65,204,87,128,68,108,174,228,200,65,243,83,128,68,108,106,54,201,65,
                                               40,80,128,68,108,44,148,201,65,112,76,128,68,108,183,253,201,65,203,72,128,68,108,200,114,202,65,60,69,128,68,108,20,243,202,65,198,65,128,68,108,74,126,203,65,107,62,128,68,108,15,20,204,65,45,59,128,68,108,4,180,204,65,13,56,128,68,108,195,93,205,65,
                                               15,53,128,68,108,224,16,206,65,52,50,128,68,108,230,204,206,65,125,47,128,68,108,95,145,207,65,236,44,128,68,108,204,93,208,65,132,42,128,68,108,171,49,209,65,70,40,128,68,108,116,12,210,65,50,38,128,68,108,155,237,210,65,75,36,128,68,108,145,212,211,
                                               65,146,34,128,68,108,192,192,212,65,7,33,128,68,108,147,177,213,65,172,31,128,68,108,110,166,214,65,129,30,128,68,108,182,158,215,65,136,29,128,68,108,204,153,216,65,193,28,128,68,108,14,151,217,65,44,28,128,68,108,219,149,218,65,202,27,128,68,108,144,
                                               149,219,65,155,27,128,68,108,0,0,220,65,151,27,128,68,108,0,0,220,65,151,27,128,68,108,0,0,220,65,151,27,128,68,108,229,255,220,65,177,27,128,68,108,38,255,221,65,253,27,128,68,108,32,253,222,65,125,28,128,68,108,48,249,223,65,47,29,128,68,108,181,242,
                                               224,65,20,30,128,68,108,16,233,225,65,42,31,128,68,108,163,219,226,65,113,32,128,68,108,210,201,227,65,232,33,128,68,108,6,179,228,65,142,35,128,68,108,169,150,229,65,98,37,128,68,108,41,116,230,65,99,39,128,68,108,248,74,231,65,144,41,128,68,108,142,
                                               26,232,65,231,43,128,68,108,101,226,232,65,103,46,128,68,108,254,161,233,65,14,49,128,68,108,221,88,234,65,218,51,128,68,108,142,6,235,65,203,54,128,68,108,162,170,235,65,220,57,128,68,108,176,68,236,65,14,61,128,68,108,85,212,236,65,94,64,128,68,108,
                                               53,89,237,65,201,67,128,68,108,251,210,237,65,77,71,128,68,108,90,65,238,65,233,74,128,68,108,10,164,238,65,154,78,128,68,108,205,250,238,65,93,82,128,68,108,107,69,239,65,49,86,128,68,108,180,131,239,65,18,90,128,68,108,129,181,239,65,254,93,128,68,
                                               108,177,218,239,65,243,97,128,68,108,44,243,239,65,238,101,128,68,108,228,254,239,65,237,105,128,68,108,0,0,240,65,151,107,128,68,108,0,0,240,65,151,107,128,68,99,109,0,0,112,65,46,23,125,68,108,0,0,32,66,46,23,125,68,109,0,0,0,0,46,23,125,68,108,0,0,
                                               32,65,46,23,125,68,109,0,0,112,65,46,23,125,68,108,0,0,112,65,46,23,125,68,108,52,243,111,65,45,31,125,68,108,216,204,111,65,39,39,125,68,108,4,141,111,65,23,47,125,68,108,226,51,111,65,247,54,125,68,108,170,193,110,65,196,62,125,68,108,166,54,110,65,
                                               118,70,125,68,108,46,147,109,65,11,78,125,68,108,170,215,108,65,125,85,125,68,108,148,4,108,65,198,92,125,68,108,114,26,107,65,227,99,125,68,108,218,25,106,65,207,106,125,68,108,112,3,105,65,134,113,125,68,108,230,215,103,65,2,120,125,68,108,253,151,
                                               102,65,65,126,125,68,108,128,68,101,65,62,132,125,68,108,72,222,99,65,245,137,125,68,108,60,102,98,65,98,143,125,68,108,75,221,96,65,131,148,125,68,108,113,68,95,65,83,153,125,68,108,180,156,93,65,209,157,125,68,108,34,231,91,65,248,161,125,68,108,213,
                                               36,90,65,198,165,125,68,108,236,86,88,65,57,169,125,68,108,142,126,86,65,78,172,125,68,108,233,156,84,65,4,175,125,68,108,51,179,82,65,89,177,125,68,108,164,194,80,65,76,179,125,68,108,122,204,78,65,218,180,125,68,108,246,209,76,65,4,182,125,68,108,93,
                                               212,74,65,199,182,125,68,108,244,212,72,65,37,183,125,68,108,0,0,72,65,46,183,125,68,108,0,0,72,65,46,183,125,68,108,0,0,72,65,46,183,125,68,108,54,0,70,65,251,182,125,68,108,181,1,68,65,97,182,125,68,108,193,5,66,65,98,181,125,68,108,161,13,64,65,254,
                                               179,125,68,108,150,26,62,65,53,178,125,68,108,224,45,60,65,9,176,125,68,108,187,72,58,65,123,173,125,68,108,92,108,56,65,141,170,125,68,108,245,153,54,65,64,167,125,68,108,176,210,52,65,152,163,125,68,108,176,23,51,65,149,159,125,68,108,17,106,49,65,
                                               60,155,125,68,108,229,202,47,65,142,150,125,68,108,55,59,46,65,142,145,125,68,108,6,188,44,65,64,140,125,68,108,71,78,43,65,167,134,125,68,108,229,242,41,65,199,128,125,68,108,188,170,40,65,163,122,125,68,108,160,118,39,65,64,116,125,68,108,86,87,38,
                                               65,161,109,125,68,108,150,77,37,65,203,102,125,68,108,9,90,36,65,193,95,125,68,108,76,125,35,65,138,88,125,68,108,235,183,34,65,40,81,125,68,108,101,10,34,65,162,73,125,68,108,42,117,33,65,251,65,125,68,108,151,248,32,65,56,58,125,68,108,254,148,32,65,
                                               96,50,125,68,108,158,74,32,65,118,42,125,68,108,166,25,32,65,127,34,125,68,108,55,2,32,65,130,26,125,68,108,0,0,32,65,46,23,125,68,108,0,0,32,65,46,23,125,68,108,0,0,32,65,46,23,125,68,108,204,12,32,65,47,15,125,68,108,40,51,32,65,53,7,125,68,108,252,
                                               114,32,65,69,255,124,68,108,31,204,32,65,100,247,124,68,108,87,62,33,65,152,239,124,68,108,92,201,33,65,229,231,124,68,108,212,108,34,65,81,224,124,68,108,88,40,35,65,223,216,124,68,108,110,251,35,65,150,209,124,68,108,144,229,36,65,121,202,124,68,108,
                                               41,230,37,65,141,195,124,68,108,148,252,38,65,214,188,124,68,108,30,40,40,65,89,182,124,68,108,8,104,41,65,27,176,124,68,108,135,187,42,65,30,170,124,68,108,191,33,44,65,103,164,124,68,108,204,153,45,65,249,158,124,68,108,190,34,47,65,217,153,124,68,
                                               108,152,187,48,65,8,149,124,68,108,86,99,50,65,139,144,124,68,108,232,24,52,65,100,140,124,68,108,55,219,53,65,150,136,124,68,108,33,169,55,65,35,133,124,68,108,128,129,57,65,14,130,124,68,108,37,99,59,65,88,127,124,68,108,220,76,61,65,3,125,124,68,108,
                                               108,61,63,65,16,123,124,68,108,151,51,65,65,130,121,124,68,108,28,46,67,65,88,120,124,68,108,182,43,69,65,149,119,124,68,108,31,43,71,65,55,119,124,68,108,0,0,72,65,46,119,124,68,108,0,0,72,65,46,119,124,68,108,0,0,72,65,46,119,124,68,108,201,255,73,
                                               65,97,119,124,68,108,75,254,75,65,251,119,124,68,108,63,250,77,65,250,120,124,68,108,96,242,79,65,94,122,124,68,108,107,229,81,65,39,124,124,68,108,32,210,83,65,83,126,124,68,108,70,183,85,65,225,128,124,68,108,165,147,87,65,207,131,124,68,108,12,102,
                                               89,65,28,135,124,68,108,81,45,91,65,196,138,124,68,108,82,232,92,65,199,142,124,68,108,240,149,94,65,32,147,124,68,108,28,53,96,65,206,151,124,68,108,202,196,97,65,206,156,124,68,108,251,67,99,65,28,162,124,68,108,186,177,100,65,181,167,124,68,108,29,
                                               13,102,65,149,173,124,68,108,69,85,103,65,185,179,124,68,108,96,137,104,65,28,186,124,68,108,170,168,105,65,187,192,124,68,108,106,178,106,65,145,199,124,68,108,247,165,107,65,155,206,124,68,108,180,130,108,65,210,213,124,68,108,20,72,109,65,52,221,124,
                                               68,108,154,245,109,65,186,228,124,68,108,214,138,110,65,97,236,124,68,108,104,7,111,65,35,244,124,68,108,1,107,111,65,252,251,124,68,108,98,181,111,65,230,3,125,68,108,89,230,111,65,221,11,125,68,108,201,253,111,65,218,19,125,68,108,0,0,112,65,46,23,
                                               125,68,108,0,0,112,65,46,23,125,68,99,101,0,0 };

            Path p;
            p.loadPathFromData (pathData, sizeof (pathData));

            return p;
        }
        
        const Path createShortOptionsPath()
        {
            const unsigned char pathData[] = { 110,109,0,0,112,65,46,151,127,68,108,0,0,112,65,46,151,127,68,108,52,243,111,65,45,159,127,68,108,216,204,111,65,39,167,127,68,108,4,141,111,65,23,175,127,68,108,226,51,111,65,247,182,127,68,108,170,193,110,65,196,190,127,68,108,166,54,110,65,118,198,
                                               127,68,108,46,147,109,65,11,206,127,68,108,170,215,108,65,125,213,127,68,108,148,4,108,65,198,220,127,68,108,114,26,107,65,227,227,127,68,108,218,25,106,65,207,234,127,68,108,112,3,105,65,134,241,127,68,108,230,215,103,65,2,248,127,68,108,253,151,102,
                                               65,65,254,127,68,108,128,68,101,65,31,2,128,68,108,72,222,99,65,250,4,128,68,108,60,102,98,65,177,7,128,68,108,75,221,96,65,66,10,128,68,108,113,68,95,65,170,12,128,68,108,180,156,93,65,232,14,128,68,108,34,231,91,65,252,16,128,68,108,213,36,90,65,227,
                                               18,128,68,108,236,86,88,65,156,20,128,68,108,142,126,86,65,39,22,128,68,108,233,156,84,65,130,23,128,68,108,51,179,82,65,173,24,128,68,108,164,194,80,65,166,25,128,68,108,122,204,78,65,109,26,128,68,108,246,209,76,65,2,27,128,68,108,93,212,74,65,100,
                                               27,128,68,108,244,212,72,65,147,27,128,68,108,0,0,72,65,151,27,128,68,108,0,0,72,65,151,27,128,68,108,0,0,72,65,151,27,128,68,108,54,0,70,65,125,27,128,68,108,181,1,68,65,49,27,128,68,108,193,5,66,65,177,26,128,68,108,161,13,64,65,255,25,128,68,108,150,
                                               26,62,65,26,25,128,68,108,224,45,60,65,4,24,128,68,108,187,72,58,65,189,22,128,68,108,92,108,56,65,70,21,128,68,108,245,153,54,65,160,19,128,68,108,176,210,52,65,204,17,128,68,108,176,23,51,65,203,15,128,68,108,17,106,49,65,158,13,128,68,108,229,202,
                                               47,65,71,11,128,68,108,55,59,46,65,199,8,128,68,108,6,188,44,65,32,6,128,68,108,71,78,43,65,84,3,128,68,108,229,242,41,65,99,0,128,68,108,188,170,40,65,163,250,127,68,108,160,118,39,65,64,244,127,68,108,86,87,38,65,161,237,127,68,108,150,77,37,65,203,
                                               230,127,68,108,9,90,36,65,193,223,127,68,108,76,125,35,65,138,216,127,68,108,235,183,34,65,40,209,127,68,108,101,10,34,65,162,201,127,68,108,42,117,33,65,251,193,127,68,108,151,248,32,65,56,186,127,68,108,254,148,32,65,96,178,127,68,108,158,74,32,65,
                                               118,170,127,68,108,166,25,32,65,127,162,127,68,108,55,2,32,65,130,154,127,68,108,0,0,32,65,46,151,127,68,108,0,0,32,65,46,151,127,68,108,0,0,32,65,46,151,127,68,108,204,12,32,65,47,143,127,68,108,40,51,32,65,53,135,127,68,108,252,114,32,65,69,127,127,
                                               68,108,31,204,32,65,100,119,127,68,108,87,62,33,65,152,111,127,68,108,92,201,33,65,229,103,127,68,108,212,108,34,65,81,96,127,68,108,88,40,35,65,223,88,127,68,108,110,251,35,65,150,81,127,68,108,144,229,36,65,121,74,127,68,108,41,230,37,65,141,67,127,
                                               68,108,148,252,38,65,214,60,127,68,108,30,40,40,65,89,54,127,68,108,8,104,41,65,27,48,127,68,108,135,187,42,65,30,42,127,68,108,191,33,44,65,103,36,127,68,108,204,153,45,65,249,30,127,68,108,190,34,47,65,217,25,127,68,108,152,187,48,65,8,21,127,68,108,
                                               86,99,50,65,139,16,127,68,108,232,24,52,65,100,12,127,68,108,55,219,53,65,150,8,127,68,108,33,169,55,65,35,5,127,68,108,128,129,57,65,14,2,127,68,108,37,99,59,65,88,255,126,68,108,220,76,61,65,3,253,126,68,108,108,61,63,65,16,251,126,68,108,151,51,65,
                                               65,130,249,126,68,108,28,46,67,65,88,248,126,68,108,182,43,69,65,149,247,126,68,108,31,43,71,65,55,247,126,68,108,0,0,72,65,46,247,126,68,108,0,0,72,65,46,247,126,68,108,0,0,72,65,46,247,126,68,108,201,255,73,65,97,247,126,68,108,75,254,75,65,251,247,
                                               126,68,108,63,250,77,65,250,248,126,68,108,96,242,79,65,94,250,126,68,108,107,229,81,65,39,252,126,68,108,32,210,83,65,83,254,126,68,108,70,183,85,65,225,0,127,68,108,165,147,87,65,207,3,127,68,108,12,102,89,65,28,7,127,68,108,81,45,91,65,196,10,127,
                                               68,108,82,232,92,65,199,14,127,68,108,240,149,94,65,32,19,127,68,108,28,53,96,65,206,23,127,68,108,202,196,97,65,206,28,127,68,108,251,67,99,65,28,34,127,68,108,186,177,100,65,181,39,127,68,108,29,13,102,65,149,45,127,68,108,69,85,103,65,185,51,127,68,
                                               108,96,137,104,65,28,58,127,68,108,170,168,105,65,187,64,127,68,108,106,178,106,65,145,71,127,68,108,247,165,107,65,155,78,127,68,108,180,130,108,65,210,85,127,68,108,20,72,109,65,52,93,127,68,108,154,245,109,65,186,100,127,68,108,214,138,110,65,97,108,
                                               127,68,108,104,7,111,65,35,116,127,68,108,1,107,111,65,252,123,127,68,108,98,181,111,65,230,131,127,68,108,89,230,111,65,221,139,127,68,108,201,253,111,65,218,147,127,68,108,0,0,112,65,46,151,127,68,108,0,0,112,65,46,151,127,68,99,109,0,0,0,0,46,151,
                                               127,68,108,0,0,32,65,46,151,127,68,109,0,0,112,65,46,151,127,68,108,0,0,32,66,46,151,127,68,109,252,38,135,65,151,75,130,68,108,252,38,135,65,151,75,130,68,108,150,32,135,65,151,79,130,68,108,104,13,135,65,148,83,130,68,108,126,237,134,65,139,87,130,
                                               68,108,237,192,134,65,124,91,130,68,108,209,135,134,65,98,95,130,68,108,79,66,134,65,59,99,130,68,108,147,240,133,65,6,103,130,68,108,209,146,133,65,190,106,130,68,108,70,41,133,65,99,110,130,68,108,53,180,132,65,242,113,130,68,108,233,51,132,65,104,
                                               117,130,68,108,180,168,131,65,195,120,130,68,108,239,18,131,65,1,124,130,68,108,250,114,130,65,33,127,130,68,108,60,201,129,65,31,130,130,68,108,32,22,129,65,250,132,130,68,108,26,90,128,65,177,135,130,68,108,67,43,127,65,66,138,130,68,108,105,146,125,
                                               65,170,140,130,68,108,172,234,123,65,232,142,130,68,108,26,53,122,65,252,144,130,68,108,205,114,120,65,227,146,130,68,108,228,164,118,65,156,148,130,68,108,134,204,116,65,39,150,130,68,108,225,234,114,65,130,151,130,68,108,43,1,113,65,173,152,130,68,
                                               108,156,16,111,65,166,153,130,68,108,114,26,109,65,109,154,130,68,108,238,31,107,65,2,155,130,68,108,85,34,105,65,100,155,130,68,108,236,34,103,65,147,155,130,68,108,248,77,102,65,151,155,130,68,108,248,77,102,65,151,155,130,68,108,248,77,102,65,151,
                                               155,130,68,108,46,78,100,65,125,155,130,68,108,173,79,98,65,49,155,130,68,108,185,83,96,65,177,154,130,68,108,153,91,94,65,255,153,130,68,108,142,104,92,65,26,153,130,68,108,216,123,90,65,4,152,130,68,108,179,150,88,65,189,150,130,68,108,84,186,86,65,
                                               70,149,130,68,108,237,231,84,65,160,147,130,68,108,168,32,83,65,204,145,130,68,108,168,101,81,65,203,143,130,68,108,9,184,79,65,158,141,130,68,108,221,24,78,65,71,139,130,68,108,47,137,76,65,199,136,130,68,108,254,9,75,65,32,134,130,68,108,63,156,73,
                                               65,84,131,130,68,108,221,64,72,65,99,128,130,68,108,180,248,70,65,82,125,130,68,108,152,196,69,65,32,122,130,68,108,78,165,68,65,208,118,130,68,108,142,155,67,65,101,115,130,68,108,1,168,66,65,225,111,130,68,108,68,203,65,65,69,108,130,68,108,227,5,65,
                                               65,148,104,130,68,108,93,88,64,65,209,100,130,68,108,34,195,63,65,253,96,130,68,108,143,70,63,65,28,93,130,68,108,246,226,62,65,48,89,130,68,108,150,152,62,65,59,85,130,68,108,158,103,62,65,64,81,130,68,108,47,80,62,65,65,77,130,68,108,248,77,62,65,151,
                                               75,130,68,108,248,77,62,65,151,75,130,68,108,248,77,62,65,151,75,130,68,108,196,90,62,65,151,71,130,68,108,32,129,62,65,154,67,130,68,108,244,192,62,65,162,63,130,68,108,23,26,63,65,178,59,130,68,108,79,140,63,65,204,55,130,68,108,84,23,64,65,243,51,
                                               130,68,108,204,186,64,65,40,48,130,68,108,80,118,65,65,112,44,130,68,108,102,73,66,65,203,40,130,68,108,136,51,67,65,60,37,130,68,108,33,52,68,65,198,33,130,68,108,140,74,69,65,107,30,130,68,108,22,118,70,65,45,27,130,68,108,0,182,71,65,13,24,130,68,
                                               108,127,9,73,65,15,21,130,68,108,183,111,74,65,52,18,130,68,108,196,231,75,65,125,15,130,68,108,182,112,77,65,236,12,130,68,108,144,9,79,65,132,10,130,68,108,78,177,80,65,70,8,130,68,108,224,102,82,65,50,6,130,68,108,47,41,84,65,75,4,130,68,108,25,247,
                                               85,65,146,2,130,68,108,120,207,87,65,7,1,130,68,108,29,177,89,65,172,255,129,68,108,212,154,91,65,129,254,129,68,108,100,139,93,65,136,253,129,68,108,143,129,95,65,193,252,129,68,108,20,124,97,65,44,252,129,68,108,174,121,99,65,202,251,129,68,108,23,
                                               121,101,65,155,251,129,68,108,248,77,102,65,151,251,129,68,108,248,77,102,65,151,251,129,68,108,248,77,102,65,151,251,129,68,108,193,77,104,65,177,251,129,68,108,67,76,106,65,253,251,129,68,108,55,72,108,65,125,252,129,68,108,88,64,110,65,47,253,129,
                                               68,108,99,51,112,65,20,254,129,68,108,24,32,114,65,42,255,129,68,108,62,5,116,65,113,0,130,68,108,157,225,117,65,232,1,130,68,108,4,180,119,65,142,3,130,68,108,73,123,121,65,98,5,130,68,108,74,54,123,65,99,7,130,68,108,232,227,124,65,144,9,130,68,108,
                                               20,131,126,65,231,11,130,68,108,97,9,128,65,103,14,130,68,108,250,200,128,65,14,17,130,68,108,217,127,129,65,218,19,130,68,108,138,45,130,65,203,22,130,68,108,158,209,130,65,220,25,130,68,108,172,107,131,65,14,29,130,68,108,81,251,131,65,94,32,130,68,
                                               108,49,128,132,65,201,35,130,68,108,247,249,132,65,77,39,130,68,108,86,104,133,65,233,42,130,68,108,6,203,133,65,154,46,130,68,108,201,33,134,65,93,50,130,68,108,103,108,134,65,49,54,130,68,108,176,170,134,65,18,58,130,68,108,125,220,134,65,254,61,130,
                                               68,108,173,1,135,65,243,65,130,68,108,40,26,135,65,238,69,130,68,108,224,37,135,65,237,73,130,68,108,252,38,135,65,151,75,130,68,108,252,38,135,65,151,75,130,68,99,109,0,0,240,65,151,11,129,68,108,0,0,240,65,151,11,129,68,108,154,249,239,65,151,15,129,
                                               68,108,108,230,239,65,148,19,129,68,108,130,198,239,65,139,23,129,68,108,241,153,239,65,124,27,129,68,108,213,96,239,65,98,31,129,68,108,83,27,239,65,59,35,129,68,108,151,201,238,65,6,39,129,68,108,213,107,238,65,190,42,129,68,108,74,2,238,65,99,46,129,
                                               68,108,57,141,237,65,242,49,129,68,108,237,12,237,65,104,53,129,68,108,184,129,236,65,195,56,129,68,108,243,235,235,65,1,60,129,68,108,254,75,235,65,33,63,129,68,108,64,162,234,65,31,66,129,68,108,36,239,233,65,250,68,129,68,108,30,51,233,65,177,71,129,
                                               68,108,165,110,232,65,66,74,129,68,108,56,162,231,65,170,76,129,68,108,90,206,230,65,232,78,129,68,108,145,243,229,65,252,80,129,68,108,107,18,229,65,227,82,129,68,108,118,43,228,65,156,84,129,68,108,71,63,227,65,39,86,129,68,108,117,78,226,65,130,87,
                                               129,68,108,153,89,225,65,173,88,129,68,108,82,97,224,65,166,89,129,68,108,61,102,223,65,109,90,129,68,108,251,104,222,65,2,91,129,68,108,46,106,221,65,100,91,129,68,108,122,106,220,65,147,91,129,68,108,0,0,220,65,151,91,129,68,108,0,0,220,65,151,91,129,
                                               68,108,0,0,220,65,151,91,129,68,108,27,0,219,65,125,91,129,68,108,218,0,218,65,49,91,129,68,108,225,2,217,65,177,90,129,68,108,208,6,216,65,255,89,129,68,108,75,13,215,65,26,89,129,68,108,240,22,214,65,4,88,129,68,108,93,36,213,65,189,86,129,68,108,46,
                                               54,212,65,70,85,129,68,108,250,76,211,65,160,83,129,68,108,88,105,210,65,204,81,129,68,108,216,139,209,65,203,79,129,68,108,8,181,208,65,158,77,129,68,108,115,229,207,65,71,75,129,68,108,156,29,207,65,199,72,129,68,108,3,94,206,65,32,70,129,68,108,36,
                                               167,205,65,84,67,129,68,108,114,249,204,65,99,64,129,68,108,94,85,204,65,82,61,129,68,108,80,187,203,65,32,58,129,68,108,171,43,203,65,208,54,129,68,108,203,166,202,65,101,51,129,68,108,4,45,202,65,225,47,129,68,108,166,190,201,65,69,44,129,68,108,245,
                                               91,201,65,148,40,129,68,108,50,5,201,65,209,36,129,68,108,149,186,200,65,253,32,129,68,108,76,124,200,65,28,29,129,68,108,127,74,200,65,48,25,129,68,108,79,37,200,65,59,21,129,68,108,211,12,200,65,64,17,129,68,108,27,1,200,65,65,13,129,68,108,0,0,200,
                                               65,151,11,129,68,108,0,0,200,65,151,11,129,68,108,0,0,200,65,151,11,129,68,108,102,6,200,65,151,7,129,68,108,148,25,200,65,154,3,129,68,108,126,57,200,65,162,255,128,68,108,15,102,200,65,178,251,128,68,108,43,159,200,65,204,247,128,68,108,174,228,200,
                                               65,243,243,128,68,108,106,54,201,65,40,240,128,68,108,44,148,201,65,112,236,128,68,108,183,253,201,65,203,232,128,68,108,200,114,202,65,60,229,128,68,108,20,243,202,65,198,225,128,68,108,74,126,203,65,107,222,128,68,108,15,20,204,65,45,219,128,68,108,
                                               4,180,204,65,13,216,128,68,108,195,93,205,65,15,213,128,68,108,224,16,206,65,52,210,128,68,108,230,204,206,65,125,207,128,68,108,95,145,207,65,236,204,128,68,108,204,93,208,65,132,202,128,68,108,171,49,209,65,70,200,128,68,108,116,12,210,65,50,198,128,
                                               68,108,155,237,210,65,75,196,128,68,108,145,212,211,65,146,194,128,68,108,192,192,212,65,7,193,128,68,108,147,177,213,65,172,191,128,68,108,110,166,214,65,129,190,128,68,108,182,158,215,65,136,189,128,68,108,204,153,216,65,193,188,128,68,108,14,151,217,
                                               65,44,188,128,68,108,219,149,218,65,202,187,128,68,108,144,149,219,65,155,187,128,68,108,0,0,220,65,151,187,128,68,108,0,0,220,65,151,187,128,68,108,0,0,220,65,151,187,128,68,108,229,255,220,65,177,187,128,68,108,38,255,221,65,253,187,128,68,108,32,253,
                                               222,65,125,188,128,68,108,48,249,223,65,47,189,128,68,108,181,242,224,65,20,190,128,68,108,16,233,225,65,42,191,128,68,108,163,219,226,65,113,192,128,68,108,210,201,227,65,232,193,128,68,108,6,179,228,65,142,195,128,68,108,169,150,229,65,98,197,128,68,
                                               108,41,116,230,65,99,199,128,68,108,248,74,231,65,144,201,128,68,108,142,26,232,65,231,203,128,68,108,101,226,232,65,103,206,128,68,108,254,161,233,65,14,209,128,68,108,221,88,234,65,218,211,128,68,108,142,6,235,65,203,214,128,68,108,162,170,235,65,220,
                                               217,128,68,108,176,68,236,65,14,221,128,68,108,85,212,236,65,94,224,128,68,108,53,89,237,65,201,227,128,68,108,251,210,237,65,77,231,128,68,108,90,65,238,65,233,234,128,68,108,10,164,238,65,154,238,128,68,108,205,250,238,65,93,242,128,68,108,107,69,239,
                                               65,49,246,128,68,108,180,131,239,65,18,250,128,68,108,129,181,239,65,254,253,128,68,108,177,218,239,65,243,1,129,68,108,44,243,239,65,238,5,129,68,108,228,254,239,65,237,9,129,68,108,0,0,240,65,151,11,129,68,108,0,0,240,65,151,11,129,68,99,109,0,0,0,
                                               0,151,11,129,68,108,0,0,200,65,151,11,129,68,109,0,0,240,65,151,11,129,68,108,0,0,32,66,151,11,129,68,109,0,0,0,0,151,75,130,68,108,0,80,62,65,151,75,130,68,109,0,40,135,65,151,75,130,68,108,0,0,32,66,151,75,130,68,101,0,0 };
                                               
            Path p;
            p.loadPathFromData (pathData, sizeof (pathData));

            return p;
        }

        const Path createFloppyDiskPath()
        {
            const unsigned char pathData[] = { 110,109,209,81,185,65,169,232,125,68,108,226,174,202,65,169,232,125,68,98,52,223,206,65,169,232,125,68,123,62,210,65,198,5,126,68,123,62,210,65,239,41,126,68,108,123,62,210,65,39,202,127,68,98,123,62,210,65,80,238,127,68,52,223,206,65,182,5,128,68,226,
                                               174,202,65,182,5,128,68,108,209,81,185,65,182,5,128,68,98,127,33,181,65,182,5,128,68,57,194,177,65,81,238,127,68,57,194,177,65,40,202,127,68,108,57,194,177,65,240,41,126,68,98,57,194,177,65,199,5,126,68,128,33,181,65,170,232,125,68,209,81,185,65,170,
                                               232,125,68,99,109,0,96,69,64,79,60,125,68,98,47,76,217,63,79,60,125,68,0,0,21,63,214,131,125,68,0,0,21,63,143,220,125,68,108,0,0,21,63,231,40,131,68,98,0,0,21,63,68,85,131,68,48,76,217,63,247,120,131,68,0,96,69,64,247,120,131,68,108,0,170,9,66,247,120,
                                               131,68,98,159,53,15,66,247,120,131,68,0,172,19,66,68,85,131,68,0,172,19,66,231,40,131,68,108,0,172,19,66,78,149,126,68,108,0,172,252,65,78,60,125,68,108,0,124,236,65,78,60,125,68,108,0,124,236,65,134,93,128,68,108,0,8,39,65,134,93,128,68,108,0,8,39,65,
                                               77,60,125,68,108,0,96,69,64,77,60,125,68,99,109,0,32,175,64,7,101,129,68,108,0,28,0,66,7,101,129,68,108,0,28,0,66,119,220,130,68,108,0,32,175,64,119,220,130,68,108,0,32,175,64,7,101,129,68,99,101,0,0 };

            Path p;
            p.loadPathFromData (pathData, sizeof (pathData));

            return p;
        }

        const Path createFlatSavePath()
        {
            const unsigned char pathData[] = { 110,109,14,45,135,65,202,14,130,68,108,0,0,200,65,151,11,129,68,108,14,45,135,65,100,8,128,68,109,0,0,0,0,151,11,129,68,108,0,0,200,65,151,11,129,68,109,78,240,54,65,210,118,126,68,108,236,67,26,66,210,118,126,68,98,173,88,28,66,210,118,126,68,146,5,
                                               30,66,124,147,126,68,146,5,30,66,23,183,126,68,108,146,5,30,66,160,187,130,68,98,146,5,30,66,109,205,130,68,173,88,28,66,194,219,130,68,236,67,26,66,194,219,130,68,108,76,240,54,65,194,219,130,68,98,74,157,46,65,194,219,130,68,181,233,39,65,109,205,130,
                                               68,181,233,39,65,160,187,130,68,108,181,233,39,65,23,183,126,68,98,181,233,39,65,125,147,126,68,74,157,46,65,210,118,126,68,76,240,54,65,210,118,126,68,99,101,0,0 };

            Path p;
            p.loadPathFromData (pathData, sizeof (pathData));

            return p;
        }
    }
}