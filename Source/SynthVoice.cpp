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
//    auto& masterGain = voiceProcessChain.template get<masterGainIndex>();
//    masterGain.setGainLinear(0.5f);
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
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
    
    auto& osc3 = voiceProcessChain.template get<osc3Index>();
    osc3.setFrequency(freq);
    osc3.setLevel(velocity);
    
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    if (! allowTailOff || ! isVoiceActive())
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

void SynthVoice::prepareToPlay(const juce::dsp::ProcessSpec& spec)
{
//    tempBlock = juce::dsp::AudioBlock<float>(heapBlock, spec.numChannels, spec.maximumBlockSize);
    
    voiceProcessChain.prepare(spec);
    adsr.setSampleRate(spec.sampleRate);
    
    isPrepared = true;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    if (! isVoiceActive())
        return;
    
//    auto block = tempBlock.getSubBlock(0, (size_t) numSamples);
//    block.clear();
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> block { synthBuffer };
    
    juce::dsp::ProcessContextReplacing<float> context (block);
    voiceProcessChain.process(context);
    
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if (! adsr.isActive())
            clearCurrentNote();
    }
    
//    juce::dsp::AudioBlock<float>(outputBuffer)
//        .getSubBlock((size_t) startSample, (size_t) numSamples)
//        .add(tempBlock);
}

void SynthVoice::updateWaveforms(const int osc1Wavetype, const int osc2Wavetype, const int osc3Wavetype,
                                 const float osc1Gain, const float osc2Gain, const float osc3Gain)
{
    voiceProcessChain.template get<osc1Index>().setWaveform(osc1Wavetype, osc1Gain);
    voiceProcessChain.template get<osc2Index>().setWaveform(osc2Wavetype, osc2Gain);
    voiceProcessChain.template get<osc3Index>().setWaveform(osc3Wavetype, osc3Gain);
}

void SynthVoice::updateGain(const float masterGain)
{
    voiceProcessChain.template get<masterGainIndex>().setGainLinear(masterGain);
}

void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    adsr.setParameters(adsrParams);
}
