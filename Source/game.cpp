#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "objects/player.h"
#include "objects/pipe.h"
#include "objects/coin.h"

bool Game::init()
{
    if (!map.LoadFromFile("data/map.json"))
    {
        std::cout << "Failed to load map data." << std::endl;
        return false;
    }
    window.create(sf::VideoMode(680,340),
                  "Mario",
                  sf::Style::Titlebar | sf::Style::Close
                  );
    window.setFramerateLimit(60);

    font.loadFromFile("fonts/Roboto-Regular.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);

    //Load music
    musicBuffer.loadFromFile("sounds/music.wav");
    music.setBuffer(musicBuffer);


    return true;
}

void Game::run()
{
    float deltaTime = 0;
    frameClock.restart();
    gameClock.restart();
    auto player = dynamic_cast<Player*>(map.GetPlayer());
    sf::View view = window.getDefaultView();
    view.setSize(view.getSize().x / 2, view.getSize().y / 2);
    view.setCenter(view.getCenter().x / 2, view.getCenter().y / 2);
    window.setView(view);
    int score;

    //Play music
    music.play();

    while (window.isOpen())
    {
        //Handle events
        sf::Event event;
        while(window.pollEvent(event))
        {
            eventHandler(event);
        }

        //if(player->GetSprite()->getPosition().x > view.getCenter().x)
        //{
        view.setCenter(player->GetSprite()->getPosition().x,view.getCenter().y);
        //}
        window.setView(view);

        // Make coin counter follow player
        Coin::setCounterPosition(player->GetSprite()->getPosition().x+100,3);

        for(auto object : map.GetObjects()){
            auto pipe = dynamic_cast<Pipe*>(object);
            if(pipe)
                if(pipe->playerCollision())
                {
                    running = false;
                }

        }

        // Set Score
        if(running)
            score = (1000*Coin::getCount())/gameClock.getElapsedTime().asSeconds();

        //Clear window
        window.clear(sf::Color::Black);

        if(running)
        {
            //Draw 1 game frame
            for(auto object: map.GetObjects()){
                object->logic(deltaTime);
                object->draw(window);
            }
        }
        else
        {
            text.setString("Level complete!\nScore: " +std::to_string(score) );
            text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height/2);
            text.setPosition(view.getCenter());
            window.draw(text);
        }

        //Display frame
        window.display();


        deltaTime = frameClock.getElapsedTime().asSeconds();
        frameClock.restart();


    }


}

void Game::eventHandler(sf::Event event)
{
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::LostFocus:
            //TODO: pause game
            break;
        case sf::Event::GainedFocus:
            //TODO: resume game
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Space:
                {
                    auto player = dynamic_cast<Player*>(map.GetPlayer());
                    if(player->reJump)
                        player->jumpSound.play();
                    break;
                }
                default:
                    break;

            }
        case sf::Event::KeyReleased:
            switch (event.key.code) {
                case sf::Keyboard::Space:
                {
                    auto player = dynamic_cast<Player*>(map.GetPlayer());
                    player->reJump = true;
                    break;
                }

                case sf::Keyboard::Escape:
                {
                    window.close();
                    break;
                }
                default:
                    break;
            }
        case sf::Event::JoystickButtonReleased:
            switch (event.joystickButton.button) {
                case 0:
                {
                    auto player = dynamic_cast<Player*>(map.GetPlayer());
                    player->reJump = true;
                    break;
                }
            }

            break;
        case sf::Event::JoystickButtonPressed:
            switch(event.joystickButton.button){
                case 0:
                {
                    auto player = dynamic_cast<Player*>(map.GetPlayer());
                    if(player->reJump)
                        player->jumpSound.play();
                }
            }

        default:
            break;
    }
}