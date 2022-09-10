/*
  ==============================================================================

    WaveformDisplay.h
    Created: 25 Jan 2021 2:18:18pm
    Author:  Payal Khandelwal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

//==============================================================================
/*
*/
class WaveformDisplay  : public Component,
                         public ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager& formatManagerTouse,
                    AudioThumbnailCache& cacheToUse);
    /**Destructor*/
    ~WaveformDisplay() override;
    
    /**Draws the background of the component*/
    void paint (Graphics&) override;
    
    /**Sets the bounds for all the components*/
    void resized() override;
    
    /**Receives the callback*/
    void changeListenerCallback(ChangeBroadcaster *source) override;
    
    /**Loads the audio URL to display the waveform*/
    void loadURL(URL audioURL);
    
    /** set the relative postion of the playhead*/
    void setPositionRelative(double pos);

private:
    AudioThumbnail audioThumb;
    bool  fileLoaded;
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
