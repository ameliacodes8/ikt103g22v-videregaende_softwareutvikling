cmake_minimum_required(VERSION 3.21)
project(17_patterns)

set(CMAKE_CXX_STANDARD 17)

add_executable(17_patterns
        controllers/author_controller.cpp controllers/author_controller.h
        main.cpp
        models/book.h
        models/library.h
        views/author_menu.cpp views/author_menu.h
        views/main_menu.cpp
        views/main_menu.h
        )

target_include_directories(17_patterns PUBLIC .)
