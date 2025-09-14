#ifndef MARIO_GAME_H
#define MARIO_GAME_H

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "map/map.h"

class Game {
public:
    bool init();
    void run();
protected:
    sf::RenderWindow window;
    Map map;
    sf::Clock frameClock;
    sf::Clock gameClock;
    void eventHandler(sf::Event event);
    bool running = true;
    sf::Font font;
    sf::Text text;
    sf::SoundBuffer musicBuffer;
    sf::Sound music;

};


#endif //MARIO_GAME_H
