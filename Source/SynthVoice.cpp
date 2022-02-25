/*
  ==============================================================================

    SynthVoice.cpp
    Created: 24 Feb 2022 4:24:54pm
    Author:  Lee Swindell

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthVoice*>(sound) != nullptr;
}

void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    
}

void stopNote(float velocity, bool allowTailOff)
{
    
}

void pitchWheelMoved(int newPitchWheelValue)
{
    
}

void controllerMoved(int controllerNumber, int newControllerValue)
{
    
}

void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    
}
