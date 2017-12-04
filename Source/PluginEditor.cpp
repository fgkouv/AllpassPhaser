/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
AllpassPhaserAudioProcessorEditor::AllpassPhaserAudioProcessorEditor (AllpassPhaserAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p)
{
    m_textFont = Font(Typeface::createSystemTypefaceFor (BinaryData::SHPinscherRegular_otf, BinaryData::SHPinscherRegular_otfSize));
    
    m_rateLabel.setText("RATE", dontSendNotification);
    m_rateLabel.setFont(m_labelFontSize);
    m_rateLabel.setFont(m_textFont);
    m_rateLabel.setColour(Label::ColourIds::textColourId, Colours::black);
    m_rateLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&m_rateLabel);
    
    
    m_feedbackLabel.setText("FDBCK", dontSendNotification);
    m_feedbackLabel.setFont(m_labelFontSize);
    m_feedbackLabel.setFont(m_textFont);
    m_feedbackLabel.setColour(Label::ColourIds::textColourId, Colours::black);
    m_feedbackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&m_feedbackLabel);
    
    m_dryWetLabel.setText("MIX", dontSendNotification);
    m_dryWetLabel.setFont(m_labelFontSize);
    m_dryWetLabel.setFont(m_textFont);
    m_dryWetLabel.setColour(Label::ColourIds::textColourId, Colours::black);
    m_dryWetLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&m_dryWetLabel);
    
    
    addAndMakeVisible(&m_rateSlider);
    m_rateSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    m_rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    m_rateSlider.setTextValueSuffix(" Hz");
    m_rateSlider.setPopupDisplayEnabled(true, this);
    m_rateSlider.setLookAndFeel(&m_customLAF);
    m_rateSliderAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "rate", m_rateSlider);
    
    addAndMakeVisible(&m_feedbackSlider);
    m_feedbackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    m_feedbackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    m_feedbackSlider.setPopupDisplayEnabled(true, this);
    m_feedbackSlider.setLookAndFeel(&m_customLAF);
    m_feedbackSliderAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "feedback", m_feedbackSlider);


    
    addAndMakeVisible(&m_dryWetSlider);
    m_dryWetSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    m_dryWetSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    m_dryWetSlider.setTextValueSuffix(" ms");
    m_dryWetSlider.setPopupDisplayEnabled(true, this);
    m_dryWetSlider.setLookAndFeel(&m_customLAF);
    m_dryWetSliderAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "dryWet", m_dryWetSlider);

    setSize (400, 300);
}

AllpassPhaserAudioProcessorEditor::~AllpassPhaserAudioProcessorEditor()
{
}

//==============================================================================
void AllpassPhaserAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    float width = getWidth();
    float height = getHeight();
    
    juce::Rectangle<int> logoArea = juce::Rectangle<int>(0.6 * width, 0.75 * height, 0.3f * width, 0.2f * height);
    
    Font logoFont = Font(Typeface::createSystemTypefaceFor (BinaryData::Lombok_otf, BinaryData::Lombok_otfSize));
    
    g.setFont(logoFont);
    g.setFont(28.f);
    g.drawFittedText("QUA.REJ", logoArea, juce::Justification::centredBottom, 1);
    
    
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 10.f, 1.f);
    
    g.setFont(logoFont);
    g.setFont(20.f);
    g.drawFittedText("ALLPASS  |  PHASER", m_titleArea, Justification::centredLeft, 1);
}

void AllpassPhaserAudioProcessorEditor::resized()
{
    float width = getWidth();
    
    m_titleArea = juce::Rectangle<int>(5, 5, width, 30);
    
    float horizontalOffset = 10.f;
    float knobSize = 0.33f * (width - 2 * horizontalOffset);
    float xPos = 10.f;
    float yPos = m_titleArea.getBottom() + 10;
    
    float labelHeight = m_labelFontSize + 3.f;
    
    m_rateLabel.setBounds(xPos, yPos, knobSize, labelHeight);
    yPos += labelHeight;
    m_rateSlider.setBounds(xPos, yPos, knobSize, knobSize);
    
    xPos += knobSize;
    yPos -= labelHeight;
    m_feedbackLabel.setBounds(xPos, yPos, knobSize, labelHeight);
    yPos += labelHeight;
    m_feedbackSlider.setBounds(xPos, yPos, knobSize, knobSize);
    
    xPos += knobSize;
    yPos -= labelHeight;
    m_dryWetLabel.setBounds(xPos, yPos, knobSize, labelHeight);
    yPos += labelHeight;
    m_dryWetSlider.setBounds(xPos, yPos, knobSize, knobSize);
}
