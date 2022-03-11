#pragma once
#include "game.h"
#include <string>
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	void loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};