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
    auto& osc1 = oscProcessChain.template get<osc1Index>();
    osc1.initialise( [] (float x) { return std::sin(x); }, 128);
}

void CustomOsc::setFrequency(float newValue, bool force)
{
    auto& osc1 = oscProcessChain.template get<osc1Index>();
    osc1.setFrequency(newValue);
}

void CustomOsc::setLevel(float newValue)
{
    auto& gain = oscProcessChain.template get<gainIndex>();
    gain.setGainLinear(newValue);
}

void CustomOsc::prepare(const juce::dsp::ProcessSpec& spec)
{
    oscProcessChain.prepare(spec);
}

void CustomOsc::reset() noexcept
{
    oscProcessChain.reset();
}

template<typename ProcessContext>
void CustomOsc::process(const ProcessContext& context)
{
    oscProcessChain.process(context);
}
