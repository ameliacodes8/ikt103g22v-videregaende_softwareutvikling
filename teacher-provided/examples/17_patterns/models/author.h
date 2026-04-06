#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

class Author
{
public:
    Author(int id, std::string family_name, std::string given_name)
            : id(id), family_name(std::move(family_name)), given_name(std::move(given_name)) {}

    const int id;
    std::string family_name;
    std::string given_name;
};

#endif //AUTHOR_H
