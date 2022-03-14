/*
  ==============================================================================

    SynthVoice.h
    Created: 24 Feb 2022 4:24:54pm
    Author:  Lee Swindell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "CustomOsc.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    enum
    {
        osc1Index,
        osc2Index,
        osc3Index,
        masterGainIndex
    };
    
    SynthVoice();
    bool canPlaySound(juce::SynthesiserSound*) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void prepareToPlay(const juce::dsp::ProcessSpec& spec);
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    void updateWavetypes(const int osc1Wavetype, const int osc2Wavetype, const int osc3Wavetype);
    void updateGain(const float osc1Gain, const float osc2Gain, const float osc3Gain, const float masterGain);
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
        
private:
//    juce::HeapBlock<char> heapBlock;
//    juce::dsp::AudioBlock<float> tempBlock;
    juce::AudioBuffer<float> synthBuffer;
    
    juce::dsp::ProcessorChain<CustomOsc, CustomOsc, CustomOsc, juce::dsp::Gain<float>> voiceProcessChain;
    
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
    float gain1, gain2, gain3;
    
    bool isPrepared { false };
};
