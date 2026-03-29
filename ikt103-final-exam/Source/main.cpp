#include <iostream>
#include "game.h"
#include <SFML/Audio.hpp>

int main() {

    /*
     * Please note that most of the game loop and map loading
     * logic is based off the "tiled SFML" example from BitBucket
     * and is therefore fairly similar to this code.
     * */


    Game game;
    if(game.init())
        game.run();
    return 0;
}
