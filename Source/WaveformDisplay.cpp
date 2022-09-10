/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 25 Jan 2021 2:18:18pm
    Author:  Payal Khandelwal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerTouse,
                                 AudioThumbnailCache& cacheToUse) :
                                 audioThumb(1000, formatManagerTouse, cacheToUse),
                                 fileLoaded(false),
                                 position(0)
{
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (Colour(0xFF3306DC));
    g.setColour(Colours::coral);
    if(fileLoaded)
    {
        audioThumb.drawChannel(g,
                               getLocalBounds(),
                               0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);
        g.setColour(Colours::lightgreen);
        g.drawRect(position * getWidth(), 0, getWidth()/20, getHeight());
    }
    else
    {
        g.setFont (20.0f);
        g.setColour(Colours::orange);
        g.drawText ("File not loaded...", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{

}

void WaveformDisplay::loadURL(URL audioURL)
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
    if(fileLoaded)
    {
        std::cout << "wfd: loaded" << std::endl;
        repaint();
    }
    else
    {
        std::cout << "wfd: not loaded" << std::endl;
    }
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster *source)
{
    std::cout << "Change recieved" << std::endl;
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if(pos != position)
    {
        position = pos;
        repaint();
    }
}
