#include <iostream>
#include <string>

#include "item.h"

// Constructor
Item::Item(std::string owner)
{
    // Use the static class member variable to set the id.
    // Remember: This value is shared between all objects of the class.
    id = next_id++;

    this->owner = std::move(owner);
}

// Destructor
Item::~Item() = default;

int Item::Id() const
{
    return id;
}

std::string Item::Owner() const
{
    return owner;
}

void Item::Owner(std::string owner)
{
    this->owner = std::move(owner);
}

void Item::Print() const
{
    std::cout << "id: " << id << ", owner: " << owner;
}

// Allocate and initialize memory for the static class member variable
int Item::next_id = 1;
