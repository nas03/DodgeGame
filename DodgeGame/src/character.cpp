#include "character.h"

Character::Character(SDL_Renderer* renderer, const char* path):GameObject(renderer)
{
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        std::cout <<"Cant load character surface: " <<SDL_GetError()<<std::endl;
    }
    else
    {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface -> format, 69, 69, 69));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            std::cout <<"Cant load character texture: " <<SDL_GetError() <<std::endl;
        }
        else
        {
            renderRect.h = surface -> h;
            renderRect.w = surface -> w;
        }
    }
    SDL_FreeSurface(surface);
    
    x = (SCREEN_WIDTH / 2) - (renderRect.w / 2);
	y = SCREEN_HEIGHT * 0.80;
	width = 80;
	height = 80;
}
Character::~Character()
{
    SDL_DestroyTexture(texture);
}
void Character::Render()
{
	renderRect.x = x;
	renderRect.y = y;
	renderRect.h = height;
	renderRect.w = width;
	SDL_RenderCopy(renderer, texture, NULL, &renderRect);

	mainColliderRect.x = x + 25;
	mainColliderRect.y = y;
	mainColliderRect.h = height;
	mainColliderRect.w = width;

	leftColliderRect.x = x;
	leftColliderRect.y = y + 50;
	leftColliderRect.h = 40;
	leftColliderRect.w = 25;

	rightColliderRect.x = x + 75;
	rightColliderRect.y = y + 50;
	rightColliderRect.h = 40;
	rightColliderRect.w = 25;

}

void Character::moveLeft()
{
	x -= 5;
}

void Character::moveRight()
{
	x += 5;
}
void Character::moveUp()
{
    y -= 5;
}
void Character::moveDown()
{
    y += 5;
}
double Character::getX()
{
    return x;
}
double Character::getY()
{
    return y;
}