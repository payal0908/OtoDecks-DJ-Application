/*
  ==============================================================================

    FileReader.h
    Created: 18 Feb 2021 12:12:41am
    Author:  Payal Khandelwal

  ==============================================================================
*/

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "PlaylistEntry.h"

class FileReader
{
    
public:
    /**Reads a string line and separates it into tokens according to the separator
     Input arguement csvLine is of type string, line from a file that the function tokenises, and a separator of type character
     Returns a vector of type string*/
    std::vector<String> tokenise(std::string csvLine, char separator);
    
    /**Converts a vector of strings to a PlaylistEntry object
     Input argument is a vector of strings*/
    PlaylistEntry stringsToPlaylistEntry(std::vector<String> tokens);
    
};
