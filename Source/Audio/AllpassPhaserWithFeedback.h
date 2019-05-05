/*
  ==============================================================================

    AllpassPhaserWithFeedback.h
    Created: 1 Dec 2017 11:43:03am
    Author:  KrotosDevMacbook

  ==============================================================================
*/

#ifndef ALLPASSPHASERWITHFEEDBACK_H_INCLUDED
#define ALLPASSPHASERWITHFEEDBACK_H_INCLUDED

#include "ModulatedAllpassFilter.h"
#include "JuceHeader.h"


enum Channels
{
    left = 0,
    right,
    numStereoChannels
};


class AllpassPhaserWithFeedback
{
public:
    
    AllpassPhaserWithFeedback();
    ~AllpassPhaserWithFeedback();

    void processBlock(juce::AudioSampleBuffer& inputBuffer);
    
    void prepareToPlay(int blockSize, int sampleRate);
    
    void setModulationRate(float newRate);
    
    void setFeedbackLevel(float newFeedback);
    
    void setDepthLevel(float newDepth);
    
    void reset();
    
private:
    
    int m_numberOfFilters { 20 };
    
    float m_feedbackLevel { 0.f };
    float m_dryWetLevel { 1.f };    
    
    float m_modulationRate { 0.f };
    
    std::array<float, Channels::numStereoChannels> m_previousFilterChainStereoOutput;
    
    std::array<std::vector<std::unique_ptr<ModulatedAllpassFilter>>, Channels::numStereoChannels> m_stereoAllpassFilterChain;
};




#endif  // ALLPASSPHASERWITHFEEDBACK_H_INCLUDED
