#include "player.h"
#include <iostream>

Player::Player(Map &map): Object(map)
{
    jumpAnimation = map.GetAnimation(295);
    runAnimation = map.GetAnimation(291);
    bigRunAnimation = map.GetAnimation(299);
    bigJumpAnimation = map.GetAnimation(303);
    growAnimation = map.GetAnimation(306);
    jumpSoundBuffer.loadFromFile("sounds/jump.wav");
    jumpSound.setBuffer(jumpSoundBuffer);
    growSoundBuffer.loadFromFile("sounds/grow.wav");
    growSound.setBuffer(growSoundBuffer);
}

void Player::SetPosition(float x, float y)
{
    sprite.setPosition(x,y);
}

void Player::draw(sf::RenderWindow &window)
{


    map.SetSpriteTextureFromGid(sprite, animation->GetFrame());

    /*
    if(!marioIsBig)
    {
        sprite.setTextureRect(
                sf::IntRect(
                        sprite.getTextureRect().left+8,
                        sprite.getTextureRect().top+16,
                        16,
                        16));
    }
     */

    if(visible)
        window.draw(sprite);
}

void Player::mapCollision(sf::Sprite &mapSprite)
{

    if (mapSprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
    {
        float playerLeft = sprite.getPosition().x+4;
        float playerRight = sprite.getPosition().x + (float) width-4;
        float tileLeft = mapSprite.getPosition().x;
        float tileRight = mapSprite.getPosition().x + (float) map.GetTileWidth();
        float playerCenter = playerLeft+(float)width/2;
        float playerBottom = sprite.getPosition().y + (float)height;
        float playerTop = sprite.getPosition().y;
        float tileTop = mapSprite.getPosition().y;
        float tileBottom = mapSprite.getPosition().y+(float) map.GetTileHeight();

        if(!marioIsBig)
        {
            playerTop += 16;
            playerLeft +=4;
            playerRight-=4;
        }

        //Check down collision
        if (tileTop < playerBottom
        && playerCenter < tileRight
        && playerCenter > tileLeft
        )
        {
            dCollision = true;
            //uCollision = false;
        }

        /*
        //Check up collision
        if (playerTop > tileBottom
        && playerCenter < tileRight
        && playerCenter > tileLeft
        )
        {
            uCollision = true;
        }
        */

        //Make sure sprite is not part of the ground where Mario walks
        if (tileTop < playerBottom-2) {

            //Check left collision
            if (playerLeft < tileRight && tileLeft < playerLeft) {
                sprite.move(1,0);
                lCollision = true;
            }

            //Check right collision
            if (tileLeft < playerRight-2 && tileRight > playerRight-2) {
                sprite.move(-1,0);
                rCollision = true;
            }
        }

    }
}

bool Player::coinCollision(sf::Sprite &coinSprite)
{
    if(sprite.getGlobalBounds().intersects(coinSprite.getGlobalBounds()))
    {
        float playerTop = sprite.getPosition().y;
        if(!marioIsBig)
            playerTop+=16;
        float tileBottom = coinSprite.getPosition().y + (float)map.GetTileHeight();

        if(playerTop < tileBottom)
            return true;
    }

    return false;
  }

bool Player::blockCollision(sf::Sprite &blockSprite, bool broken)
{
    if (sprite.getGlobalBounds().intersects(blockSprite.getGlobalBounds()) && !broken) {

        float playerLeft = sprite.getPosition().x + 4;
        float playerRight = sprite.getPosition().x + (float) width - 4;
        float playerTop = sprite.getPosition().y;
        float playerCenter = playerLeft+(float)width/2;

        if (!marioIsBig)
        {
            playerTop += 16;
            playerLeft += 4;
            playerRight -= 4;
        }

        float tileBottom = blockSprite.getPosition().y + (float)map.GetTileHeight();
        float tileLeft = blockSprite.getPosition().x;
        float tileRight = blockSprite.getPosition().x + (float) map.GetTileWidth();


        if(playerTop < tileBottom
           && playerCenter < tileRight
           && playerCenter > tileLeft
        )
        {
            //uCollision = true;
            return true;
        }

    }
    return false;
}

bool Player::mushroomCollision(sf::Sprite &mushroomSprite, bool grow)
{
    if (sprite.getGlobalBounds().intersects(mushroomSprite.getGlobalBounds()) && !marioIsBig)
    {
        if(grow)
        {
            marioIsBig = true;
            jumpTime = jumpTime*1.2;
            jumpSpeed = jumpSpeed*1.5;
            growSound.play();
            growClock.restart();
        }

        return true;
    }
    return false;
}

void Player::logic(float deltaTime)
{
    // Gravity
    if(dCollision)
    {
        ySpeed = 0;
        dCollision = false ;
        jumpTimer.restart();
    }
    else
        ySpeed = gravity;

    //jump
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
    || sf::Joystick::isButtonPressed(0,0) )
    && reJump)
    {
        ySpeed = jumpSpeed;
        if(jumpTimer.getElapsedTime().asMilliseconds() > jumpTime)
        {
            ySpeed = gravity;
            reJump = false;
            rCollision = false;
            lCollision = false;
        }

    }

    //Check for movement
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
    || sf::Joystick::getAxisPosition(0,sf::Joystick::X) > 50)
    {
        if(rCollision)
            xSpeed = 0;
        else
            xSpeed = 100;
        lCollision = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
    || sf::Joystick::getAxisPosition(0,sf::Joystick::X) < -50)
    {
        if(lCollision)
            xSpeed = 0;
        else
            xSpeed = -100;
        rCollision = false;

    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
    && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
    && sf::Joystick::getAxisPosition(0,sf::Joystick::X) < 50
    && sf::Joystick::getAxisPosition(0,sf::Joystick::X) > -50)
        xSpeed = 0;

    // select animation
    if(marioIsBig && growClock.getElapsedTime().asMilliseconds() < 500)
        animation = growAnimation;
    else if(marioIsBig)
    {
        if (ySpeed < 0)
            animation=bigJumpAnimation;
        else if(xSpeed != 0)
            animation = bigRunAnimation;
        else
            animation = map.GetAnimation(298);
    }
    else
    {
        if (ySpeed < 0)
            animation=jumpAnimation;
        else if(xSpeed != 0)
            animation = runAnimation;
        else
            animation = map.GetAnimation(gid);
    }


    sprite.move(xSpeed * deltaTime, ySpeed * deltaTime);
}
