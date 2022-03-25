#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#include "character.h"
#include "time.h"
#pragma once

class Game{
private:
	SDL_Window* window;
	int cnt = 0;
	bool isRunning = true;
	SDL_Renderer* renderer;
	Character* player;

	SDL_Event e;

	Timer fpsTimer;
	Timer capTimer;


	unsigned int countedFrames;
	float avgFPS;
public:
	Game();
	~Game();
	bool init();
	void newGame();
	void handleEvents();
	void handleInput();
	void clean();
	void update();
	void render();
	void run();
	bool running() { return isRunning;}

	
};