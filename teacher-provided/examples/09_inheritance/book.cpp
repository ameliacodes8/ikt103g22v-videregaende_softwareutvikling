#include <iostream>
#include <string>

#include "book.h"

// This file is very similar to album.cpp.
// See album.cpp for comments and explanations.

Book::Book(std::string owner, std::string author) : Item(std::move(owner))
{
    this->author = std::move(author);
}

std::string Book::Author() const
{
    return author;
}

void Book::Author(std::string author)
{
    this->author = std::move(author);
}

void Book::Print() const
{
    Item::Print();
    std::cout << ", author: " << author;
}
