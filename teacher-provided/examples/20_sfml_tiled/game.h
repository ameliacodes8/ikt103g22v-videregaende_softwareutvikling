#ifndef GAME_H
#define GAME_H

#include "map/map.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <list>

class Object;

class Game
{
public:
    bool init();
    void run();

protected:
    bool gameTick(float deltaTime);

    sf::Clock clock;

    sf::RenderWindow window;

    Map map;
};

#endif
