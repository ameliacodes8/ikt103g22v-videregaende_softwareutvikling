#include "layer.h"
#include "player.h"
#include "mushroom.h"
#include <iostream>

void Layer::draw(sf::RenderWindow &window)
{
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x<width; x++)
        {
            unsigned int gid = tilemap[x + y * width];

            if(gid ==0)
                continue;

            sf::Sprite sprite;

            map.SetSpriteTextureFromGid(sprite,gid);
            sprite.setPosition((float)(x*map.GetTileWidth()),(float)(y*map.GetTileHeight()));

            if(gid >0 && name == "Foreground")
            {
                auto player = dynamic_cast<Player*>(map.GetPlayer());
                player->mapCollision(sprite);
                for(auto object: map.GetObjects())
                {
                    auto *mushroom = dynamic_cast<Mushroom*>(object);
                    if(mushroom)
                        mushroom->mapCollision(sprite);
                }
            }


            if(visible)
                window.draw(sprite);
        }
    }
}