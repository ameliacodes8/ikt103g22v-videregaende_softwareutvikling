cmake_minimum_required(VERSION 3.21)
project(18_sfml_simple)

set(CMAKE_CXX_STANDARD 14)

add_executable(18_sfml_simple main.cpp)
target_link_libraries (18_sfml_simple sfml-graphics sfml-window sfml-system)