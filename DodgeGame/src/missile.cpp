#include "missile.h"

Missile::Missile(SDL_Renderer* renderer,const char* path) : GameObject(renderer)
{
     surface = IMG_Load("assets/missile.png");
    if (surface == NULL)
    {
        std::cout <<"Cant create missile surface: " <<SDL_GetError() <<std::endl;
    }
    else
    {
        SDL_SetColorKey(surface, 0, SDL_MapRGB(surface -> format, 255, 255,255));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            std::cout <<"Cant create missile texture: " << SDL_GetError() <<std::endl;
        }
        else
        {
            SDL_FreeSurface(surface);
            x = 0;
            y = 100;
            width = 60;
            height = 120;
        }
    }
}
Missile::~Missile()
{
    SDL_DestroyTexture(texture);
}
void Missile::Render()
{
    SDL_Rect desRect;
    desRect.x = x;
    desRect.y =y;
    desRect.w =width;
    desRect.h = height;   

    SDL_RenderCopy(renderer, texture, NULL, &desRect);
}