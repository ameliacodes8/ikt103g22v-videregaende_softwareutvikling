#include "pipe.h"
#include "player.h"

void Pipe::draw(sf::RenderWindow &window)
{
    map.SetSpriteTextureFromGid(sprite, animation->GetFrame());
    //sprite.setPosition(x - (float)width, y - (float)height);
    sprite.setPosition(x, y);

    if(visible)
        window.draw(sprite);
}

bool Pipe::playerCollision()
{
    auto player = dynamic_cast<Player*>(map.GetPlayer());
    return  player->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds());
}

void Pipe::logic(float deltaTime)
{
}