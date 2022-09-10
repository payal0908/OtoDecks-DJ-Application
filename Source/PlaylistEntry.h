/*
  ==============================================================================

    PlaylistEntry.h
    Created: 16 Feb 2021 1:18:26pm
    Author:  Payal Khandelwal

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

using namespace juce;

class PlaylistEntry
{
public:
    PlaylistEntry(File file_name);
    
    File filename;
    String trackName;
    URL file_url;
    String duration;
};
