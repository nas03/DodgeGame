#include "fireball.h"
#include "const.h"
Fireball::Fireball(SDL_Renderer* renderer) : FlyingObject(renderer)
{
    path = "assets/fireball.png";

    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        std::cout <<"Cant create fireball surface: " <<SDL_GetError() <<std::endl;
    }
    else
    {
        SDL_SetColorKey(surface, 0, SDL_MapRGB(surface -> format, 255, 255,255));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            std::cout <<"Cant create fireball texture: " << SDL_GetError() <<std::endl;
        }
        else
        {
            Box.h = surface -> h;
            Box.w = surface -> w;
        }
    }
    SDL_FreeSurface(surface);

    x = rand() % SCREEN_WIDTH;
	y = 0;
	flySpeed = 5;

	Box.w = 80;
	Box.h = 60;
	Box.x = x;
	Box.y = y - Box.h;
}
Fireball::Fireball(SDL_Renderer* renderer,int xpos, int ypos) : FlyingObject(renderer)
{
    path = "assets/fireball.png";

    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        std::cout <<"Cant create fireball surface: " <<SDL_GetError() <<std::endl;
    }
    else
    {
        SDL_SetColorKey(surface, 0, SDL_MapRGB(surface -> format, 255, 255,255));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            std::cout <<"Cant create fireball texture: " << SDL_GetError() <<std::endl;
        }
        else
        {
            Box.h = surface -> h;
            Box.w = surface -> w;
        }
    }
    SDL_FreeSurface(surface);

    x = xpos;
	y = ypos;
	flySpeed = 5;

	Box.w = 80;
	Box.h = 60;
	Box.x = x;
	Box.y = y - Box.h;
}
Fireball::~Fireball()
{
    SDL_DestroyTexture(texture);
}
bool Fireball::checkCollision(SDL_Rect* mainCollider, SDL_Rect* leftCollider, SDL_Rect* rightCollider)
{
    if (SDL_HasIntersection(mainCollider, &collisionRect))
	{
		return true;
	}
	if (SDL_HasIntersection(leftCollider, &collisionRect))
	{
		return true;
	}
	if (SDL_HasIntersection(rightCollider, &collisionRect))
	{
		return true;
	}

	return false;
}
void Fireball::Update()
{
    Box.y += flySpeed;
}

void Fireball::Render()
{
    collisionRect.x = Box.x;
	collisionRect.y = Box.y;
	collisionRect.w = Box.w;
	collisionRect.h = Box.h;

	clip.x = 0;
	clip.y = 0;
	clip.w = 80;
	clip.h = 60;

    SDL_RenderCopy(renderer, texture, &clip, &Box);
}
int Fireball::getX()
{
    return Box.x;
}
int Fireball::getY()
{
    return Box.y;
}