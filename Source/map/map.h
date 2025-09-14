#ifndef MARIO_MAP_H
#define MARIO_MAP_H

#include <list>
#include <map>

#include "animation.h"
#include "../objects/object.h"
#include "../rapidjson/document.h"


struct Tileset
{
    unsigned int firstGid;
    int columns;
    int tileWidth;
    int tileHeight;
    int spacing;
    sf::Texture texture;
};

class Object;

class Map {
public:
    std::list<Object*>&GetObjects(){return objects;}
    int GetTileWidth() const{return tileWidth;}
    int GetTileHeight() const{return tileHeight;}
    bool LoadFromFile(const std::string &filename);
    void SetSpriteTextureFromGid(sf::Sprite &sprite, unsigned int gid);
    Animation *GetAnimation(unsigned int gid);
    Object *GetPlayer(){return  player;}
    void AddObject(Object* object){objects.push_back(object);}

protected:
    std::list<Object*> objects;
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    std::list<Tileset*> tilesets;
    std::map<unsigned int,Animation*> animations;
    Object *player;


    void LoadTileset(rapidjson::Value &tileset);
    void LoadTileLayer(rapidjson::Value &layer);
    void LoadObjectLayer(rapidjson::Value &layer);

    void LoadObject(Object* object, rapidjson::Value &jsonObject);
};


#endif //MARIO_MAP_H
