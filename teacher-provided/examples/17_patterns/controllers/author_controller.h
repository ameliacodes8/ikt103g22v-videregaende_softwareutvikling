#ifndef AUTHOR_CONTROLLER_H
#define AUTHOR_CONTROLLER_H

#include "models/library.h"

class AuthorController
{
public:
    explicit AuthorController(Library &library);

    void AddAuthor(std::string family_name, std::string given_name);

protected:
    Library &library;

    // AuthorController is responsible the auto increment behavior of author ids
    int nextId = 1;
};

#endif //AUTHOR_CONTROLLER_H
