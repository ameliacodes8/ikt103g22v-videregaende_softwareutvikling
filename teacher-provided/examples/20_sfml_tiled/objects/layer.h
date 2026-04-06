#ifndef LAYER_H
#define LAYER_H

#include "objects/object.h"

#include <string>

// Class representing a tile layer
class Layer : public Object
{
    // Map needs to access protected/private data
    friend class Map;

public:
    explicit Layer(Map &map) : Object(map) { }
    ~Layer() override { delete[] tilemap; }

    void draw(sf::RenderWindow &window) override;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

protected:
    int id = 0;
    std::string name;
    int width = 0;
    int height = 0;
    bool visible = false;
    unsigned int *tilemap = nullptr;
};

#endif
