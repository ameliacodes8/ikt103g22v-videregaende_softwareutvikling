#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object
{
public:
    Object()
    {
        x = y = xspeed = yspeed = 0;
    }

    Object(float x, float y) : x(x), y(y), xspeed(0), yspeed(0) {}

    // Common logic for moving objects
    virtual void logic(float deltaTime)
    {
        x += xspeed * deltaTime;
        y += yspeed * deltaTime;
    }

    // draw() is pure virtual since the Object class doesn't have a visual representation
    virtual void draw(sf::RenderWindow &window) = 0;

    float x;
    float xspeed;

    float y;
    float yspeed;
};

#endif //OBJECT_H
