#ifndef ALBUM_H
#define ALBUM_H

#include <string>

#include "item.h"

class Album : public Item
{
public:
    // Constructor
    Album(std::string owner, std::string artist);

    // Getter for artist
    std::string Artist() const;

    // Setter for artist
    void Artist(std::string artist);

    // Utility function that prints object information.
    // const   : The function can not modify the object
    // override: The function overrides an existing implementation from its base class
    void Print() const override;

protected:
    std::string artist;
};

#endif //ALBUM_H
