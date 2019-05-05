 /*
  ==============================================================================

    AllpassPhaserWithFeedback.cpp
    Created: 1 Dec 2017 11:43:03am
    Author:  KrotosDevMacbook

  ==============================================================================
*/

#include "AllpassPhaserWithFeedback.h"


AllpassPhaserWithFeedback::AllpassPhaserWithFeedback()
{
    
    m_previousFilterChainStereoOutput.fill(0.f);
    
    for (int chanNum = 0; chanNum < Channels::numStereoChannels; ++chanNum)
    {
        for (int filterNum = 0; filterNum < m_numberOfFilters; ++filterNum)
        {
            m_stereoAllpassFilterChain[chanNum].push_back(std::make_unique<ModulatedAllpassFilter>());
        }
    }
}


AllpassPhaserWithFeedback::~AllpassPhaserWithFeedback()
{
    
}

void AllpassPhaserWithFeedback::processBlock(juce::AudioSampleBuffer& inputBuffer)
{
    
    int numSamples = inputBuffer.getNumSamples();
    int numChannels = inputBuffer.getNumChannels();
    
    
    for (int chanNum = 0; chanNum < numChannels; ++chanNum)
    {
        float* inputChannelData = inputBuffer.getWritePointer(chanNum);
        
        for (int sampleNum = 0; sampleNum < numSamples; ++sampleNum)
        {
            float filterOutput = inputChannelData[sampleNum] + m_feedbackLevel * m_previousFilterChainStereoOutput[chanNum];
            
            for (int filterStage = 0; filterStage < m_numberOfFilters; ++filterStage)
            {
               filterOutput = m_stereoAllpassFilterChain[chanNum][filterStage]->getNextSample(filterOutput);
            }
            
//            float filterChainOutputMixedWithFeedback = (1.f - m_feedbackLevel) * filterOutput + m_feedbackLevel * m_previousFilterChainOutput;
//            float crossFadedSample =  m_dryWetLevel * filterChainOutputMixedWithFeedback + (1.f - m_dryWetLevel) * inputChannelData[sampleNum];

            m_previousFilterChainStereoOutput[chanNum] = filterOutput;
            
            float crossFadedSample =  m_dryWetLevel * filterOutput + (1.f - m_dryWetLevel) * inputChannelData[sampleNum];

            inputChannelData[sampleNum] = crossFadedSample;
        }
    }
}



void AllpassPhaserWithFeedback::prepareToPlay(int blockSize, int sampleRate)
{
    for (int chanNum = 0; chanNum < Channels::numStereoChannels; ++chanNum)
    {
        for (int filterNum = 0; filterNum < m_numberOfFilters; ++filterNum)
        {
            m_stereoAllpassFilterChain[chanNum][filterNum]->reset();
            m_stereoAllpassFilterChain[chanNum][filterNum]->prepareToPlay(blockSize, sampleRate);
        }
    }
}

void AllpassPhaserWithFeedback::setModulationRate(float newRate)
{
    for (int chanNum = 0; chanNum < Channels::numStereoChannels; ++chanNum)
    {
        for (int filterNum = 0; filterNum < m_numberOfFilters; ++filterNum)
        {
            m_stereoAllpassFilterChain[chanNum][filterNum]->setModulationRate(newRate);
        }
    }
}

void AllpassPhaserWithFeedback::setFeedbackLevel(float newFeedback)
{
    m_feedbackLevel = std::min(newFeedback, 1.f);
    m_feedbackLevel = std::max(m_feedbackLevel, 0.f);
}


void AllpassPhaserWithFeedback::setDepthLevel(float newDepth)
{
    m_dryWetLevel = std::min(newDepth, 1.f);
    m_dryWetLevel = std::max(m_dryWetLevel, 0.f);
}


void AllpassPhaserWithFeedback::reset()
{
    m_previousFilterChainStereoOutput.fill(0.f);
    
    for (int chanNum = 0; chanNum < Channels::numStereoChannels; ++chanNum)
    {
        for (int filterNum = 0; filterNum < m_numberOfFilters; ++filterNum)
        {
            m_stereoAllpassFilterChain[chanNum][filterNum]->reset();
        }
    }
}
