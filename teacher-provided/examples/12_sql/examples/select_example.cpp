#include "select_example.h"
#include "util/util.h"

#include "sqlite3.h"
#include "SQLiteCpp/SQLiteCpp.h"

#include <iostream>

void select_example(SQLite::Database &db)
{
    print_header("SELECT example");

    // Create the query statement. ? inserts a parameter that can be replaced
    SQLite::Statement query(db, "SELECT * FROM authors WHERE id = ?");

    // Bind the value of the first query parameter, which replaces the '?'
    query.bind(1, 3);

    // SELECT queries might return more than one row. Loop over all returned rows
    while (query.tryExecuteStep() == SQLITE_ROW)
    {
        // Read column values
        int id = query.getColumn("id");
        std::string family_name = query.getColumn("family_name");
        std::string given_name = query.getColumn("given_name");

        // Print each row
        std::cout << "id: " << id << ", family_name: " << family_name << ", given_name: " << given_name << std::endl;
    }
}
