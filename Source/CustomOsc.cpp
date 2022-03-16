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

}

void CustomOsc::setWaveform(const int wavetype, const float gain)
{
    auto& osc = oscProcessChain.template get<oscIndex>();
    switch (wavetype)
    {
        case 0: //Sine Wave
            osc.initialise ([gain](float x) { return gain * (std::sin(x)); }, 128);
            break;
        
        case 1: //Square Wave
            osc.initialise([gain](float x) { return gain * (x < 0.0f ? -1.0f : 1.0f); });
            break;
            
        case 2: //Sawtooth Wave
            osc.initialise([gain](float x) { return gain * (juce::jmap (x,
                                                                        float (-juce::MathConstants<double>::pi),
                                                                        float (juce::MathConstants<double>::pi),
                                                                        float (-1),
                                                                        float (1))); }, 2);
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void CustomOsc::setFrequency(float newFreq, bool force)
{
    auto& osc = oscProcessChain.template get<oscIndex>();
    osc.setFrequency(pitchAdjust * newFreq);
}

void CustomOsc::setLevel(float newLevel)
{
    auto& osc = oscProcessChain.template get<gainIndex>();
    osc.setGainLinear(newLevel);
}

void CustomOsc::setPitch(float newPitch)
{
    pitchAdjust = newPitch;
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
