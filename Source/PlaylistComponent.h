/*
  ==============================================================================

    PlaylistComponent.h
    Created: 27 Jan 2021 5:11:17pm
    Author:  Payal Khandelwal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "PlaylistEntry.h"
#include "DeckGUI.h"
#include "DJAudioPlayer.h"
#include <iostream>
#include <fstream>
#include "FileReader.h"

using namespace juce;

//==============================================================================
/*
*/
class PlaylistComponent  : public Component,
                           public TableListBoxModel,
                           public Button::Listener,
                           public TextEditor::Listener
{
public:
    PlaylistComponent(DeckGUI* _deckGUI1,
                      DeckGUI* _deckGUI2,
                      DJAudioPlayer* _audioPlayer);
    /**Destructor for class*/
    ~PlaylistComponent() override;
    
    /**Draws the component*/
    void paint (Graphics&) override;
    
    /**Sets the bounds for all the components*/
    void resized() override;
    
    /**Returns the number of rows in trackEntries*/
    int getNumRows() override;
    
    /**Draws the background of the tableComponent*/
    void paintRowBackground(Graphics& , int rowNumber, int width, int height, bool rowIsSelected) override;
    
    /**Draws each cell inside the tableComponent*/
    void paintCell(Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    
    /**updates the content in the cell and is called whenever the cell needs to be updated*/
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    /**Function is called when the button is clicked*/
    void buttonClicked(Button* button) override;
    
private:
    
    TableListBox tableComponent;
    std::vector<PlaylistEntry> trackEntries;
    
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    DJAudioPlayer* audioPlayer;
    
    TextButton loadInDeck1Button{"load -> Deck 1"};
    TextButton loadInDeck2Button{"load -> Deck 2"};
    TextButton importTracksButton{"Import Tracks to Playlist"};
    TextEditor searchForTracksText;
    
    FileReader fileReader;
    
    void searchForTracks(String text);
    void importToPlaylist();
    String getDuration(URL trackURL);
    void deleteEntry(int id);
    void loadInDeck(DeckGUI* deckGUI);
    void writeToFile();
    void readFromFile();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
