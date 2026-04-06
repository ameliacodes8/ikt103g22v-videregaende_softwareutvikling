cmake_minimum_required(VERSION 3.21)
project(SMFL_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(SMFL_test main.cpp)
target_link_libraries (SMFL_test sfml-graphics sfml-window sfml-system)
