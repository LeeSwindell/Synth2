/*
  ==============================================================================

    CustomOsc.h
    Created: 24 Feb 2022 8:16:00pm
    Author:  Lee Swindell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomOsc
{
public:
    CustomOsc();
    void setWaveform(const int wavetype, const float gain);
    void setFrequency(float newValue, bool force=false);
    void setLevel(float newValue);
    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset() noexcept;
    
//    template<typename ProcessContext> why didn't this template work?? figure it out sometime
    void process(juce::dsp::ProcessContextReplacing<float>& context) noexcept;

private:
    enum
    {
        oscIndex,
        gainIndex
    };
    
    juce::dsp::ProcessorChain<juce::dsp::Oscillator<float>, juce::dsp::Gain<float>> oscProcessChain;
};
