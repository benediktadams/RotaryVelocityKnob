/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//============================================================
//============================================================
RotaryVelocityKnob::RotaryVelocityKnob()
{
    value.addListener (this);
}

double RotaryVelocityKnob::getValue() const
{
    return double (value.getValue());
}

Value& RotaryVelocityKnob::getValueObject()
{
    return value;
}
void RotaryVelocityKnob::setValue (double newValue, NotificationType notification)
{
    value = range.snapToLegalValue (newValue);

    if (notification == sendNotification)
    {
        if (onValueChange)
            onValueChange();
    }
    else if (notification == sendNotificationAsync)
    {
        if (onValueChange)
            MessageManager::callAsync (onValueChange);
    }
}

void RotaryVelocityKnob::setRange (double minimum, double maximum, double interval)
{
    range = { minimum, maximum, interval };
}

void RotaryVelocityKnob::setNormalisableRange (NormalisableRange<double> newRange)
{
    range = newRange;
}

bool RotaryVelocityKnob::hitTest (int x, int y)
{
    auto dist   = getLocalBounds().getCentre().getDistanceFrom ({x, y});
    auto radius = jmin (getWidth(), getHeight()) / 2;
    return dist < radius && dist > radius / 2;
}


void RotaryVelocityKnob::paint(Graphics &g)
{
    auto area = getLocalBounds().toFloat();

    auto wheel = ImageCache::getFromMemory(BinaryData::TempoWheel_png , BinaryData::TempoWheel_pngSize);
    auto imgArea = area.reduced(getWidth() * (0.05f));

    g.drawImage(wheel, imgArea, RectanglePlacement::centred);

    {
        Graphics::ScopedSaveState save (g);

        g.addTransform (AffineTransform::rotation (lastAngle, area.getCentreX(), area.getCentreY()));
        auto overlay = ImageCache::getFromMemory (BinaryData::TempoWheelOverlay_png, BinaryData::TempoWheelOverlay_pngSize);
        g.drawImage (overlay, area.reduced (area.getWidth() * (0.09f)), RectanglePlacement::centred);
    }

    g.setColour(Colours::white);
    g.setFont(20.0f);
    g.drawText (String (getValue()), area, Justification::centred);

}

void RotaryVelocityKnob::mouseDown (const MouseEvent& e)
{
    lastAngle = getLocalBounds().getCentre().toFloat().getAngleToPoint (e.position);

    if (onDragStart)
        onDragStart();
}

void RotaryVelocityKnob::mouseDrag (const MouseEvent& e)
{
    const auto angle = getLocalBounds().getCentre().toFloat().getAngleToPoint (e.position);

    auto diff  = angle - lastAngle;
    if (std::abs (diff) > MathConstants<float>::pi)
        diff = MathConstants<float>::twoPi - diff;

    const auto increment = diff * range.getRange().getLength() / MathConstants<double>::twoPi;

    if (increment >= 1.0)
    {
        setValue (getValue() + std::floor (increment));
        lastAngle = angle;
    }
    if (increment <= -1.0)
    {
        setValue (getValue() + std::ceil (increment));
        lastAngle = angle;
    }
}

void RotaryVelocityKnob::mouseUp (const MouseEvent& e)
{
    if (onDragEnd)
        onDragEnd();

    if (onValueChange)
        onValueChange();
}

void RotaryVelocityKnob::mouseWheelMove (const MouseEvent &, const MouseWheelDetails &)
{
    
}

void RotaryVelocityKnob::valueChanged (Value&)
{
    repaint();
}


//============================================================
//==============================================================================
MainComponent::MainComponent()
{
    rotaryKnob.setRange (60, 240);
    rotaryKnob.setValue (120);

    addAndMakeVisible (rotaryKnob);
    
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
    const auto area = getLocalBounds();
    
    const auto knobSize = jmin(getWidth(), getHeight());
    
    Rectangle<int> knobArea (knobSize, knobSize);
    knobArea.setCentre(area.getCentre());
    
    rotaryKnob.setBounds(area);
}
