/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 21 Jan 2021 6:57:36pm
    Author:  Payal Khandelwal

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

using namespace juce;

class DJAudioPlayer : public AudioSource {
public:
    
    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();
    
    //==============================================================================
    /**Prepares the source to play and initialises any resources the source might need*/
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    /**Called repeatedly to fetch subsequent blocks of audio data*/
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    /**Allows the source to release anything it no longer needs after playback has stopped*/
    void releaseResources() override;
    
    /**creates a reader for the audio file and takes URL as the input argument*/
    void loadURL(URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);
    
    void start();
    void stop();
    
    /**Sets the room size*/
    void setRoom(float size);
    
    /**sets the damp level*/
    void setDamp(float damp);
    
    /**sets the wet level*/
    void setWet(float wet);
    
    /**sets the dry level*/
    void setDry(float dry);
    
    /**Get the relative position of the playhead*/
    double getPositionRelative();
    
    /**gets the song length in seconds*/
    double getSongDuration();
    
private:
    
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, false,2};
    ReverbAudioSource reverbSource{&resampleSource, false};
    Reverb::Parameters reverbParam;
    
    
};
