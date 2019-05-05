/*
  ==============================================================================

    ModulatedAllpassFilter.cpp
    Created: 1 Dec 2017 11:41:15am
    Author:  KrotosDevMacbook

  ==============================================================================
*/

#include "ModulatedAllpassFilter.h"


ModulatedAllpassFilter::ModulatedAllpassFilter()
{
    
}


ModulatedAllpassFilter::~ModulatedAllpassFilter()
{
    
}


float ModulatedAllpassFilter::getNextSample(float inputSample)
{
    
    float modulatorSample = m_LFO.getNextSample();
    
    float outputSample = inputSample * modulatorSample + m_previousInput - m_previousOutput * modulatorSample;
    
    m_previousInput = inputSample;
    m_previousOutput = outputSample;
    
    return outputSample;
}

void ModulatedAllpassFilter::processBlock(juce::AudioSampleBuffer& inputBuffer)
{
    
}


void ModulatedAllpassFilter::setModulationRate(float newRate)
{
    m_LFO.setFrequency(newRate);
}


void ModulatedAllpassFilter::setModulationWave(WaveShapes newWaveshape)
{
    m_LFO.setWaveShape(newWaveshape);
}



void ModulatedAllpassFilter::prepareToPlay(int blockSize, int sampleRate)
{
    m_LFO.setSampleRate(sampleRate);
}


void ModulatedAllpassFilter::reset()
{
    m_previousInput = 0.f;
    m_previousOutput = 0.f;
    
    
    m_LFO.resetPhase();
}
