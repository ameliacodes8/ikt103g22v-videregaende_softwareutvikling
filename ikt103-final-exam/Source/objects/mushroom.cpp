#include "mushroom.h"
#include "player.h"

Mushroom::Mushroom(Map &map): Object(map)
{
    visible = false;
    height = 16;
    width = 16;
}

void Mushroom::draw(sf::RenderWindow &window)
{
    map.SetSpriteTextureFromGid(sprite,284);

    auto player = dynamic_cast<Player*>(map.GetPlayer());
    if(player->mushroomCollision(sprite, isMapCollision) && isMapCollision)
    {
        visible = false;
        collected = true;
    }


    if(visible)
        window.draw(sprite);
}

void Mushroom::mapCollision(sf::Sprite &mapSprite)
{
    if (visible && mapSprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
    {
        float mLeft = sprite.getPosition().x;
        float tileLeft = mapSprite.getPosition().x;
        float tileRight = mapSprite.getPosition().x + (float) map.GetTileWidth();
        float mCenter = mLeft+(float)width/2;
        float mBottom = sprite.getPosition().y + (float)height;
        float tileTop = mapSprite.getPosition().y;

        //Check vertical collision
        if (tileTop < mBottom && mCenter < tileRight && mCenter > tileLeft)
        {
            isMapCollision = true;
        }


    }
}