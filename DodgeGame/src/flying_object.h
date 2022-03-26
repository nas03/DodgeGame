#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <time.h>
#include "game_object.h"


class FlyingObject : public GameObject
{
public:
    FlyingObject(SDL_Renderer * renderer);
    ~FlyingObject();

    SDL_Rect Box;
    float flySpeed;
private:
};