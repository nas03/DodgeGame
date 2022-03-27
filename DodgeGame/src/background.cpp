#include "background.h"

Background::Background(SDL_Renderer* renderer, const char* path,int xpos, int ypos) : GameObject(renderer)
{
    surface = IMG_Load(path);
    if (surface == NULL)
    {
        std::cout <<"Cant create background surface: " <<SDL_GetError() <<std::endl;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            std::cout <<"Cant create background texture: " <<SDL_GetError() <<std::endl;
        }
        SDL_FreeSurface(surface);

        x = xpos;
	    y = ypos;
	    width = surface -> w;
	    height = surface -> h;
    }
}
Background::~Background()
{
    SDL_DestroyTexture(texture);
}
void Background::Render()
{
    SDL_Rect desRect;
    desRect.x = x;
    desRect.y = y;
    desRect.w = width;
    desRect.h = height;
    SDL_RenderCopy(renderer,texture,NULL,&desRect);
}