#ifndef SQUARE_H
#define SQUARE_H

#include "object.h"

#include <SFML/Graphics.hpp>

class Square : public Object
{
public:
    // x and y are passed on to the Object constructor
    Square(float x, float y) : Object(x, y)
    {
        shape.setSize(sf::Vector2f(20, 20));
        shape.setFillColor(sf::Color::Green);
    }

    void logic(float deltaTime) override
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            yspeed = -30;
        else
            yspeed = 30;

        // Reuse the movement logic from the Object class
        Object::logic(deltaTime);

        shape.setPosition(x, y);
    }

    void draw(sf::RenderWindow &window) override
    {
        window.draw(shape);
    }

protected:
    sf::RectangleShape shape;
};

#endif //SQUARE_H
