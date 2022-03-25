#include <SDL.h>
#include <SDL_image.h>
#include "game_object.h"
#include <iostream>
#include "const.h"
#pragma once
class Character : public GameObject
{
public:
    Character(SDL_Renderer* renderer, const char* path);
	~Character();

	void Render();

	
	void moveLeft();
	void moveRight();
    void moveUp();
    void moveDown();
	
	SDL_Rect* getMainCollider() { return &mainColliderRect; }
	SDL_Rect* getLeftCollider() { return &leftColliderRect; }
	SDL_Rect* getRightCollider() { return &rightColliderRect; }

private:
	SDL_Texture* texture;
	SDL_Rect renderRect;
	SDL_Rect mainColliderRect;
	SDL_Rect leftColliderRect;
	SDL_Rect rightColliderRect; 
};