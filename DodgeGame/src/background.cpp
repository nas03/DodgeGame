#include "background.h"

Background::Background(SDL_Renderer* renderer, const char* path) : GameObject(renderer)
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

        x = 0;
	    y = 0;
	    width = 1080;
	    height = 560;
    }
}
Background::~Background()
{
    SDL_DestroyTexture(texture);
}
void Background::Render()
{
    SDL_RenderCopy(renderer,texture,NULL,NULL);
}