#ifndef STORAGE_H
#define STORAGE_H

#include "library/author.h"
#include "library/book.h"
#include "library/user.h"

#include <sqlite_orm/sqlite_orm.h>

// Function that initializes SQLite ORM with table descriptions.
// The return type is auto so we don't need to specify a very complex type.
// The implementation of the function must be in a header file due to the use of auto.
inline auto init_storage(const std::string &filename)
{
    // Removes the need for specifying a namespace in this function only
    using namespace sqlite_orm;

    // Initialize SQLite ORM with table descriptions
    auto storage = make_storage(filename,
                           make_table("authors",
                                           make_column("id", &Author::id, autoincrement(), primary_key()),
                                           make_column("family_name", &Author::family_name),
                                           make_column("given_name", &Author::given_name)
                           ),
                           make_table("books",
                                           make_column("id", &Book::id, autoincrement(), primary_key()),
                                           make_column("user_id", &Book::user_id),
                                           make_column("title", &Book::title),
                                           make_column("summary", &Book::summary),
                                           foreign_key(&Book::user_id).references(&User::id)
                           ),
                           make_table("users",
                                           make_column("id", &User::id, autoincrement(), primary_key()),
                                           make_column("family_name", &User::family_name),
                                           make_column("given_name", &User::given_name),
                                           make_column("email", &User::email)
                           )
    );

    return storage;
}

// Creates a type alias we can use elsewhere in the application.
// We don't actually know the C++ type of our storage object, so we do it automatically like this.
using Storage = decltype(init_storage(""));

#endif //STORAGE_H
