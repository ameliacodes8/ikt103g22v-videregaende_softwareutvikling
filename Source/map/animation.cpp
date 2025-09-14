#include "animation.h"

AnimationFrame::AnimationFrame()
{
    nextFrame = this;
    tileId = 0;
    duration = -1;
}

Animation::Animation()
{
    currentFrame = nullptr;
    frameTime.restart();
}

Animation::Animation(unsigned int gid)
{
    currentFrame = new AnimationFrame();
    currentFrame->tileId = gid;
}


void Animation::AddFrame(AnimationFrame *frame)
{
    if(currentFrame == nullptr)
    {
        currentFrame = frame;
        currentFrame->nextFrame = currentFrame;
    }
    else
    {
        auto temp = currentFrame;
        while(temp->nextFrame != currentFrame)
        {
            temp = temp->nextFrame;
        }
        temp->nextFrame = frame;
        frame->nextFrame = currentFrame;
    }
}

unsigned int Animation::GetFrame()
{
    if(frameTime.getElapsedTime().asMilliseconds() >= currentFrame->duration)
    {
        currentFrame = currentFrame->GetNextFrame();
        frameTime.restart();
    }
    return currentFrame->tileId;
}