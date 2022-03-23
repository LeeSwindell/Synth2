# Lee's JUCE Synthesizer
---
This synthesizer was my way of learning C++. It uses the JUCE framework to handle midi data and providing an easy way to connect the synth with a DAW (digital audio workstation - Logic Pro/Ableton etc). To start with, I had never seen or used either of these tools, having programmed with only Python, Java, Javascript, and Julia.  

---
I'll discuss what a synth is and what this one can do musically, then go into more detail about the structure of the code at the end.  

---
![Custom GUI](https://github.com/LeeSwindell/Synth2/blob/main/images/GUI.png)  

This is the (very plain) custom gui for the synth. There's 3 different oscillators, each of which can produce a sine, square, sawtooth, triangle, and wide or narrow pulse. Each waveform has a slightly different musical timbre, due to how our ear decodes these signals. For example, a sine wave at 440 hertz sounds like a pure 'A' note. A square wave at 440 hertz has the same pitch, but many overtones. If you're familiar with fourier transforms, you can think of our ear as decoding the more complex waveforms into many sine waves of differing frequencies. The structure of these overtones is what gives a sound its timbre; it's how we distinguish whether a note was played on a guitar, piano, trumpet, and so on. 

---
For any given waveform, we can also change the shape by molding the frequency vs amplitude and amplitude vs time space. The 'Att', 'Dec', 'Sus', 'Rel' knobs (Attack, Decay, Sustain, Release) control the envelope filter, which shapes the volume of the wave each time a key is pressed or released. The attack determines how long after a key is pressed before it reaches its full volume. The release determines how long after a key is release before it is silent. The sustain controls the percent of total volume that a note will play at while being held down. So a sustain of .5 will initially rise to full volume, then quiet down to 50% volume. Decay controls how long it takes to reach the sustain volume after reaching full volume.  
  
The 'Cutoff', 'Resonance', and 'Drive' knobs control the ladder filter, which is a specific implementation of a lowpass filter. For all frequencies above the cutoff, there is a 24 dB reduction per octave above the cutoff. Essentially, the high pitch sounds get increasingly muted the higher they are. This can give some waveforms like the sawtooth, which has many overtones, a warmer sound. The resonance adds a small volume boost to frequencies near the cutoff, which alters the color of the sound a bit more. The drive just adds a bit of warm distortion.  
  
There's also three individual gain controls for each oscillator. If one oscillator has a sawtooth wave playing the leading sound, but you want to support it with a little triangle wave on oscillator 2 for example, you could mix them directly here.  
  
Finally, the pitch knobs can be set at up to a perfect fifth interval away from the first oscillator. In this way, you thicken the sound of the synth by playing either an interval (like 4th or 5th) as if it's a chord. You could also try setting the pitches to be almost the same but slightly detuned, which will add a neat warbly sound.  
  
---
## How the code works
---
The JUCE framework provides a great starting point for music plugins. I'll explain how this code is structured from the top down, starting with what the framework handles automatically when creating a project.  
  
To start with, there is 2 main files: the plugin processor, and plugin editor. The plugin processor will repeatedly call the 'processBlock' function in order to write audio info to the output buffer. For this project, it writes the output of the synthesizer to the output buffer (to be sent to the speakers), and it updates the parameters that we control via the gui every cycle. the plugin editor is the basis of the gui. Structurally that's the basis of the JUCE framework. the other source files extend on the base classes and functions provided by JUCE.  
  
As for my own part, I structured the code such that the synth could be easily extended. From the plugin processor, the synth voice class is called. This contains a processing chain which handles everything sequentially. If we want to add a fourth oscillator, or another filter, all we need to do is add it into the processor chain (voiceProcessChain). This chain contains several instantiations of the CustomOsc class, a ladder filter, and our gain control. Each CustomOsc instantiation has its own processor chain (oscProcessChain) with a basic oscillator and gain control.  
  
The goal with structuring things this way is to make it very easy to keep adding in new features. Anything else I decide to add can be placed in a new class and then added to the synth with only a few lines of code.  
