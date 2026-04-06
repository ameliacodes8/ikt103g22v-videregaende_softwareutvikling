#ifndef MAP_H
#define MAP_H

#include "rapidjson/document.h"

#include <SFML/Graphics/Texture.hpp>

#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace sf
{
    class Sprite;
}

namespace Json
{
    class Value;
}

class Object;
class Layer;

// Helper struct describing a tileset
struct Tileset
{
    unsigned int firstGid;
    int columns;
    int tileWidth;
    int tileHeight;
    int spacing;

    sf::Texture texture;
};

// Helper struct describing a frame of animation
struct AnimationFrame
{
    AnimationFrame(unsigned int gid, int duration) : gid(gid), duration(duration) {}

    unsigned int gid;
    int duration;
};

// Class containing the information in a Tiled map
class Map
{
public:
    // Load map from Tiled JSON file
    bool loadFromFile(const std::string &filename);

    int getTileWidth() const { return tileWidth; }
    int getTileHeight() const { return tileHeight; }

    // Gets animation for a specific global tile id
    std::vector<AnimationFrame*> *getAnimation(unsigned int gid);

    // Sets sprite texture and texture coordinates based on global tile id
    void setSpriteTextureFromGid(sf::Sprite &sprite, unsigned int gid, int frame = 0);

    std::list<Object*> &GetObjects() { return objects; }

protected:
    // Used in loadFromFile to load information from JSON
    void loadTileset(rapidjson::Value &tileset);
    void loadTileLayer(rapidjson::Value &layer);
    void loadObjectLayer(rapidjson::Value &layer);

    int width;
    int height;
    int tileWidth;
    int tileHeight;

    // Map information
    std::list<Tileset*> tilesets;
    std::map<unsigned int, std::vector<AnimationFrame*>*> animations;

    // Map content (layers + objects)
    std::list<Object*> objects;
};

#endif
