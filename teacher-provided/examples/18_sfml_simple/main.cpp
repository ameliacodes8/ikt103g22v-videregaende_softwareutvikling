// Simple example showing how the game loop works
#include <SFML/Graphics.hpp>

int main()
{
    // Create an instance of the RenderWindow class.
    // This object is the graphical window of our program.
    sf::RenderWindow window(sf::VideoMode(300, 300), "Circle of doom!");

    // Enable vertical sync. Locks framerate to the display and prevents tearing.
    window.setVerticalSyncEnabled(true);

    // Create an instance of the CircleShape class.
    // The object exists from this line, but isn't drawn until we manually do so later in the program.
    sf::CircleShape shape(150.f);

    // Set the internal color of the circle
    shape.setFillColor(sf::Color::Red);

    // Run the game loop as long as the window is open
    while (window.isOpen())
    {
        // Use {} to default initialize the struct. Prevents a warning.
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

        // Draw our circle
        window.draw(shape);

        // Flip the back buffer and front buffer, showing what was drawn.
        // This is a technique called double buffering, where we draw on a non-visible screen then flip them.
        window.display();
    }

    return 0;
}
