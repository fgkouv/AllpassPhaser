/*
  ==============================================================================

    ModulatedAllpassFilter.h
    Created: 1 Dec 2017 11:41:15am
    Author:  KrotosDevMacbook

  ==============================================================================
*/

#ifndef MODULATEDALLPASSFILTER_H_INCLUDED
#define MODULATEDALLPASSFILTER_H_INCLUDED

#include "JuceHeader.h"
#include "WavetableOscillator.h"


class ModulatedAllpassFilter
{
public:
    
    ModulatedAllpassFilter();
    ~ModulatedAllpassFilter();

    float getNextSample(float inputSample);
    
    void processBlock(juce::AudioSampleBuffer& inputBuffer);
    
    void prepareToPlay(int blockSize, int sampleRate);
    
    void setModulationRate(float newRate);
    void setModulationWave(WaveShapes newWaveshape);
    
    
    void reset();
    
private:
    
    WavetableOscillator m_LFO;
    float m_previousInput   { 0.f };
    float m_previousOutput  { 0.f };
    
};



#endif  // MODULATEDALLPASSFILTER_H_INCLUDED
