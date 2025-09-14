#ifndef MARIO_PIPE_H
#define MARIO_PIPE_H

#include "object.h"

class Pipe : public Object
{
public:
    explicit Pipe(Map &map): Object(map){}
    void draw(sf::RenderWindow &window) override;
    void logic(float deltaTime) override;
    bool playerCollision();

};


#endif //MARIO_PIPE_H
