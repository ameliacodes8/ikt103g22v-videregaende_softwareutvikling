#include "block.h"
#include "player.h"

void Block::draw(sf::RenderWindow &window)
{
    map.SetSpriteTextureFromGid(sprite, animation->GetFrame());
    //sprite.setPosition(x - (float)width, y - (float)height);
    sprite.setPosition(x, y);

    auto player = dynamic_cast<Player*>(map.GetPlayer());
    if(player->blockCollision(sprite, !visible))
    {
        if(visible)
            sound.play();
        visible = false;
    }

    if(visible)
        window.draw(sprite);

}

void Block::loadStatics()
{
    buffer.loadFromFile("sounds/block.wav");
    sound.setBuffer(buffer);
}


sf::SoundBuffer Block::buffer = sf::SoundBuffer();
sf::Sound Block::sound = sf::Sound();