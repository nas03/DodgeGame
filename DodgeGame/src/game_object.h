#include <SDL.h>
#include <SDL_image.h>
#pragma once
class GameObject
{
public: 
    GameObject(SDL_Renderer * renderer);
    ~GameObject();

    float x;
    float y;
    float width;
    float height;
protected:
    SDL_Renderer * renderer;
};