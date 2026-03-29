#include <list>
#include "../objects/block.h"
#include "../objects/coin.h"
#include "../objects/object.h"
#include "../objects/item.h"
#include "../objects/mushroom.h"
#include "../objects/layer.h"
#include "../objects/player.h"
#include "../objects/pipe.h"
#include "../rapidjson/document.h"
#include "../rapidjson/istreamwrapper.h"
#include <fstream>
#include "map.h"

bool Map::LoadFromFile(const std::string &filename)
{
    Coin::loadStatics();
    Block::loadStatics();
    // Parse JSON
    rapidjson::Document root;
    std::ifstream ifs(filename);
    rapidjson::IStreamWrapper iws(ifs);
    root.ParseStream(iws);

    //Get tilesize
    width = root["width"].GetInt();
    height = root["height"].GetInt();
    tileWidth = root["tilewidth"].GetInt();
    tileHeight = root["tileheight"].GetInt();

    for(auto &tileset: root["tilesets"].GetArray())
        LoadTileset(tileset);

    for(auto &layer: root["layers"].GetArray())
    {
        if (layer["type"].GetString() == std::string("tilelayer"))
            LoadTileLayer(layer);
        else
            LoadObjectLayer(layer);
    }
    return true;
}


void Map::SetSpriteTextureFromGid(sf::Sprite &sprite, unsigned int gid)
{
    auto tileset = *std::find_if(tilesets.rbegin(), tilesets.rend(), [gid](auto ts) { return gid >= ts->firstGid; } );

    int tileid = gid - tileset->firstGid;
    int x = (tileid % tileset->columns) * (tileset->tileWidth + tileset->spacing);
    int y = (tileid / tileset->columns) * (tileset->tileWidth + tileset->spacing);

    int textureRectWidth = tileset->tileWidth;
    int textureRectHeight = tileset->tileHeight;
    sprite.setTexture(tileset->texture);
    sprite.setTextureRect(sf::IntRect(x, y, textureRectWidth, textureRectHeight));
}

void Map::LoadTileset(rapidjson::Value &tileset)
{
    auto ts = new Tileset();
    ts->firstGid  = tileset["firstgid"].GetUint();
    ts->columns  = tileset["columns"].GetInt();
    ts->tileWidth  = tileset["tilewidth"].GetInt();
    ts->tileHeight  = tileset["tileheight"].GetInt();
    ts->spacing  = tileset["spacing"].GetInt();

    ts->texture.loadFromFile(std::string("data/") + tileset["image"].GetString());

    tilesets.push_back(ts);

    for(auto &tile : tileset["tiles"].GetArray())
    {
        unsigned int id = tile["id"].GetUint()+ts->firstGid;
        auto animation = new Animation();

        for(auto &frame : tile["animation"].GetArray())
        {
            auto *animationFrame = new AnimationFrame();
            animationFrame->tileId = frame["tileid"].GetUint()+ts->firstGid;
            animationFrame->duration = frame["duration"].GetInt();

            animation->AddFrame(animationFrame);

        }
        animations[id] = animation;
    }
}

void Map::LoadTileLayer(rapidjson::Value &layer)
{
    auto _layer = new Layer(*this);
    _layer->id = layer["id"].GetInt();
    _layer->name = layer["name"].GetString();
    _layer->visible = layer["visible"].GetBool();
    _layer->width = layer["width"].GetInt();
    _layer->height = layer["height"].GetInt();
    _layer->tilemap = new unsigned int[_layer->width * _layer->height];

    const auto &tilemap = layer["data"].GetArray();
    for (size_t i = 0; i < tilemap.Size(); i++)
        _layer->tilemap[i] = tilemap[(int) i].GetUint();

    objects.push_back(_layer);
}

Animation *Map::GetAnimation(unsigned int gid)
{
    for(const auto &animation : animations)
    {
        if(animation.first == gid)
            return animation.second;


    }
    return new Animation(gid);
}

void Map::LoadObjectLayer(rapidjson::Value &layer)
{
    for(auto &object : layer["objects"].GetArray())
    {
        if(object["type"].GetString() == std::string("coin"))
        {
            auto coin = new Coin(*this);
            LoadObject(coin,object);
        }
        if(object["type"].GetString() == std::string("block"))
        {
            auto block = new Block(*this);
            LoadObject(block,object);
        }
        if(object["type"].GetString() == std::string("item"))
        {
            auto item = new Item(*this);
            LoadObject(item,object);
        }
        if(object["type"].GetString() == std::string("pipe"))
        {
            auto pipe = new Pipe(*this);
            LoadObject(pipe,object);
        }
        if(object["type"].GetString() == std::string("player"))
        {
            auto player = new Player(*this);
            LoadObject(player,object);
            player->SetPosition(player->x, player->y);
            this->player = player;
        }
    }

}

void Map::LoadObject(Object *object, rapidjson::Value &jsonObject)
{
    object->gid = jsonObject["gid"].GetUint();
    object->visible = jsonObject["visible"].GetBool();
    object->height = jsonObject["height"].GetInt();
    object->width = jsonObject["width"].GetInt();
    object->x = jsonObject["x"].GetFloat();
    object->y = jsonObject["y"].GetFloat()-(float)object->height;
    object->animation = GetAnimation(object->gid);
    objects.push_back(object);
}



