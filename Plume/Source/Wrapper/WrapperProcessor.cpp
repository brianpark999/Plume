/*
  ==============================================================================

    WrappedPluginProcessor.cpp
    Created: 9 Apr 2018 3:23:04pm
    Author:  Alex LEVACHER

  ==============================================================================
*/

#include "PluginWrapper.h"

//==============================================================================
/*class that wraps a parameter from the plugin, forwarding it's methods to the wrapperProcessor*/

class WrapperProcessor::WrappedParameter :  public AudioProcessorParameter
{
public:
    explicit WrappedParameter(AudioProcessorParameter& wrap)
        : wrappedParam(wrap)
    {}
    
    float getValue() const override                          { return wrappedParam.getValue();         }
    void setValue (float newValue) override                  {        wrappedParam.setValue (newValue);}
    float getDefaultValue() const override                   { return wrappedParam.getDefaultValue();  }
    String getName (int maxLen) const override               { return wrappedParam.getName (maxLen);   }
    String getLabel() const override                         { return wrappedParam.getLabel();         }
    int getNumSteps() const override                         { return wrappedParam.getNumSteps();      }
    bool isDiscrete() const override                         { return wrappedParam.isDiscrete();       }
        
    String getText (float v, int len) const override         { return wrappedParam.getText (v, len);        }
    float getValueForText (const String& t) const override   { return wrappedParam.getValueForText (t);     }
    String getCurrentValueAsText() const override            { return wrappedParam.getCurrentValueAsText(); }
    bool isOrientationInverted() const override              { return wrappedParam.isOrientationInverted(); }
    bool isAutomatable() const override                      { return wrappedParam.isAutomatable();         }
    bool isMetaParameter() const override                    { return wrappedParam.isMetaParameter();       }
    Category getCategory() const override                    { return wrappedParam.getCategory();           }
    
private:
    AudioProcessorParameter& wrappedParam;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WrappedParameter)
};


//==============================================================================
WrapperProcessor::WrapperProcessor(AudioPluginInstance& wrappedPlugin, PluginWrapper& ownerWrapper)
    : AudioProcessor (WrapperProcessor::createBusesPropertiesFromPluginInstance (wrappedPlugin)),
      plugin (wrappedPlugin),
      owner (ownerWrapper)
{
    //plugin.setBusesLayout (getBusesLayout());
    initWrappedParameters();
    disableNonMainBuses();
    writeBusesLayoutToLog();
}

WrapperProcessor::~WrapperProcessor()
{
    auto& params = plugin.getParameters();
    
    for (auto* param : params)
    {
        param->removeListener (&getOwnerWrapper());
    }
}

//==============================================================================
void WrapperProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    // Clears the audioBuffer if its not needed
    if (plugin.getMainBusNumInputChannels() == 0)
    {
        buffer.clear();
    }

    int channelCount = 0;
    int mainBusId = 0;
    for (int outBusNum =0; outBusNum < plugin.getBusCount (false); outBusNum++)
    {
        if (plugin.getBus (false, outBusNum)->isMain()) mainBusId = outBusNum;

        channelCount += getChannelCountOfBus (false, outBusNum);
    }

    AudioBuffer<float> wrapperBuffer (channelCount, buffer.getNumSamples());
    
    // Makes the plugin use playhead from the DAW
    plugin.setPlayHead (getPlayHead());
    plugin.processBlock (wrapperBuffer, midiMessages);

    copyWrapperBuffersIntoPlumeBuffer (buffer, wrapperBuffer);
}


//==============================================================================
bool WrapperProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    PLUME::log::writeToLog ("Checking buses Layout : " + String (layouts.getMainInputChannels())
                                               + " | " + String (layouts.getMainOutputChannels()),
                            PLUME::log::pluginWrapping);

    return plugin.checkBusesLayoutSupported (layouts);
}

bool WrapperProcessor::applyBusLayouts (const BusesLayout &layouts)
{
    return (AudioProcessor::applyBusLayouts(layouts) && plugin.setBusesLayout (layouts));
}

//==============================================================================
bool WrapperProcessor::canAddBus (bool isInput) const
{
    return plugin.canAddBus (isInput);
}

bool WrapperProcessor::canRemoveBus (bool isInput) const
{
    return plugin.canRemoveBus (isInput);
}

//==============================================================================
void WrapperProcessor::initWrappedParameters()
{
    auto& params = plugin.getParameters();
    
    for (auto* param : params)
    {
        addParameter(new WrappedParameter(*param));
        param->addListener (&getOwnerWrapper());
    }
}

AudioProcessorParameter& WrapperProcessor::getWrappedParameter (int id)
{
    auto& params = plugin.getParameters();
    
    return *(params[id]);
}

PluginWrapper& WrapperProcessor::getOwnerWrapper()
{
    return owner;
}

AudioPluginInstance& WrapperProcessor::getWrappedInstance()
{
    return plugin;
}

void WrapperProcessor::clearEditor()
{
    owner.clearWrapperEditor();
}

AudioProcessor::BusesProperties WrapperProcessor::createBusesPropertiesFromPluginInstance (AudioPluginInstance& pluginInstance)
{
    BusesProperties busesProp;

    busesProp.addBus (false, "Main Output", AudioChannelSet::stereo(), true);

    for (int isInput =1; isInput >= 0; isInput--)
    {
        for (int busNum =0; busNum < pluginInstance.getBusCount (isInput); busNum++)
        {
            if (const Bus* bus = pluginInstance.getBus (isInput, busNum))
            {
                busesProp.addBus (isInput, bus->getName(),
                                           bus->getDefaultLayout(),
                                           bus->isEnabledByDefault());
            }    
        }
    }

    return busesProp;
}

void WrapperProcessor::copyWrapperBuffersIntoPlumeBuffer (AudioBuffer<float>& plumeBuffer, AudioBuffer<float>& wrapperBuffer)
{
    for (int busNum =0; busNum < plugin.getBusCount (false); busNum++)
    {
        if (auto* bus = plugin.getBus (false, busNum))
        {
            if (bus->isEnabled() && bus->getNumberOfChannels() <= plumeBuffer.getNumChannels())
            {
                for (int channelNum =0; channelNum < plumeBuffer.getNumChannels(); channelNum++)
                    plumeBuffer.addFrom (channelNum, 0, wrapperBuffer,
                                         bus->getChannelIndexInProcessBlockBuffer (channelNum),
                                         0, plumeBuffer.getNumSamples());
            }
        }
    }
}

void WrapperProcessor::writeBusesLayoutToLog()
{
    Array<AudioProcessor*> processors (this, &plugin);

    for (auto* processor : processors)
    {
        String logString ("Processor " + processor->getName() + " :\nOutput buses : " + String (processor->getBusCount (false)));
        
        for (int outBusNum =0; outBusNum < processor->getBusCount (false); outBusNum++)
        {
            if (const AudioProcessor::Bus* bus = processor->getBus (false, outBusNum))
            {
                logString += "\n  -| " + bus->getName()
                           + " | Main ? " + String (bus->isMain() ? "Y" : "N")
                           + " | Layout : " + bus->getCurrentLayout().getDescription()
                           + " (" + bus->getCurrentLayout().getSpeakerArrangementAsString()
                           + ") | Channels : " + String (bus->getNumberOfChannels())
                           + " | Enabled ? " + String (bus->isEnabled() ? "Y" : "N")
                           + " | Enabled By Default ? " + String (bus->isEnabledByDefault() ? "Y" : "N");
            }
        }

        PLUME::log::writeToLog (logString, PLUME::log::pluginWrapping);
    }
}
