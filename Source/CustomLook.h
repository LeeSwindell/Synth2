/*
  ==============================================================================

    CustomLook.h
    Created: 2 Mar 2022 2:27:45pm
    Author:  Lee Swindell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomLook : public juce::LookAndFeel_V4
{
public:
  CustomLook();
    void drawRotarySlider(juce::Graphics&, int, int, int, int, float,
                          const float, const float, juce::Slider&) override;
private:
    float scale;
    juce::Font getCommonMenuFont(float); //returns a default font
};
