#pragma once
#include "SDL.h"
#include "SDL_image.h"

class TextureManager {
public:
	static SDL_Texture* loadTexture(const char* textureFile);
};
