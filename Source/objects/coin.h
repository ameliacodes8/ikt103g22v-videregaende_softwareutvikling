#ifndef MARIO_COIN_H
#define MARIO_COIN_H

#include "object.h"
#include <SFML/Audio.hpp>

class Coin : public Object
{
    friend class Map;
public:
    explicit Coin(Map &map): Object(map){}
    void draw(sf::RenderWindow &window) override;
    void logic(float deltaTime) override;
    //~Coin() override;
    static void loadStatics();
    static void setCounterPosition(float x, float y);
    static int getCount(){return count;}
protected:
    static int count;
    static sf::Text countText;
    static sf::Font font;
    static sf::SoundBuffer buffer;
    static sf::Sound sound;
    static void playSound();

};


#endif //MARIO_COIN_H
