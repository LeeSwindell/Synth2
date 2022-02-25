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
    auto& osc = oscProcessChain.template get<oscIndex>();
    osc.initialise( [] (float x) { return std::sin(x); }, 128);
    //Need to add the ability to use different wavetypes
}

void CustomOsc::setFrequency(float newValue, bool force)
{
    auto& osc = oscProcessChain.template get<oscIndex>();
    osc.setFrequency(newValue);
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

template <typename ProcessContext>
void CustomOsc::oscProcess(const ProcessContext& context) noexcept
{
    oscProcessChain.process(context);
}
