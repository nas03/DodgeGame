#pragma once
#include "SDL.h"
#include "texture.h"
class GameObject {
public:
	GameObject(const char* textureSheet,int x, int y);
	~GameObject();
	void Update();
	void Render();
private:
	//Screen position
	int xpos;
	int ypos;
	
	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer ;
};