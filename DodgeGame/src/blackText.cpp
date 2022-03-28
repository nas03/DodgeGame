#include "blackText.h"

BlackText::BlackText(SDL_Renderer* renderer)
{
    this -> renderer = renderer;
}
void BlackText::drawText(std::string text, int x, int y, int fontSize)
{
    TTF_Font * font = TTF_OpenFont("assets/JackPixel.ttf", fontSize);
	if (font == NULL)
	{
		std::cout <<"Cant create text font: " <<SDL_GetError() <<std::endl;
	}
    SDL_Color textColor = {0,0,0};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (surface == NULL)
	{
		std::cout <<"Cant create text surface: " <<SDL_GetError()<<std::endl;
	}
	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect sizeRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surface->w;
	sizeRect.h = surface->h;

	SDL_Rect posRect;
	posRect.x = x;
	posRect.y = y;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(renderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}