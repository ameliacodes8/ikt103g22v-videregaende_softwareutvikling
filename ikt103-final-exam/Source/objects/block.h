#ifndef MARIO_BLOCK_H
#define MARIO_BLOCK_H

#include "object.h"
#include <SFML/Audio.hpp>


class Block : public Object
{

        friend class Map;
public:
    explicit Block(Map &map) : Object(map){}
    void draw(sf::RenderWindow &window) override;
    static void loadStatics();

protected:
    static sf::SoundBuffer buffer;
    static sf::Sound sound;

};


#endif //MARIO_BLOCK_H
