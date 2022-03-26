#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "game_object.h"

class Background : public GameObject
{
public:
    Background(SDL_Renderer*renderer, const char* path);
    ~Background();
    void Render();
private:
    SDL_Texture* texture;
    SDL_Surface* surface;
};