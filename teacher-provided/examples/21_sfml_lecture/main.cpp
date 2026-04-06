#include "circle.h"
#include "square.h"
#include "object.h"

#include <SFML/Graphics.hpp>

#include <list>

int main()
{
    // List can contain any object of a class that inherits from Object
    std::list<Object*> objects;

    // Add 5 circles
    for (int i = 0; i < 5; i++)
        objects.push_back(new Circle(float(20 + i * 50), float(i * 75)));

    // Add 5 squares
    for (int i = 0; i < 5; i++)
        objects.push_back(new Square(float(20 + i * 75), 30));

    // Create an instance of the RenderWindow class.
    // This object is the graphical window of our program.
    sf::RenderWindow window(sf::VideoMode(640, 480), "Shapes?");

    // Enable vertical sync. Locks framerate to the display and prevents tearing.
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;

    // Run the game loop as long as the window is open
    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event{};

        // Read all events from the window, one at a time
        while (window.pollEvent(event))
        {
            // Quit when the user presses 'x', ignore all other events
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window to black
        window.clear();

        // Run logic and draw each object
        for (auto object: objects)
        {
            object->logic(deltaTime);
            object->draw(window);
        }

        // Flip the back buffer and front buffer, showing what was drawn
        window.display();
    }
}
