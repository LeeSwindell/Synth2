# JUCE Synthesizer

## Why?

Well. I wanted to make a synth. Who wouldn't? I've played drums, guitar, piano,
and synths for years.

"What I cannot create, I do not understand" - Richard Feynman

I like to learn, so by extension I like to create!

## Features

![Custom GUI](https://github.com/LeeSwindell/Synth2/blob/main/images/GUI.png)  

Here's the beautifully designed gui for our synth. It has 3 oscillators, with 6
wavetypes - sine, square, sawtooth, triangle, wide/narrow pulse. For each
oscillator, we can control the relative gain/pitch. There is also controls for
envelope filtering - the classic Attack, Decay, Sustain, and Release. Last,
there is an implementation of a lowpass filter called a Ladder Filter, which the
cuttoff, resonanace, and drive knobs control. 

## How to use

If you're completely new to C++, I'd recommend finding a better guide for
compiling C++ code. After that's sorted, you'll need to install JUCE.


[Juce installation](https://juce.com/get-juce/).

Once you install JUCE, build the projucer using cmake, or whatever platform
specific tool you have for C++. The projucer is a GUI for managing development
with the JUCE framework. Then, clone this repo.

```git clone https://github.com/LeeSwindell/Synth2```


Now that you've got the code, open the Synth2.jucer file in the projucer. The
projucer will generate the files needed for your platform. Build the project
using Xcode for mac, Make for linux, etc.

Open your DAW (Logic Pro/Pro tools/Ableton live). Find the software instruments,
and import the executable as a new instrument and voila! If there's any problems
I'd check the fairly extensive JUCE docs [here](https://juce.com/learn/documentation/)

