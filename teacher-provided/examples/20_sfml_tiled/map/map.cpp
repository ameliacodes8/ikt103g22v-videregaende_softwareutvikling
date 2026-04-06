#include "map.h"
#include "objects/object.h"
#include "objects/layer.h"
#include "objects/sprite.h"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include <SFML/Graphics/Sprite.hpp>

#include <memory>
#include <fstream>

// Public functions

bool Map::loadFromFile(const std::string &filename)
{
    // Clear existing data. Note that the memory used by existing data is lost since we don't delete the pointers.
    // See the "Memory Management" lecture for techniques on how to handle this.
    tilesets.clear();
    animations.clear();
    objects.clear();

    // Will contain the data we read in
    rapidjson::Document root;

    // Stream used for reading the data file. The data file has been saved as JSON in Tiled
    std::ifstream ifs(filename);

    // Convert the stream to the rapidjson stream type
    rapidjson::IStreamWrapper isw(ifs);

    // Read data from file into root object
    root.ParseStream(isw);

    // Map properties
    width = root["width"].GetInt();
    height = root["height"].GetInt();
    tileWidth = root["tilewidth"].GetInt();
    tileHeight = root["tileheight"].GetInt();

    // Load all tilesets
    for (auto &tileset: root["tilesets"].GetArray())
        loadTileset(tileset);

        // Read in each layer
    for (auto &layer: root["layers"].GetArray())
    {
        if (layer["type"].GetString() == std::string("tilelayer"))
            loadTileLayer(layer);
        else
            loadObjectLayer(layer);
    }

    return true;
}

std::vector<AnimationFrame*> *Map::getAnimation(unsigned int gid)
{
    auto animationIt = animations.find(gid);

    if (animationIt != animations.end())
        return animationIt->second;

    return nullptr;
}

void Map::setSpriteTextureFromGid(sf::Sprite &sprite, unsigned int gid, int frame)
{
    // Extract flip flags
    unsigned int flipFlags = gid >> 29;

    // Remove flip flags
    gid &= ~(0b111 << 29);

    // Look for an animation for this gid
    auto animationIt = animations.find(gid);

    if (animationIt != animations.end())
    {
        auto animation = *animationIt->second;

        if (frame >= 0 && frame < (int)animation.size())
            gid = animation[frame]->gid;
    }

    // Find the correct tileset for this gid
    auto tileset = *std::find_if(tilesets.rbegin(), tilesets.rend(), [gid](auto ts) { return gid >= ts->firstGid; } );

    // Calculate x and y positions in the tileset
    int tileid = gid - tileset->firstGid;
    int x = (tileid % tileset->columns) * (tileset->tileWidth + tileset->spacing);
    int y = (tileid / tileset->columns) * (tileset->tileWidth + tileset->spacing);

    int textureRectWidth = tileset->tileWidth;
    int textureRectHeight = tileset->tileHeight;

    // Vertical flip
    if (flipFlags & 2)
    {
        textureRectHeight *= -1;
        y += tileset->tileHeight;
    }

    // Horizontal flip
    if (flipFlags & 4)
    {
        textureRectWidth *= -1;
        x += tileset->tileWidth;
    }

    // Set the texture and texture source rectangle
    sprite.setTexture(tileset->texture);
    sprite.setTextureRect(sf::IntRect(x, y, textureRectWidth, textureRectHeight));
}

// Protected functions

void Map::loadTileset(rapidjson::Value &tileset)
{
    auto ts = new Tileset();

    ts->firstGid  = tileset["firstgid"].GetUint();
    ts->columns  = tileset["columns"].GetInt();
    ts->tileWidth  = tileset["tilewidth"].GetInt();
    ts->tileHeight  = tileset["tileheight"].GetInt();
    ts->spacing  = tileset["spacing"].GetInt();

    ts->texture.loadFromFile(std::string("data/") + tileset["image"].GetString());

    tilesets.push_back(ts);

    // Load all animations
    for (rapidjson::Value &tile: tileset["tiles"].GetArray())
    {
        unsigned int animationId = ts->firstGid + tile["id"].GetInt();

        for (rapidjson::Value &animation: tile["animation"].GetArray())
        {
            unsigned int gid = ts->firstGid + animation["tileid"].GetUint();
            int duration = animation["duration"].GetInt();

            if (animations.find(animationId) == animations.end())
                animations[animationId] = new std::vector<AnimationFrame*>();

            animations[animationId]->push_back(new AnimationFrame(gid, duration));
        }
    }
}

void Map::loadTileLayer(rapidjson::Value &layer)
{
    auto tmp = new Layer(*this);

    // Store info on layer
    tmp->id = layer["id"].GetInt();
    tmp->name = layer["name"].GetString();
    tmp->visible = layer["visible"].GetBool();
    tmp->width = layer["width"].GetInt();
    tmp->height = layer["height"].GetInt();
    tmp->tilemap = new unsigned int[tmp->width * tmp->height];

    // Read in tilemap
    const auto &tilemap = layer["data"].GetArray();

    for (size_t i = 0; i < tilemap.Size(); i++)
        tmp->tilemap[i] = tilemap[(int) i].GetUint();

    objects.push_back(tmp);
}

void Map::loadObjectLayer(rapidjson::Value &layer)
{
    // Get all objects from layer
    for (rapidjson::Value &object: layer["objects"].GetArray())
    {
        auto sprite = new Sprite(*this);

        // Load basic object info
        sprite->id = object["id"].GetInt();
        sprite->gid = object["gid"].GetUint();
        sprite->x = object["x"].GetInt();
        sprite->y = object["y"].GetInt();
        sprite->width = object["width"].GetInt();
        sprite->height = object["height"].GetInt();
        sprite->y -= sprite->height; // Not sure why Tiled anchor in the bottom left...

        objects.push_back(sprite);
    }
}
