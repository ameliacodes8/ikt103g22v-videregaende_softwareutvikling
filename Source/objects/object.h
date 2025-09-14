#ifndef MARIO_OBJECT_H
#define MARIO_OBJECT_H


#include <SFML/Graphics.hpp>
#include "../map/map.h"
#include "../map/animation.h"

class Map;

class Object {
    friend class Map;
public:
    Object(Map &map): map(map){}
    virtual ~Object() = default;
    virtual void logic(float deltaTime){};
    virtual void draw(sf::RenderWindow &window){};
protected:
    Map &map;
    Animation *animation = nullptr;
    unsigned int gid = 0;
    sf::Sprite sprite;
    bool visible = false;
    int height = 0;
    int width = 0;
    float x = 0;
    float y = 0;
    float xSpeed = 0;
    float ySpeed = 0;
};


#endif //MARIO_OBJECT_H
