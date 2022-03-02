/*
  ==============================================================================

    CustomLook.cpp
    Created: 2 Mar 2022 2:27:45pm
    Author:  Lee Swindell

  ==============================================================================
*/

#include "CustomLook.h"

//initialize the scale of the fonts sand the default slider color
CustomLook::CustomLook()
{
  scale = 1.f; //default scale
  setColour(juce::Slider::thumbColourId, juce::Colours::darkmagenta); //default slider color
}

//drawing each slider to have this kind of style, filled in with solid color and outlined with a dial
void CustomLook::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    double radius = juce::jmin(width / 2, height / 2) - 4.0f;
    double centreX = x + width * 0.5f;
    double centreY = y + height * 0.5f;
    double rx = centreX - radius;
    double ry = centreY - radius;
    double rw = radius * 2.0f;
    double angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    //fill the rotary
    g.setColour(juce::Colours::whitesmoke);
    g.setOpacity(0.13f);
    g.fillEllipse(rx, ry, rw, rw);
    
    //outline the rotary
    g.setColour(juce::Colours::darkmagenta);
    g.drawEllipse(rx, ry, rw, rw, 0.5f);
    
    //draw the knob dial
    juce::Path p;
    double pointerLength = radius * 0.33f;
    double pointerThickness = 5.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY)); //animate
    g.setColour(juce::Colours::seashell); //color of dial
    g.fillPath(p);
}
