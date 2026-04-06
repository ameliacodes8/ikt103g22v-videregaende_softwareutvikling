#ifndef CIRCLE_H
#define CIRCLE_H

#include "object.h"

#include <SFML/Graphics.hpp>

class Circle : public Object
{
public:
    // x and y are passed on to the Object constructor
    Circle(float x, float y) : Object(x, y)
    {
        xspeed = 80;

        shape.setRadius(50.f);
        shape.setFillColor(sf::Color::Red);
    }

    void logic(float deltaTime) override
    {
        if (x <= 0)
            xspeed = -xspeed;

        if (x >= 640 - 100)
            xspeed = -xspeed;

        // Reuse the movement logic from the Object class
        Object::logic(deltaTime);

        shape.setPosition(x, y);
    }

    void draw(sf::RenderWindow &window) override
    {
        window.draw(shape);
    }

protected:
    sf::CircleShape shape;
};

#endif //CIRCLE_H
