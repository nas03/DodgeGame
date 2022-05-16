#include "invincible.h"


Invincible::Invincible(SDL_Renderer* renderer,const char* path) : GameObject(renderer)
{
     surface = IMG_Load("assets/invincible.png");
    if (surface == NULL)
    {
        std::cout <<"Cant create Invincible surface: " <<SDL_GetError() <<std::endl;
    }
    else
    {
        SDL_SetColorKey(surface, 0, SDL_MapRGB(surface -> format, 255, 255,255));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            std::cout <<"Cant create Invincible texture: " << SDL_GetError() <<std::endl;
        }
        else
        {
            SDL_FreeSurface(surface);
            x = 20;
            y = 210;
            width = 128;
            height = 128;
        }
    }
}
Invincible::~Invincible()
{
    SDL_DestroyTexture(texture);
}
void Invincible::Render()
{
    SDL_Rect desRect;
    desRect.x = x;
    desRect.y =y;
    desRect.w =width;
    desRect.h = height;   

    SDL_RenderCopy(renderer, texture, NULL, &desRect);
}