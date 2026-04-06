#include "update_example.h"
#include "util/util.h"

#include "sqlite3.h"
#include "SQLiteCpp/SQLiteCpp.h"

#include <iostream>

void update_example(SQLite::Database &db)
{
    print_header("UPDATE example");

    // Create the query statement. ? inserts a parameter that can be replaced
    SQLite::Statement query(db, "UPDATE authors SET family_name=?, given_name=? WHERE id=?");

    // Bind the value of the parameters, which replaces the '?'s
    query.bind(1, "Larsen");
    query.bind(2, "Lise");
    query.bind(3, 1);

    // Run the query against the database and store the number of changed rows
    int count = query.exec();

    // Print result
    std::cout << "UPDATE updated " << count << " rows." << std::endl;
}
