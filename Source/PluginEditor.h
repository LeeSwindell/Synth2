/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Synth2AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Synth2AudioProcessorEditor (Synth2AudioProcessor&);
    ~Synth2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Synth2AudioProcessor& audioProcessor;
    juce::MidiKeyboardState midiKeyboardState;
    juce::MidiKeyboardComponent midiKeyboardComponent { midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth2AudioProcessorEditor)
};
