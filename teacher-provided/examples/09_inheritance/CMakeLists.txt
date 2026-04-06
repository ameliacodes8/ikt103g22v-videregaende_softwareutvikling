cmake_minimum_required(VERSION 3.21)
project(inheritance)

set(CMAKE_CXX_STANDARD 14)

add_executable(slide_notes main.cpp Album.cpp Album.h Item.cpp Item.h Book.cpp Book.h)
