#include "item.h"
#include "player.h"

Item::Item(Map &map) : Object(map)
{
    mushroom = new Mushroom(map);
    map.AddObject(mushroom);


}

void::Item::draw(sf::RenderWindow &window)
{
    map.SetSpriteTextureFromGid(sprite, animation->GetFrame());
    sprite.setPosition(x - (float)width, y - (float)height);

    auto player = dynamic_cast<Player*>(map.GetPlayer());
    if(player->blockCollision(sprite, !visible) && !mushroom->collected)
    {
        mushroom->visible = true;
    }

    //mushroom->draw(window);
    if(visible)
        window.draw(sprite);


}

void Item::logic(float deltaTime)
{
    if(!mushroom->collected)
    {
        bool intersect = sprite.getGlobalBounds().intersects(mushroom->sprite.getGlobalBounds());
        if(mushroom->visible)
        {
            if(intersect)
                mushroom->sprite.move(0,-20*deltaTime);
            else if(mushroom->sprite.getPosition().x < sprite.getPosition().x+(float )width)
                mushroom->sprite.move(30*deltaTime,0);
            else if(!mushroom->isMapCollision)
                mushroom->sprite.move(10*deltaTime,50*deltaTime);



        }
        else
        {
            mushroom->sprite.setPosition(sprite.getPosition());
        }
    }

}