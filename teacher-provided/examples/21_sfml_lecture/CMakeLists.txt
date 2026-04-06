cmake_minimum_required(VERSION 3.21)
project(21_sfml_lecture)

set(CMAKE_CXX_STANDARD 14)

add_executable(21_sfml_lecture main.cpp object.h circle.h square.h)
target_link_libraries (21_sfml_lecture sfml-graphics sfml-window sfml-system)