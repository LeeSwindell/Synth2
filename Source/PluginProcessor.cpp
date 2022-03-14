/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth2AudioProcessor::Synth2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                    apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

Synth2AudioProcessor::~Synth2AudioProcessor()
{
}

//==============================================================================
const juce::String Synth2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Synth2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Synth2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Synth2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Synth2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Synth2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Synth2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Synth2AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Synth2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Synth2AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Synth2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    midiMessageCollector.reset (sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            voice->prepareToPlay({ sampleRate, (juce::uint32) samplesPerBlock, (juce::uint32) getTotalNumOutputChannels() });
    }
}

void Synth2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Synth2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Synth2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    midiMessageCollector.removeNextBlockOfMessages (midiMessages, buffer.getNumSamples()); //this is for the editor midi keyboard
    
    for (int i=0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            
            voice->updateWavetypes(*apvts.getRawParameterValue("OSC1"),
                                   *apvts.getRawParameterValue("OSC2"),
                                   *apvts.getRawParameterValue("OSC3"));
            voice->updateGain(*apvts.getRawParameterValue("GAIN1"),
                              *apvts.getRawParameterValue("GAIN2"),
                              *apvts.getRawParameterValue("GAIN3"),
                              *apvts.getRawParameterValue("MASTERGAIN"));
            voice->updateADSR(attack.load(), decay.load(), sustain.load(), release.load());
            
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Synth2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Synth2AudioProcessor::createEditor()
{
    return new Synth2AudioProcessorEditor (*this);
}

//==============================================================================
void Synth2AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Synth2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Synth2AudioProcessor();
}

//==============================================================================
//Audio Processor Value Tree State

juce::AudioProcessorValueTreeState::ParameterLayout Synth2AudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    // Osc Wavetype Selectors
    layout.add(std::make_unique<juce::AudioParameterChoice> ("OSC1", "Osc 1 Wavetype", juce::StringArray { "Sine", "Square", "Saw" }, 0));
    layout.add(std::make_unique<juce::AudioParameterChoice> ("OSC2", "Osc 2 Wavetype", juce::StringArray { "Sine", "Square", "Saw" }, 0));
    layout.add(std::make_unique<juce::AudioParameterChoice> ("OSC3", "Osc 3 Wavetype", juce::StringArray { "Sine", "Square", "Saw" }, 0));
    
    // Osc Gain Params
    layout.add(std::make_unique<juce::AudioParameterFloat>("GAIN1", "Osc 1 Gain", juce::NormalisableRange<float> { 0.0f, 1.0f }, 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("GAIN2", "Osc 2 Gain", juce::NormalisableRange<float> { 0.0f, 1.0f }, 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("GAIN3", "Osc 3 Gain", juce::NormalisableRange<float> { 0.0f, 1.0f }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("MASTERGAIN", "Master Gain", juce::NormalisableRange<float> { 0.0f, 1.0f }, 0.5f));

    // ADSR Params
    layout.add(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f }, 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f }, 0.4f));
    
    // Lowpass Filter
    layout.add(std::make_unique<juce::AudioParameterFloat>("CUTOFF", "Cutoff Frequency",
                                                           juce::NormalisableRange<float> { 20.0f, 20000.0f }, 20000.0f));
    
    return layout;
}
