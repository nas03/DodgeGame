#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#pragma once
class Game{
private:
	SDL_Window* window;
	int cnt = 0;
	bool isRunning = true;
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullScr);
	
	void handleEvents();
	void clean();
	void update();
	void render();
	bool running() { return isRunning;}

	static SDL_Renderer* renderer;
};