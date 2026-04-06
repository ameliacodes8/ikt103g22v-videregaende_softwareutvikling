cmake_minimum_required(VERSION 3.3)
project(20_sfml_tiled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

add_executable(20_sfml_tiled
        game.cpp game.h
        main.cpp
        map/map.cpp map/map.h
        objects/layer.cpp objects/layer.h
        objects/object.h
        objects/sprite.cpp objects/sprite.h
        )

# Link with SFML dependencies
target_link_libraries(20_sfml_tiled sfml-graphics sfml-window sfml-system)
target_include_directories(20_sfml_tiled PUBLIC . libs/jsoncpp/include)