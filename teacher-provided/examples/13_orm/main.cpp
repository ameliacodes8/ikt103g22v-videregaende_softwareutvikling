/*
 * This example requires a C++ Standard Library with filesystem support
 *
 * On Windows you will need to change the compiler:
 ** 1. File -> Settings -> Build, Execution and Deployment -> Toolchains
 ** 2. Click + and choose "Bundled MinGW" if it's not already selected
 ** 3. Select the new toolchain and move it up with the up arrow to make it default
 */

#include "util/storage.h"

#include "examples/delete_example.h"
#include "examples/insert_example.h"
#include "examples/select_example.h"
#include "examples/update_example.h"

 #include <filesystem>

// Create a namespace alias
namespace fs = std::filesystem;

int main()
{
    // Restore the database from the backup on startup.
    // This ensures a known state of the database.
    fs::remove("library.sqlite");
    fs::copy_file("library.sqlite.bak", "library.sqlite");

    // Open the database using our function from util/util.cpp
    auto storage = init_storage("library.sqlite");

    // Run all the examples included above. Pass the database as a reference (dependency injection)
    select_example(storage);
    insert_example(storage);
    update_example(storage);
    delete_example(storage);
}
