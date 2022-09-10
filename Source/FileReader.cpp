/*
  ==============================================================================

    FileReader.cpp
    Created: 18 Feb 2021 12:12:41am
    Author:  Payal Khandelwal

  ==============================================================================
*/

#include "FileReader.h"

std::vector<String> FileReader::tokenise(std::string csvLine, char separator)
{
    std::vector<String> tokens;
    signed int start, end;
    std::string token;
    start = (int)csvLine.find_first_not_of(separator, 0); // finds the first index of string that is not of the separator
    do{
        end = (int)csvLine.find_first_of(separator,start); // next position of separator after start
        if(start == csvLine.length() || start == end) break; // checks if start has reached the end of the string
        if(end>=0) token = csvLine.substr(start, end-start); // if separator is found we extract the token
        else token = csvLine.substr(start, csvLine.length()-start);
        tokens.push_back(token); // adding the extracted token into the vector
        start = end + 1;
    }while(end>0);
    
    return tokens;
}

PlaylistEntry FileReader::stringsToPlaylistEntry(std::vector<String> tokens)
{
    String filePathName;
    String duration;
        
    if(tokens.size() != 2) // checking if the size of tokens
    {
        std::cout << "bad line" << std::endl;
    }
    filePathName = tokens[0]; // first token is set as file path
    duration = tokens[1]; // second token is set at the duration of the song
    File file{filePathName}; // creating file variable using file path
    PlaylistEntry pe{file}; // initializing playlistEntry object
    pe.duration = duration;
    
    return pe;
}
