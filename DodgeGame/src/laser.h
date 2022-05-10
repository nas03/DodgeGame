#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "const.h"
#include "flying_object.h"
#include "character.h"

class Laser : public FlyingObject
{
public:
    Laser(SDL_Renderer* renderer, int xpos, int ypos);
    ~Laser();
    SDL_Rect* getMainCollider() { return &mainColliderRect; }
	SDL_Rect* getLeftCollider() { return &leftColliderRect; }
	SDL_Rect* getRightCollider() { return &rightColliderRect; }

    void Update();
    void Render();
private:
    SDL_Texture* texture;
    SDL_Rect renderRect;
    SDL_Rect mainColliderRect;
	SDL_Rect leftColliderRect;
	SDL_Rect rightColliderRect;
    SDL_Rect clip;
    const char* path;
};