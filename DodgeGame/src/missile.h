#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "game_object.h"


class Missile : public GameObject
{
public:
    Missile(SDL_Renderer*renderer, const char* path);
    ~Missile();
    void Render();
    void Update();
private:
    SDL_Texture* texture;
    SDL_Surface* surface;
};
