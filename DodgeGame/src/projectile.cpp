#include "projectile.h"
#pragma once
#include "texture.h"
#include "game.h"

Projectile::Projectile(const char* textureSheet, int x, int y)
{
	projectile = TextureManager::loadTexture(textureSheet);

	xpos = x;
	ypos = y;
}

void Projectile::ProjectileUpdate()
{
	xpos++;
	ypos++;

	srcRect.h = 64;
	srcRect.w = 128;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}
void Projectile::ProjectileRender()
{
	SDL_RenderCopy(Game::renderer, projectile, &srcRect, &destRect);
}