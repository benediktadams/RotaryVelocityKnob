/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"



class RotaryVelocityKnob  : public Component,
                            private Value::Listener
{
public:
    RotaryVelocityKnob();

    double getValue() const;
    Value& getValueObject();
    void   setValue (double value, NotificationType notification = sendNotificationAsync);
    void   setRange (double minimum, double maximum, double interval=0);
    void   setNormalisableRange (NormalisableRange<double> newRange);

    void paint (Graphics& g) override;

    bool hitTest (int x, int y) override;

    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;
    void mouseWheelMove (const MouseEvent &, const MouseWheelDetails &) override;

    std::function<void()> onValueChange;
    std::function<void()> onDragStart;
    std::function<void()> onDragEnd;

private:
    void valueChanged (Value&) override;

    Value value;
    NormalisableRange<double> range;

    double lastAngle = 0;

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
