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
    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE", releaseSlider);
    
    createADSRSliders(attackSlider);
    createADSRSliders(decaySlider);
    createADSRSliders(sustainSlider);
    createADSRSliders(releaseSlider);
        
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
    attackSlider.setBounds(130, 40, 60, 60);
    decaySlider.setBounds(200, 40, 60, 60);
    sustainSlider.setBounds(270, 40, 60, 60);
    releaseSlider.setBounds(340, 40, 60, 60);
}

void Synth2AudioProcessorEditor::createADSRSliders(juce::Slider& slider)
{
    slider.textFromValueFunction = nullptr;
    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    slider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(slider);
}
