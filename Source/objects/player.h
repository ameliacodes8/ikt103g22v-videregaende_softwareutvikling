#ifndef MARIO_PLAYER_H
#define MARIO_PLAYER_H

#include "object.h"
#include <SFML/Audio.hpp>

class Player : public Object
{
    friend class Layer;
    friend class Pipe;
public:
    explicit Player(Map &map);
    void draw(sf::RenderWindow &window) override;
    void logic(float deltaTime) override;
    void mapCollision(sf::Sprite &sprite);
    bool coinCollision(sf::Sprite &coinSprite);
    bool blockCollision(sf::Sprite &blockSprite, bool broken);
    bool mushroomCollision(sf::Sprite &mushroomSprite, bool grow);
    void SetPosition(float x, float y);
    sf::Sprite *GetSprite(){return &sprite;}
    bool reJump = true;
    sf::Sound jumpSound;

protected:
    Animation *runAnimation = nullptr;
    Animation *jumpAnimation = nullptr;
    Animation *growAnimation = nullptr;
    Animation *bigRunAnimation = nullptr;
    Animation *bigJumpAnimation = nullptr;
    bool dCollision = false;
    bool uCollision = false;
    bool lCollision = false;
    bool rCollision = false;
    sf::Clock jumpTimer;
    int jumpTime = 200;
    float jumpSpeed = -150;
    float gravity = 100;
    sf::SoundBuffer jumpSoundBuffer;
    bool marioIsBig = false;
    sf::Clock growClock;
    sf::SoundBuffer growSoundBuffer;
    sf::Sound growSound;



};


#endif //MARIO_PLAYER_H
