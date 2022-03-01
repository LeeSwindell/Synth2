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
    setSize (400, 300);
    
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
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Synth2AudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    midiKeyboardComponent.setBounds (area.removeFromTop (80).reduced (8));
}
