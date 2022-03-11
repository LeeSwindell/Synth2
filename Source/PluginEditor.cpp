/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth2AudioProcessorEditor::Synth2AudioProcessorEditor (Synth2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
    setLookAndFeel(&lookAndFeel);
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    // Osc Params
    osc1Attachment = std::make_unique<ComboAttachment>(audioProcessor.apvts, "OSC1", osc1Combo);
    osc2Attachment = std::make_unique<ComboAttachment>(audioProcessor.apvts, "OSC2", osc2Combo);
    osc3Attachment = std::make_unique<ComboAttachment>(audioProcessor.apvts, "OSC3", osc3Combo);
    osc1GainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "GAIN1", osc1GainSlider);
    osc2GainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "GAIN2", osc2GainSlider);
    osc3GainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "GAIN3", osc3GainSlider);
    masterGainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "MASTERGAIN", masterGainSlider);
    
    createComboBox(osc1Combo, osc1Label, "Osc 1 Wavetype");
    createComboBox(osc2Combo, osc2Label, "Osc 2 Wavetype");
    createComboBox(osc3Combo, osc3Label, "Osc 3 Wavetype");
    createSliders(osc1GainSlider, osc1GainLabel, "Gain1");
    createSliders(osc2GainSlider, osc2GainLabel, "Gain2");
    createSliders(osc3GainSlider, osc3GainLabel, "Gain3");
    createSliders(masterGainSlider, masterGainLabel, "Master");
    
    // ADSR Sliders
    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE", releaseSlider);
    
    createSliders(attackSlider, attackLabel, "Att");
    createSliders(decaySlider, decayLabel, "Dec");
    createSliders(sustainSlider, sustainLabel, "Sus");
    createSliders(releaseSlider, releaseLabel, "Rel");
        
    addAndMakeVisible (midiKeyboardComponent);
    midiKeyboardComponent.setMidiChannel (2);
    midiKeyboardState.addListener (&audioProcessor.getMidiMessageCollector());
}

Synth2AudioProcessorEditor::~Synth2AudioProcessorEditor()
{
    midiKeyboardState.removeListener (&audioProcessor.getMidiMessageCollector());
    setLookAndFeel(nullptr);
}

//==============================================================================
void Synth2AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void Synth2AudioProcessorEditor::resized()
{
//    auto area = getLocalBounds();
//    midiKeyboardComponent.setBounds (area.removeFromTop (80).reduced (8));
    
    // Osc Params
    osc1Combo.setBounds(10, 30, 120, 30);
    osc2Combo.setBounds(10, 85, 120, 30);
    osc3Combo.setBounds(10, 140, 120, 30);
    osc1GainSlider.setBounds(130, 30, 60, 60);
    osc2GainSlider.setBounds(200, 30, 60, 60);
    osc3GainSlider.setBounds(270, 30, 60, 60);
    masterGainSlider.setBounds(340, 30, 60, 60);
    
    // ADSR Sliders
    attackSlider.setBounds(130, 110, 60, 60);
    decaySlider.setBounds(200, 110, 60, 60);
    sustainSlider.setBounds(270, 110, 60, 60);
    releaseSlider.setBounds(340, 110, 60, 60);
}

void Synth2AudioProcessorEditor::createSliders(juce::Slider& slider, juce::Label& label, juce::String labelText)
{
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);
    slider.textFromValueFunction = nullptr;
    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    slider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(slider);
}

void Synth2AudioProcessorEditor::createComboBox(juce::ComboBox& comboBox, juce::Label &label, juce::String labelText)
{
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&comboBox, false);
    comboBox.addItem("Sine", 1);
    comboBox.addItem("Square", 2);
    comboBox.addItem("Saw", 3);
    addAndMakeVisible(comboBox);
}
