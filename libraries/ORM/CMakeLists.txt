cmake_minimum_required(VERSION 3.21)
project(orm)

# <filesystem> requires C++17
set(CMAKE_CXX_STANDARD 17)

# SQLite library
add_library(sqlite3 sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC sqlite3)

# Program executable
add_executable(
        orm
        main.cpp
        sqlite_orm/sqlite_orm.h
        library/author.h)

target_include_directories(orm PUBLIC .)
target_link_libraries(orm sqlite3)