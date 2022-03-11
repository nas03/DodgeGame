#pragma once
#include "game_object.h"
#include "texture.h"
#include "game.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objectTexture = TextureManager::loadTexture(textureSheet);
	
	xpos = x;
	ypos = y;
}

void GameObject::Update()
{

	srcRect.h = 64;
	srcRect.w = 128;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w*2;
	destRect.h = srcRect.h*2;
}
void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objectTexture,&srcRect, &destRect);
}