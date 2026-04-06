cmake_minimum_required(VERSION 3.2)
project(io)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

set(SOURCE_FILES
    main.cpp
    number.cpp
    number.h)

add_executable(io ${SOURCE_FILES})