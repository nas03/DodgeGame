#pragma once
#include "SDL.h"
#include "texture.h"
class Projectile {
public:
	Projectile(const char* textureSheet, int x, int y);
	~Projectile();
	void ProjectileUpdate();
	void ProjectileRender();
private:
	//Screen position
	int xpos;
	int ypos;

	SDL_Texture* projectile;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};