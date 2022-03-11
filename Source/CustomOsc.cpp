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
    osc.initialise ([](float x) { return std::sin (x); }, 128); //sin wave
    //osc.initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; }); //square wave
    /*osc.initialise([](float x) { return juce::jmap (x,
     float (-juce::MathConstants<double>::pi),
     float (juce::MathConstants<double>::pi),
     float (-1),
     float (1)); }, 2); Sawtooth wave*/
    
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

//template <typename ProcessContext>  why didn't this template work?? figure it out sometime
void CustomOsc::process(juce::dsp::ProcessContextReplacing<float>& context) noexcept
{
    oscProcessChain.process(context);
}
