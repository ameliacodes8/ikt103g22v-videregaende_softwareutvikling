#ifndef MARIO_ANIMATION_H
#define MARIO_ANIMATION_H

#include <SFML/Graphics.hpp>

class AnimationFrame
{
    friend class Map;
    friend class Animation;
public:
    explicit AnimationFrame();
    ~AnimationFrame(){} //TODO implement AnimationFrame deconstructor

    AnimationFrame *GetNextFrame() {return nextFrame;}

protected:
    unsigned int tileId;
    AnimationFrame *nextFrame;
    int duration;
};

class Animation
{
    friend class Map;
public:
    explicit Animation();
    explicit Animation(unsigned int gid);
    ~Animation(){} //TODO implement Animation deconstructor
    unsigned int GetFrame();
    void AddFrame(AnimationFrame *frame);

protected:
    AnimationFrame *currentFrame;
    sf::Clock frameTime;

};




#endif //MARIO_ANIMATION_H
