cmake_minimum_required(VERSION 3.21)
project(12_sql)

set(CMAKE_CXX_STANDARD 17)

# SQLite library
add_library(sqlite3 sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC sqlite3)

if (UNIX)
    target_link_libraries(sqlite3 pthread dl)
endif (UNIX)

# SQLiteCpp library
add_library(sqlitecpp
        sqlitecpp/src/Backup.cpp
        sqlitecpp/src/Column.cpp
        sqlitecpp/src/Database.cpp
        sqlitecpp/src/Exception.cpp
        sqlitecpp/src/Statement.cpp
        sqlitecpp/src/Transaction.cpp
        )

target_include_directories(sqlitecpp PUBLIC sqlitecpp/include)
target_link_libraries(sqlitecpp sqlite3)

# Program executable
add_executable(12_sql main.cpp
        examples/delete_example.cpp examples/delete_example.h
        examples/insert_example.cpp examples/insert_example.h
        examples/select_example.cpp examples/select_example.h
        examples/update_example.cpp examples/insert_example.h
        util/util.cpp util/util.h
        )

target_include_directories(12_sql PUBLIC .)
target_link_libraries(12_sql sqlite3 sqlitecpp)
