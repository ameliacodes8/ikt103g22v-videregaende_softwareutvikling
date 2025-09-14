#include "coin.h"
#include "player.h"

void Coin::loadStatics()
{
    //Load font
    font.loadFromFile("fonts/Roboto-Regular.ttf");
    countText.setFont(font);
    countText.setFillColor(sf::Color::White);
    countText.setCharacterSize(12);

    // Load sound
    buffer.loadFromFile("sounds/coin.wav");
    sound.setBuffer(buffer);
}

void Coin::setCounterPosition(float x, float y)
{
    countText.setPosition(x,y);
}
void Coin::playSound()
{
    sound.play();
}

void Coin::draw(sf::RenderWindow &window)
{
    map.SetSpriteTextureFromGid(sprite, animation->GetFrame());
    sprite.setPosition(x, y);

    auto player = dynamic_cast<Player*>(map.GetPlayer());
    if(player->coinCollision(sprite))
    {
        if(visible)
        {
            playSound();
            count++;
        }

        visible = false;

    }

    if(visible)
        window.draw(sprite);
    window.draw(countText);
}

void Coin::logic(float deltaTime)
{
    countText.setString("Coins: "+ std::to_string(count));
}

int Coin::count = 0;
sf::Font Coin::font = sf::Font();
sf::Text Coin::countText = sf::Text();
sf::SoundBuffer Coin::buffer = sf::SoundBuffer();
sf::Sound Coin::sound = sf::Sound();