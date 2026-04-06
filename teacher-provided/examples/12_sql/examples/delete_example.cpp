#include "delete_example.h"
#include "util/util.h"

#include "sqlite3.h"
#include "SQLiteCpp/SQLiteCpp.h"

#include <iostream>

void delete_example(SQLite::Database &db)
{
    print_header("DELETE example");

    // Create the query statement. ? inserts a parameter that can be replaced
    SQLite::Statement query(db, "DELETE FROM authors WHERE id=?");

    // Bind the value of the parameters, which replaces the '?'
    query.bind(1, 1);

    // Run the query against the database and store the number of changed rows
    int count = query.exec();

    // Print result
    std::cout << "DELETE deleted " << count << " rows." << std::endl;
}
