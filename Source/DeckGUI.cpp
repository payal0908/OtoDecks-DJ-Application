/*
  ==============================================================================

    DeckGUI.cpp
    Created: 24 Jan 2021 2:56:53pm
    Author:  Payal Khandelwal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager& formatManagerToUse,
                 AudioThumbnailCache& cacheToUse) : player(_player),
                                                    waveformDisplay(formatManagerToUse, cacheToUse)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    
    addAndMakeVisible(roomSlider);
    addAndMakeVisible(dampSlider);
    addAndMakeVisible(wetSlider);
    addAndMakeVisible(drySlider);
    
    addAndMakeVisible(waveformDisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    roomSlider.addListener(this);
    dampSlider.addListener(this);
    wetSlider.addListener(this);
    drySlider.addListener(this);
    
    volSlider.setSliderStyle(Slider::SliderStyle::LinearVertical); // setting slider as a vertical slider
    volSlider.setRange(0.0,1.0); // setting range
    volSlider.setValue(0.7); // setting default value
    
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical); // setting slider as a vertical slider
    speedSlider.setRange(0.0,3.0);
    speedSlider.setValue(1.0);
    
    posSlider.setSliderStyle(Slider::SliderStyle::LinearVertical); // setting slider as a vertical slider
    posSlider.setRange(0.0,1.0);
    
    roomSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    roomSlider.setRange(0.0, 1.0);
    
    dampSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    dampSlider.setRange(0.0, 1.0);
    
    wetSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    wetSlider.setRange(0.0, 1.0);
    
    drySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    drySlider.setValue(0.5);
    drySlider.setRange(0.0, 1.0);
    
    startTimer(400);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    //setting custom look and feel to the sliders
    otherLookAndFeel.setColour(Slider::thumbColourId, Colours::indianred);
    volSlider.setLookAndFeel(&otherLookAndFeel);
    speedSlider.setLookAndFeel(&otherLookAndFeel);
    posSlider.setLookAndFeel(&otherLookAndFeel);
    
    reverbLookAndFeel.setColour(Slider::thumbColourId, Colours::blueviolet);
    roomSlider.setLookAndFeel(&reverbLookAndFeel);
    dampSlider.setLookAndFeel(&reverbLookAndFeel);
    wetSlider.setLookAndFeel(&reverbLookAndFeel);
    drySlider.setLookAndFeel(&reverbLookAndFeel);
    
        
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8;
    
    waveformDisplay.setBounds(0, 0, getWidth(), rowH*2);
    
    playButton.setBounds(0, rowH*2, getWidth()/3, rowH);
    playButton.setColour(ComboBox::outlineColourId, Colours::darkgreen);
    playButton.setColour(TextButton::buttonColourId, Colours::green);
    
    stopButton.setBounds(0, rowH*3, getWidth()/3, rowH);
    stopButton.setColour(ComboBox::outlineColourId, Colours::darkred);
    stopButton.setColour(TextButton::buttonColourId, Colours::red);
    
    loadButton.setBounds(0, rowH*4, getWidth()/3, rowH);
    loadButton.setColour(ComboBox::outlineColourId, Colours::black);
    
    volSlider.setNumDecimalPlacesToDisplay(3);
    volSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, volSlider.getTextBoxHeight());
    volSlider.setBounds(getWidth()/3, rowH*2, getWidth()/3, rowH * 3);
    volSlider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
    
    speedSlider.setNumDecimalPlacesToDisplay(3);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, speedSlider.getTextBoxHeight());
    speedSlider.setBounds(getWidth()/2, rowH*2, getWidth()/3, rowH*3);
    speedSlider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
    
    posSlider.setNumDecimalPlacesToDisplay(3);
    posSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, posSlider.getTextBoxHeight());
    posSlider.setBounds(getWidth()/1.5, rowH*2, getWidth()/3, rowH*3);
    posSlider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
    
    roomSlider.setNumDecimalPlacesToDisplay(2);
    roomSlider.setBounds(0, rowH*5, getWidth()/4, rowH*3);
    roomSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, roomSlider.getTextBoxHeight());
    roomSlider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
    
    dampSlider.setNumDecimalPlacesToDisplay(2);
    dampSlider.setBounds(getWidth()/4, rowH*5, getWidth()/4, rowH*3);
    dampSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, dampSlider.getTextBoxHeight());
    dampSlider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
    
    wetSlider.setNumDecimalPlacesToDisplay(2);
    wetSlider.setBounds(getWidth()/2, rowH*5, getWidth()/4, rowH*3);
    wetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, wetSlider.getTextBoxHeight());
    wetSlider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
    
    drySlider.setNumDecimalPlacesToDisplay(2);
    drySlider.setBounds(getWidth()/1.35, rowH*5, getWidth()/4, rowH*3);
    drySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, posSlider.getTextBoxHeight());
    drySlider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);
    
}

void DeckGUI::buttonClicked(Button* button)
{
    if(button == &playButton)
    {
        //std::cout<<"Play button was clicked"<<std::endl;
        player->start();
    }
    if(button == &stopButton)
    {
        //std::cout<<"Stop button was clicked"<<std::endl;
        player->stop();
    }
    if(button == &loadButton)
    {
        FileChooser chooser{"Select a file..."};
        if(chooser.browseForFileToOpen())
        {
            player->loadURL(URL{chooser.getResult()});
            waveformDisplay.loadURL(URL{chooser.getResult()});
        }

    }
}

void DeckGUI::sliderValueChanged(Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    if(slider == &roomSlider)
    {
        player->setRoom(slider->getValue());
        //player->setFreeze(slider->getValue());
    }
    if(slider == &dampSlider)
    {
        player->setDry(slider->getValue());
    }
    if(slider == &wetSlider)
    {
        player->setWet(slider->getValue());
    }
    if(slider == &drySlider)
    {
        player->setDry(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}
void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if(files.size() == 1)
    {
        player->loadURL(URL{File{files[0]}});
        waveformDisplay.loadURL(URL{File{files[0]}});
    }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

void DeckGUI::loadFileToPlayer(URL trackURL)
{
    player->loadURL(trackURL);
    waveformDisplay.loadURL(trackURL);
}
