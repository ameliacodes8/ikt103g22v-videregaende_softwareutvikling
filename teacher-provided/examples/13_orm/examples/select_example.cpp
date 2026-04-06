#include "library/author.h"
#include "util/storage.h"
#include "util/util.h"

#include <iostream>

void select_example(Storage &storage)
{
    print_header("SELECT example with get_all()");

    // Read all authors from the DB. SQLite ORM will generate a SELECT statement for us.
    auto authors = storage.get_all<Author>();

    // Loop over all returned objects
    for (auto &author: authors)
    {
        // Print each object
        std::cout << "id: " << author.id << ", family_name: " << author.family_name << ", given_name: " << author.given_name << std::endl;
    }
}
