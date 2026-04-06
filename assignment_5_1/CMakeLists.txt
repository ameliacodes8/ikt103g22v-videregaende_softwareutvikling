
cmake_minimum_required(VERSION 3.2)
project(assignment_5_1)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCE_FILES
        main.cpp)

add_executable(assignment_5_1 ${SOURCE_FILES})
target_link_libraries(assignment_5_1
        SQLiteCpp
        sqlite3
        pthread
        dl
        )
if (UNIX)
    target_link_libraries(sqlite3 pthread dl)
endif (UNIX)