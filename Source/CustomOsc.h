/*
  ==============================================================================

    CustomOsc.h
    Created: 24 Feb 2022 8:16:00pm
    Author:  Lee Swindell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomOsc : public juce::dsp::Oscillator<float>
{
public:
    CustomOsc();
    
    enum
    {
        osc1Index,
        osc2Index,
        masterGainIndex
    };
    
    juce::dsp::ProcessorChain<juce::dsp::Oscillator<float>, juce::dsp::Oscillator<float>, juce::dsp::Gain<float>> processChain;
    // set default gain/oscillators somewhere??
    
    void setFrequency(float newValue, bool force=false);
    void setLevel(float newValue);
    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset() noexcept;
    template<typename ProcessContext>
    void process(const ProcessContext& context);

private:
    
};
