#ifndef MARIO_ITEM_H
#define MARIO_ITEM_H

#include "object.h"
#include "mushroom.h"

class Item : public Object{
public:
    explicit Item(Map &map);
    void draw(sf::RenderWindow &window) override;
    void logic(float deltaTime) override;

protected:
    Mushroom *mushroom;


};


#endif //MARIO_ITEM_H
