#ifndef MARIO_LAYER_H
#define MARIO_LAYER_H

#include "object.h"

class Layer : public Object
{
    friend class Map;
public:
    explicit Layer(Map &map) : Object(map){animation = nullptr;}
    ~Layer() override { delete[] tilemap;}

    void draw(sf::RenderWindow &window) override;

protected:
    int id = 0;
    std::string name;
    unsigned int *tilemap = nullptr;
};


#endif //MARIO_LAYER_H
