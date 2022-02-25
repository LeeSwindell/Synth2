/*
  ==============================================================================

    SynthVoice.cpp
    Created: 24 Feb 2022 4:24:54pm
    Author:  Lee Swindell

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice()
{
    auto& masterGain = voiceProcessChain.template get<masterGainIndex>();
    masterGain.setGainLinear(0.7f);
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthVoice*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    auto freq = (float) juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    
    auto& osc1 = voiceProcessChain.template get<osc1Index>();
    osc1.setFrequency(freq);
    osc1.setLevel(velocity);
    
    auto& osc2 = voiceProcessChain.template get<osc2Index>();
    osc2.setFrequency(1.01f * freq);
    osc2.setLevel(velocity);
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    clearCurrentNote();
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    //fill in later
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
    //fill in later
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    auto block = tempBlock.getSubBlock(0, (size_t) numSamples);
    block.clear();
    
    juce::dsp::ProcessContextReplacing<float> context (block);
    voiceProcessChain.process(context);
    
    juce::dsp::AudioBlock<float>(outputBuffer)
        .getSubBlock((size_t) startSample, (size_t) numSamples)
        .add(tempBlock);
    
}

void SynthVoice::prepareToPlay(const juce::dsp::ProcessSpec& spec)
{
    tempBlock = juce::dsp::AudioBlock<float>(heapBlock, spec.numChannels, spec.maximumBlockSize);
    
    voiceProcessChain.prepare(spec);
    
    isPrepared = true;
}
