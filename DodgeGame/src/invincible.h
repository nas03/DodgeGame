#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "game_object.h"


class Invincible : public GameObject
{
public:
    Invincible(SDL_Renderer*renderer, const char* path);
    ~Invincible();
    void Render();
    void Update();
private:
    SDL_Texture* texture;
    SDL_Surface* surface;
};
