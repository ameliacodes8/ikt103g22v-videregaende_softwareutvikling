#ifndef MARIO_MUSHROOM_H
#define MARIO_MUSHROOM_H

#include "object.h"

class Mushroom: public Object
{
    friend class Item;
public:
    explicit Mushroom(Map &map);
    void draw(sf::RenderWindow &window) override;
    void mapCollision(sf::Sprite &mapSprite);

protected:
    bool isMapCollision = false;
    bool collected = false;

};


#endif //MARIO_MUSHROOM_H
