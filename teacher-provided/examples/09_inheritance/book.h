#ifndef BOOK_H
#define BOOK_H

#include <string>

#include "item.h"

// This class is very similar to Album.
// See album.h for comments and explanations.
class Book : public Item
{
public:
    Book(std::string owner, std::string author);

    std::string Author() const;
    void Author(std::string author);

    void Print() const override;

protected:
    std::string author;
};

#endif //BOOK_H
