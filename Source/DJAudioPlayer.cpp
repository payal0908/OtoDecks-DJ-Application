/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 21 Jan 2021 6:57:36pm
    Author:  Payal Khandelwal

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager) : formatManager(_formatManager)
{
    reverbParam.roomSize = 0;
    reverbParam.damping = 0;
    reverbParam.wetLevel = 0;
    reverbParam.dryLevel = 0.5;
    reverbSource.setParameters(reverbParam);
}
DJAudioPlayer::~DJAudioPlayer()
{
    
}

//==============================================================================
void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void DJAudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    reverbSource.getNextAudioBlock(bufferToFill);
}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
    reverbSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));// creates a reader for the audio file
    if (reader != nullptr) //good file!
    {
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true));
        transportSource.setSource(newSource.get(),0,nullptr,reader->sampleRate);
        readerSource.reset(newSource.release()); 
    }
}
void DJAudioPlayer::setGain(double gain)
{
    if(gain < 0 || gain > 1)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1"<<std::endl;
    }else{
        transportSource.setGain(gain);
    }
}
void DJAudioPlayer::setSpeed(double ratio)
{
    if(ratio < 0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlajer::setSpeed ratio should be between 0 and 100"<<std::endl;
    }else{
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
    if(pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlajer::setPositionRelative pos should be between 0 and 1"<<std::endl;
    }else{
        double posInSecs = transportSource.getLengthInSeconds()*pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start()
{
    transportSource.start();
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
}

void DJAudioPlayer::setRoom(float size)
{
    reverbParam.roomSize = size;
    reverbSource.setParameters(reverbParam);
}

void DJAudioPlayer::setDamp(float damp)
{
    reverbParam.damping = damp;
    reverbSource.setParameters(reverbParam);
}

void DJAudioPlayer::setWet(float wet)
{
    reverbParam.wetLevel = wet;
    reverbSource.setParameters(reverbParam);
}

void DJAudioPlayer::setDry(float dry)
{
    reverbParam.dryLevel = dry;
    reverbSource.setParameters(reverbParam);
}

double DJAudioPlayer::getPositionRelative()
{
    if(transportSource.getCurrentPosition()>0)
        return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    else
        return 0;
}

double DJAudioPlayer::getSongDuration()
{
    return transportSource.getLengthInSeconds();
}
