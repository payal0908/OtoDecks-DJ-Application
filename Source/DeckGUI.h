/*
  ==============================================================================

    DeckGUI.h
    Created: 24 Jan 2021 2:56:53pm
    Author:  Payal Khandelwal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

using namespace juce;
//==============================================================================
/*
*/
class DeckGUI  : public Component,
                 public Button::Listener,
                 public Slider::Listener,
                 public FileDragAndDropTarget,
                 public Timer
{
public:
    
    DeckGUI(DJAudioPlayer* player,
            AudioFormatManager& formatManagerToUse,
            AudioThumbnailCache& cacheToUse);
    
    /**Destructor*/
    ~DeckGUI() override;

    /**Draws the background of the component*/
    void paint (Graphics&) override;
    
    /**Sets the bounds for all the components*/
    void resized() override;
    
    /**Function is called when the button is clicked*/
    void buttonClicked (Button *) override;
    
    /**Function called when slider value changes*/
    void sliderValueChanged (Slider *slider) override;
    
    /**Returns a boolean value to indicate if there is a file being dragged over the component*/
    bool isInterestedInFileDrag (const StringArray &files) override;
    
    /**Loads the audio file in the audio player once the file is dropped*/
    void filesDropped (const StringArray &files, int x, int y) override;
    
    /**Function gets called periodically to update the waveform display*/
    void timerCallback() override;
    
    /**Loads a music file into the audio player by taking the url of the music file as input*/
    void loadFileToPlayer(URL trackURL);
    
private:
    LookAndFeel_V4 otherLookAndFeel;
    LookAndFeel_V4 reverbLookAndFeel;
    
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    
    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    
    Slider roomSlider;
    Slider dampSlider;
    Slider wetSlider;
    Slider drySlider;
    
    DJAudioPlayer* player;
    
    WaveformDisplay waveformDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
