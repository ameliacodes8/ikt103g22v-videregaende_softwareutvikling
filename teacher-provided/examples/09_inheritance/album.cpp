#include <iostream>
#include <string>

#include "album.h"

// The base class constructor is called using : (colon)
Album::Album(std::string owner, std::string artist) : Item(std::move(owner))
{
    this->artist = std::move(artist);
}

std::string Album::Artist() const
{
    return artist;
}

void Album::Artist(std::string artist)
{
    this->artist = std::move(artist);
}

void Album::Print() const
{
    // Call the base class implementation using the class name
    Item::Print();
    std::cout << ", artist: " << artist;
}
