/*
  ==============================================================================

    PlaylistEntry.cpp
    Created: 16 Feb 2021 1:18:26pm
    Author:  Payal Khandelwal

  ==============================================================================
*/

#include "PlaylistEntry.h"

using namespace juce;

PlaylistEntry::PlaylistEntry(File file_name) : filename(file_name),
                                               trackName(file_name.getFileNameWithoutExtension()),
                                               file_url(URL{file_name})
{
    
}
