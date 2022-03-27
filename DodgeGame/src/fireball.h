#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "flying_object.h"

class Fireball : public FlyingObject
{
public:
    Fireball(SDL_Renderer* renderer);
    ~Fireball();

    bool checkCollision(SDL_Rect * mainCollider, SDL_Rect* leftCollider, SDL_Rect * rightCollider);
    void Update();
    void Render();
    void getFireball();
    void levelUp();
private:
    SDL_Texture* texture;
    SDL_Rect collisionRect;
    SDL_Rect clip;
    const char* path;
};