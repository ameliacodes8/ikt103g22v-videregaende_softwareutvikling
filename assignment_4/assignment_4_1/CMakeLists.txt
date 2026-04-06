
cmake_minimum_required(VERSION 3.2)
project(assignment_4_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCE_FILES
        main.cpp)

add_executable(assignment_4_1 ${SOURCE_FILES})