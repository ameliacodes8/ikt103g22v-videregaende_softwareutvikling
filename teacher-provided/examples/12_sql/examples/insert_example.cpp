#include "insert_example.h"
#include "util/util.h"

#include "sqlite3.h"
#include "SQLiteCpp/SQLiteCpp.h"

#include <iostream>

void insert_example(SQLite::Database &db)
{
    print_header("INSERT example");

    // Create the query statement. ? inserts a parameter that can be replaced
    SQLite::Statement query(db, "INSERT INTO authors (family_name, given_name) VALUES (?, ?)");

    // Bind the value of the parameters, which replaces the '?'
    query.bind(1, "Larsen");
    query.bind(2, "Lise");

    // Run the query against the database and store the number of changed rows
    int count = query.exec();

    // Print result
    std::cout << "INSERT inserted " << count << " rows." << std::endl;
}
