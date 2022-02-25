/*
  ==============================================================================

    CustomOsc.cpp
    Created: 24 Feb 2022 8:16:00pm
    Author:  Lee Swindell

  ==============================================================================
*/

#include "CustomOsc.h"

CustomOsc::CustomOsc()
{
    auto& osc1 = processChain.template get<osc1Index>();
    auto& osc2 = processChain.template get<osc2Index>();
//    auto& masterGain = processChain.template get<masterGainIndex>();
    
    osc1.initialise( [] (float x) { return std::sin(x); }, 128);
    osc2.initialise( [] (float x) { return std::sin(x); }, 128);
}

void CustomOsc::setFrequency(float newValue, bool force)
{
    
}

void CustomOsc::setLevel(float newValue)
{
    auto& masterGain = processChain.template get<masterGainIndex>();
    masterGain.setGainLinear(newValue);
}

void CustomOsc::prepare(const juce::dsp::ProcessSpec& spec)
{
    processChain.prepare(spec);
}

void CustomOsc::reset() noexcept
{
    processChain.reset();
}

template<typename ProcessContext>
void CustomOsc::process(const ProcessContext& context)
{
    
}
