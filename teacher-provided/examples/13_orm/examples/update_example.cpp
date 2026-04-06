#include "update_example.h"
#include "util/storage.h"
#include "util/util.h"

#include <iostream>

void update_example(Storage &storage)
{
    print_header("UPDATE example");

    // Get object representing the row with id 1
    auto author = storage.get<Author>(1);

    // Change a member variable of the object
    author.given_name = "Knut";

    // Save changes to the database
    storage.update(author);

    std::cout << "UPDATE updated author with id " << author.id << "." << std::endl;
}
