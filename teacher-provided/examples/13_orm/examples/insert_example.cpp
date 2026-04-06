#include "library/author.h"
#include "util/storage.h"
#include "util/util.h"

#include <iostream>

void insert_example(Storage &storage)
{
    print_header("INSERT example with insert()");

    // Create the object we want to insert
    Author author { -1, "A6F", "A6G" };

    // Insert using the db object. Insert returns the id of the newly inserted row.
    author.id = storage.insert(author);

    // Print result
    std::cout << "Inserted author with id " << author.id << "." << std::endl;
}
