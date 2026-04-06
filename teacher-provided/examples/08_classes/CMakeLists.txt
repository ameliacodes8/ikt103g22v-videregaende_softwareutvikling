cmake_minimum_required(VERSION 3.2)
project(classes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

set(SOURCE_FILES
        string_value.cpp
        string_value.h
    main.cpp)

add_executable(class ${SOURCE_FILES})