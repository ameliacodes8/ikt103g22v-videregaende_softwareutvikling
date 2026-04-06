#include "author_controller.h"

AuthorController::AuthorController(Library &library) : library(library)
{
    library.authors.emplace_back(Author(nextId++, "A1F", "A1G"));
    library.authors.emplace_back(Author(nextId++, "A2F", "A2G"));
    library.authors.emplace_back(Author(nextId++, "A3F", "A2G"));
}

void AuthorController::AddAuthor(std::string family_name, std::string given_name)
{
    library.authors.emplace_back(Author(nextId++, std::move(family_name), std::move(given_name)));
}
