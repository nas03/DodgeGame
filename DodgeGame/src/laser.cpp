#include "laser.h"
Laser::Laser(SDL_Renderer* renderer,int xpos, int ypos) : FlyingObject(renderer)
{
    path = "assets/laser.png";
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        std::cout << "Cant load laser surface: " << SDL_GetError() << std::endl;
    }
    else
    {
        SDL_SetColorKey(surface, 0,SDL_MapRGB(surface -> format, 255,255,255));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            std::cout << "Cant create laser texture: " << SDL_GetError() << std::endl;
        }
        else
        {
            Box.h = surface ->h;
            Box.w = surface -> w;
        }
    }
    SDL_FreeSurface(surface);
    x = xpos;
    y = ypos;
    flySpeed = 15;

    Box.w = 60;
    Box.h = 80;
    Box.x = x;
    Box.y = y;
}
Laser::~Laser()
{
    SDL_DestroyTexture(texture);
}

void Laser::Render()
{
	renderRect.x = 0;
	renderRect.y = 0;
	renderRect.h = 60;
	renderRect.w = 80;
	SDL_RenderCopy(renderer, texture, &renderRect, &Box);

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
void Laser::Update()
{
    Box.y -= flySpeed;
}

