/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLook.h"

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
    void createSliders(juce::Slider& slider, juce::Label& label, juce::String labelText);
    void createComboBox(juce::ComboBox& comboBox, juce::Label& label, juce::String labelText);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Synth2AudioProcessor& audioProcessor;
    juce::MidiKeyboardState midiKeyboardState;
    juce::MidiKeyboardComponent midiKeyboardComponent { midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard };
    CustomLook lookAndFeel;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    //Osc Selectors
    juce::ComboBox osc1Combo, osc2Combo, osc3Combo;
    juce::Label osc1Label, osc2Label, osc3Label;
    std::unique_ptr<ComboAttachment> osc1Attachment, osc2Attachment, osc3Attachment;
    
    //Gain Sliders
    juce::Slider osc1GainSlider, osc2GainSlider, osc3GainSlider, masterGainSlider;
    juce::Label osc1GainLabel, osc2GainLabel, osc3GainLabel, masterGainLabel; //I dont think these labels do anything atm. 
    std::unique_ptr<SliderAttachment> osc1GainAttachment, osc2GainAttachment, osc3GainAttachment, masterGainAttachment;
    
    //ADSR Params
    juce::Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
    juce::Label attackLabel, decayLabel, sustainLabel, releaseLabel;
    std::unique_ptr<SliderAttachment> attackAttachment, decayAttachment, sustainAttachment, releaseAttachment;
    
    // Cutoff Freq
    juce::Slider cutoffFreqSlider;
    juce::Label cutoffFreqLabel;
    std::unique_ptr<SliderAttachment> cutoffFreqAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth2AudioProcessorEditor)
};
