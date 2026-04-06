/*
 * This example shows how to parse the map and object data in JSON exported from the Tiled editor.

* Note: Here the objects know how to draw themselves, thus all classes depend on SFML.
*       As an alternative a separate View could be implemented so that the SFML dependency
*       only exists there.
*/

#include "game.h"

#include <iostream>

int main()
{
    Game game;

    if (!game.init())
    {
        std::cout << "Failed to initialize the game. Quitting." << std::endl;
        return -1;
    }

    game.run();

    return 0;
}
