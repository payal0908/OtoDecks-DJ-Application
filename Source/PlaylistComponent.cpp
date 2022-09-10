/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 27 Jan 2021 5:11:17pm
    Author:  Payal Khandelwal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deckGUI1,
                                     DeckGUI* _deckGUI2,
                                     DJAudioPlayer* _audioPlayer) : deckGUI1(_deckGUI1),
                                                                    deckGUI2(_deckGUI2),
                                                                    audioPlayer(_audioPlayer)
{
    
    //adding and making the components visible
    addAndMakeVisible(loadInDeck1Button);
    addAndMakeVisible(loadInDeck2Button);
    addAndMakeVisible(importTracksButton);
    addAndMakeVisible(searchForTracksText);
    
    //adding listeners
    loadInDeck1Button.addListener(this);
    loadInDeck2Button.addListener(this);
    importTracksButton.addListener(this);
    searchForTracksText.addListener(this);

    
    searchForTracksText.setTextToShowWhenEmpty("Search for tracks by name...", Colours::white);
    searchForTracksText.onTextChange = [this](){searchForTracks(
                                                             searchForTracksText.getText()
                                                                );}; // calling function each time there is a change
    
    tableComponent.getHeader().addColumn("Track Title", 1, 500);
    tableComponent.getHeader().addColumn("Duration", 2, 200);
    tableComponent.getHeader().addColumn("", 3, 100);
    
    
    tableComponent.setModel(this);
    
    addAndMakeVisible(tableComponent);
    readFromFile(); // loads the music files into the library

}

PlaylistComponent::~PlaylistComponent()
{
    writeToFile(); // writes to file after program ends
}

void PlaylistComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
    
}

void PlaylistComponent::resized()
{
    // setting position of the components
    tableComponent.setBounds(0, getHeight()/8, getWidth(), 6*getHeight()/8);
    
    importTracksButton.setBounds(3*getWidth()/5, 7*getHeight()/8, 2*getWidth()/5, getHeight()/8);
    importTracksButton.setColour(ComboBox::outlineColourId, Colours::orange);
    
    loadInDeck1Button.setBounds(0, 7*getHeight()/8, getWidth()/5, getHeight()/8);
    loadInDeck1Button.setColour(ComboBox::outlineColourId, Colours::orange);
    loadInDeck2Button.setBounds(getWidth()/5,7*getHeight()/8,getWidth()/5, getHeight()/8);
    loadInDeck2Button.setColour(ComboBox::outlineColourId, Colours::orange);
    
    searchForTracksText.setBounds(0,0,getWidth(),getHeight()/8);
    searchForTracksText.setColour(TextEditor::outlineColourId, Colours::orange);
}

int PlaylistComponent::getNumRows()
{
    return (int)trackEntries.size();
}
void PlaylistComponent::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if(rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
        g.fillAll(Colours::darkgrey);
    }
}
void PlaylistComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if(columnId == 1)
        g.drawText(trackEntries[rowNumber].trackName,2,1,width-4,height,Justification::centredLeft,true);
    if(columnId == 2)
        g.drawText(trackEntries[rowNumber].duration,2,1,width-4,height,Justification::centred,true);
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
{
    // creating delete button
    if(columnId == 3)
    {
        if(existingComponentToUpdate == nullptr)
        {
            TextButton* delBtn = new TextButton{"Delete"};
            delBtn->setColour(ComboBox::outlineColourId, Colours::transparentBlack);
            String id{std::to_string(rowNumber)};
            delBtn->setComponentID(id);
            
            delBtn->addListener(this);
            existingComponentToUpdate = delBtn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    if(button->getButtonText() == "Delete")
    {
        int id = std::stoi(button->getComponentID().toStdString());
        std::cout<<"Delete "<<trackEntries[id].trackName<<std::endl;
        deleteEntry(id);
        tableComponent.updateContent();
    }
    if(button == &loadInDeck1Button)
    {
        std::cout<<"Load in Deck1"<<std::endl;
        loadInDeck(deckGUI1);
    }
    if(button == &loadInDeck2Button)
    {
        std::cout<<"Load in Deck2"<<std::endl;
        loadInDeck(deckGUI2);
    }
    if(button == &importTracksButton)
    {
        std::cout<<"Import tracks"<<std::endl;
        importToPlaylist();
        tableComponent.updateContent();
    }
}

void PlaylistComponent::searchForTracks(String text)
{
    for(int i=0;i<trackEntries.size();i++)
    {
        if(trackEntries[i].trackName.contains(text)) // if the music name contains the text
        {
            tableComponent.selectRow(i);
        }
    }
}

void PlaylistComponent::importToPlaylist()
{
    std::cout<<"importToPlalist called"<<std::endl;
    
    FileChooser filechooser("Select tracks");
    if(filechooser.browseForMultipleFilesToOpen())
    {
        for(const File& file : filechooser.getResults())
        {
            PlaylistEntry newEntry(file);
            URL trackURL(file);
            newEntry.duration = getDuration(trackURL);
            
            trackEntries.push_back(newEntry);
            std::cout<<"File loaded"<<std::endl;
        }
    }
}

String PlaylistComponent::getDuration(URL trackURL)
{
    audioPlayer->loadURL(trackURL);
    int sec = audioPlayer->getSongDuration();
    int min = 0.0;
    min += sec/60;
    sec = sec%60;
    String duration = std::to_string(min)+":"+std::to_string(sec);
    return duration;
}

void PlaylistComponent::deleteEntry(int id)
{
    trackEntries.erase(trackEntries.begin()+id); // deletes the music file from the vector
}

void PlaylistComponent::loadInDeck(DeckGUI *deckGUI)
{
    int row = tableComponent.getSelectedRow();
    deckGUI->loadFileToPlayer(trackEntries[row].file_url);
}

void PlaylistComponent::writeToFile()
{
    std::cout<<"saving to external data"<<std::endl;
    //std::ofstream playlist("./Users/payal/Desktop/OtoDecks_Playlist.txt");
    File file = File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory).getChildFile("OtoDecks_Playlist.txt");
    String fullPath = file.getFullPathName();
    std::ofstream playlist(fullPath.toStdString());
    
    for(PlaylistEntry& entry : trackEntries)
    {
        String fullPath = entry.filename.getFullPathName(); // getting full path of each music file
        playlist << fullPath << ";" << entry.duration << "\n"; // writing to the file in the correct format
    }
}

void PlaylistComponent::readFromFile()
{
    std::cout<<"loading from external data"<<std::endl;
    File file = File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory).getChildFile("OtoDecks_Playlist.txt"); // to get the location of the file
    String fullPath = file.getFullPathName(); // gets the full pathname in string
    std::ifstream playlist(fullPath.toStdString());
    std::string line;

    if(playlist.is_open()) // checking if file is open
    {
        while(std::getline(playlist, line)) // getting each line from the while
        {
            try{
                PlaylistEntry pe = fileReader.stringsToPlaylistEntry(fileReader.tokenise(line, ';')); // tokenising the line, converting it into a playlistEntry object
                trackEntries.push_back(pe); // adding PlaylistEntry object to the vector
            }catch(const std::exception& e)
            {
                std::cout << "Bad data" << std::endl;
            }
        }
    }else{
        std::cout<<"file not open"<<std::endl;
    }
    playlist.close();
    
}
