cmake_minimum_required(VERSION 3.6)
project(19_sfml_input)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

add_executable(19_sfml_input
        app.h
        config.h app.cpp
        main.cpp
        square.cpp square.h
        )

target_link_libraries(19_sfml_input sfml-graphics sfml-window sfml-system)