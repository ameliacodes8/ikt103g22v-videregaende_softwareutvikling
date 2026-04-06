cmake_minimum_required(VERSION 3.21)
project(13_orm)

set(CMAKE_CXX_STANDARD 17)

# SQLite library
add_library(sqlite3 sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC sqlite3)

if (UNIX)
    target_link_libraries(sqlite3 pthread dl)
endif (UNIX)

# Program executable
add_executable(13_orm main.cpp
        examples/delete_example.cpp examples/delete_example.h
        examples/insert_example.cpp examples/insert_example.h
        examples/select_example.cpp examples/select_example.h
        examples/update_example.cpp examples/insert_example.h
        library/author.h
        library/book.h
        library/user.h
        util/util.cpp util/util.h
        util/storage.h
        )

target_include_directories(13_orm PUBLIC .)
target_link_libraries(13_orm sqlite3)
