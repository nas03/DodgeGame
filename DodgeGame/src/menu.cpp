#include "menu.h"
#include "const.h"
Menu::Menu(SDL_Renderer* renderer, const char *path) : GameObject(renderer)
{
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        std::cout <<"cant create menu surface: " <<SDL_GetError()<<std::endl;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            std::cout <<"Cant create menu texture: " <<SDL_GetError() <<std::endl;
        }
        else
        {
            SDL_FreeSurface(surface);
            x = 0;
            y = 0;
            width = 100;
            height = 100;
            
        }
    }
}
Menu::~Menu()
{
    SDL_DestroyTexture(texture);
}
void Menu::Render()
{
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = width;
    srcRect.h = height;
    SDL_Rect desRect;
    desRect.x = SCREEN_WIDTH /2 - 55;
    desRect.y = SCREEN_HEIGHT /2 - 55;
    desRect.w = srcRect.w;    
    desRect.h = srcRect.h;
    SDL_RenderCopy(renderer,texture,&srcRect,&desRect);   
    
}