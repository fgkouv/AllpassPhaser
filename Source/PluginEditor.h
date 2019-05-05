/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"




class AllpassPhaserLAF
:
public LookAndFeel_V4
{
public:
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        const auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);
        const auto fill    = slider.findColour (Slider::rotarySliderFillColourId);
        
        const auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);
        
        auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
        const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin (8.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;
        
        Path backgroundArc;
        backgroundArc.addCentredArc (bounds.getCentreX(),
                                     bounds.getCentreY(),
                                     arcRadius,
                                     arcRadius,
                                     0.0f,
                                     rotaryStartAngle,
                                     rotaryEndAngle,
                                     true);
        
        g.setColour (outline);
        g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
        
        if (slider.isEnabled())
        {
            Path valueArc;
            valueArc.addCentredArc (bounds.getCentreX(),
                                    bounds.getCentreY(),
                                    arcRadius,
                                    arcRadius,
                                    0.0f,
                                    rotaryStartAngle,
                                    toAngle,
                                    true);
            
            g.setColour (fill);
            g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
        }
        
        
        const float thumbScalingFactor = 1.2f;
        const auto thumbWidth = lineW * thumbScalingFactor;
        const Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - float_Pi * 0.5f),
                                       bounds.getCentreY() + arcRadius * std::sin (toAngle - float_Pi * 0.5f));
        
        g.setColour (slider.findColour (Slider::thumbColourId));
        g.fillEllipse (Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
    }
    
    
    
    void drawToggleButton (Graphics& g, ToggleButton& button, bool isMouseOverButton, bool isButtonDown) override
    {
        
        float width = button.getWidth();
        float height = button.getHeight();
        
        juce::Rectangle<float> bounds(0.f, 0.f, width, height);
        
        
        if (false == button.getToggleState())
        {
            Colour offColour = juce::Colour::fromRGB(50, 70, 80);
            g.setColour(offColour);
        }
        else
        {
            Colour onColour = juce::Colour::fromRGB(178, 99, 0);
            g.setColour(onColour);
        }
        
        g.fillRoundedRectangle(bounds, 8.f);
        
        
        if (true == isMouseOverButton)
        {
            Colour mouseOverColour = juce::Colour::fromRGB(245, 255, 152).withAlpha(0.5f);
            g.setColour(mouseOverColour);
            g.fillRoundedRectangle(bounds, 8.f);
        }
        
        g.setColour(Colours::floralwhite);
        g.drawRoundedRectangle(bounds, 8.f, 1);
        
        g.setColour(Colours::black);
        Font font = Font(Typeface::createSystemTypefaceFor (BinaryData::SHPinscherRegular_otf, BinaryData::SHPinscherRegular_otfSize));
        g.setFont (font);
        juce::Rectangle<int> textArea = juce::Rectangle<int>(5, 0.1f * button.getHeight(), button.getWidth() - 10, 0.8f * button.getHeight());
        
        g.drawFittedText(button.getButtonText(), textArea, Justification::centred, 1);
    }
    
    void drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/) override
    {
        
        Font font = Font(Typeface::createSystemTypefaceFor (BinaryData::SHPinscherRegular_otf, BinaryData::SHPinscherRegular_otfSize));
        
        g.setFont (font);
        g.setFont(button.getHeight() * 0.55f);
        g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                        : TextButton::textColourOffId)
                     .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
        
        const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
        const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;
        
        const int fontHeight = roundToInt (font.getHeight() * 0.6f);
        const int leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
        const int rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
        const int textWidth = button.getWidth() - leftIndent - rightIndent;
        
        if (textWidth > 0)
            g.drawFittedText (button.getButtonText(),
                              leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                              Justification::centred, 2);
            }
    
    
    
};







//==============================================================================




class AllpassPhaserAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    AllpassPhaserAudioProcessorEditor (AllpassPhaserAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~AllpassPhaserAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;
    
private:
    AllpassPhaserAudioProcessor& processor;

    Slider m_rateSlider;
    Slider m_feedbackSlider;
    Slider m_dryWetSlider;
    
    ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m_rateSliderAttachment;
    ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m_feedbackSliderAttachment;
    ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> m_dryWetSliderAttachment;
    
    Label m_rateLabel;
    Label m_feedbackLabel;
    Label m_dryWetLabel;
    
    juce::Rectangle<int> m_titleArea;
    
    Font m_textFont;
    
    int m_labelFontSize { 14 };
    
    AllpassPhaserLAF m_customLAF;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AllpassPhaserAudioProcessorEditor)
};
