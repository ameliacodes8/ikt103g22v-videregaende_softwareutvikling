cmake_minimum_required(VERSION 3.21)
project(Mario)

set(CMAKE_CXX_STANDARD 14)

add_executable(Mario
        main.cpp
        game.cpp game.h
        objects/object.cpp objects/object.h
        map/map.cpp map/map.h objects/layer.cpp objects/layer.h objects/coin.cpp objects/coin.h objects/block.cpp objects/block.h map/animation.cpp map/animation.h objects/player.cpp objects/player.h objects/item.cpp objects/item.h objects/mushroom.cpp objects/mushroom.h objects/pipe.cpp objects/pipe.h)
target_link_libraries (Mario sfml-graphics sfml-window sfml-audio sfml-system)