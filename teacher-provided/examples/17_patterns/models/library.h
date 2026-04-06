#ifndef LIBRARY_H
#define LIBRARY_H

#include "author.h"
#include "book.h"
#include "user.h"

#include <list>

class Library
{
public:
    std::list<Author> authors;
    std::list<Book> books;
    std::list<User> users;
};

#endif //LIBRARY_H
