#include "delete_example.h"
#include "util/storage.h"
#include "util/util.h"

#include <iostream>

void delete_example(Storage &storage)
{
    print_header("DELETE example");

    // Delete the row with id 6 from the database
    storage.remove<Author>(6);

    std::cout << "DELETE deleted author with id " << 6 << "." << std::endl;
}
