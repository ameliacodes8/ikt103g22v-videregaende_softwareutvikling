#include <filesystem>
#include <sqlite_orm/sqlite_orm.h>
#include <library/author.h>
#include <iostream>

namespace fs = std::filesystem; //vi slipper å skrive hele navnet

using namespace sqlite_orm;

int main()
{
    fs::remove("library.sqlite");
    fs::copy_file("library.sqlite.bak", "library.sqlite");

    auto storage = make_storage("Library.sqlite",

                                            make_table("authors",
                                                   make_column("id", &Author::id, autoincrement(), primary_key()),
                                                   make_column("family_name", &Author::family_name),
                                                   make_column("given_name", &Author::given_name)
                                                  )
                                           );
    auto author1 = storage.get<Author>(1); //Same as: SELECT * FROM authors WHERE id = 1

    std::cout << ".get() fetched author: " << author1.family_name << " , " << author1.given_name << std::endl;


    return 0;
}
