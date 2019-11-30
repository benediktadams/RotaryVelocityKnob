/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"



class RotaryVelocityKnob : public Slider
{
public:
    RotaryVelocityKnob();
    
    void paint(Graphics& g) override;
    void resized() override;
    bool hitTest(int x, int y) override;
    
    
private:
    Path touchPath; //for hitTest

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryVelocityKnob)
};


class MainComponent   : public Component
{
public:
  
    MainComponent();
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    RotaryVelocityKnob rotaryKnob;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
