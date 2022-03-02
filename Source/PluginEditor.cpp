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
    auto area = getLocalBounds();
    midiKeyboardComponent.setBounds (area.removeFromTop (80).reduced (8));
    attackSlider.setBounds(0, 150, 100, 100);
    decaySlider.setBounds(75, 150, 100, 100);
    sustainSlider.setBounds(150, 150, 100, 100);
    releaseSlider.setBounds(225, 150, 100, 100);
}

void Synth2AudioProcessorEditor::createADSRSliders(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    slider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(slider);
}
