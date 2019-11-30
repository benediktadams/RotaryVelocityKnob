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
    Slider::RotaryParameters rot;
    rot.stopAtEnd = true;
    rot.startAngleRadians = (0.0f);
    rot.endAngleRadians = MathConstants<float>::twoPi;

    setSliderStyle(Slider::Rotary);
    setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
   
    setRotaryParameters(rot);
    
    //these don't have any effect when SliderStyle is set to Slider::Rotary
    //use Slider::RotaryHorizontalVerticalDrag to test, what the difference in behaviour is with these
    //==========================================
    setVelocityBasedMode(true);
    setVelocityModeParameters(1.35, 1, 0.023, false);
    setSliderSnapsToMousePosition(false);
    //==========================================
    
    setRange(60, 240);
    setValue(120);

}



bool RotaryVelocityKnob::hitTest(int x, int y)
{
    return touchPath.contains(x, y);
}


void RotaryVelocityKnob::paint(Graphics &g)
{
    auto area = getLocalBounds().toFloat();

    auto wheel = ImageCache::getFromMemory(BinaryData::TempoWheel_png , BinaryData::TempoWheel_pngSize);
    auto imgArea = area.reduced(getWidth() * (0.05f));
    
    g.drawImage(wheel, imgArea, RectanglePlacement::centred);
   
    
    {
        Graphics::ScopedSaveState save (g);
        
        auto rotation = jmap (Slider::getValue(),
                                 Slider::getRange().getStart(),
                                 Slider::getRange().getEnd(),
                                 (double)Slider::getRotaryParameters().startAngleRadians,
                                 (double)Slider::getRotaryParameters().endAngleRadians);
        
        AffineTransform rot;
        rot = rot.rotated(rotation, area.getCentreX(), area.getCentreY());
        
        g.addTransform(rot);
        auto overlay = ImageCache::getFromMemory(BinaryData::TempoWheelOverlay_png, BinaryData::TempoWheelOverlay_pngSize);
        g.drawImage(overlay, area.reduced(area.getWidth() * (0.09f)), RectanglePlacement::centred);

    
    }
   
    g.setColour(Colours::white);
    g.setFont(20.0f);
    g.drawText(String(getValue()), area, Justification::centred);

}

void RotaryVelocityKnob::resized()
{
    auto area = getLocalBounds().toFloat();
    
    touchPath.clear();
    touchPath.addEllipse(area);
    
    Slider::resized();
}


//============================================================
//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(&rotaryKnob);
    
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
