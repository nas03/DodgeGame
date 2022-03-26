#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#include <list>
#include "character.h"
#include "time.h"
#include "fireball.h"
#pragma once

class Game{
private:
	SDL_Window* window;
	int cnt = 0;
	bool isRunning = true;
	SDL_Renderer* renderer;
	Character* player;
	Fireball* fireball;
	SDL_Event e;
	std::list<Fireball*> firebalList;

	Timer fpsTimer;
	Timer capTimer;

	unsigned int fireballRate;
	unsigned int countedFrames;
	float avgFPS;
public:
	Game();
	~Game();
	bool init();
	void newGame();
	void handleEvents();
	void checkScreenCollisions(GameObject* obj);
	void iterateList();
	void handleInput();
	void clean();
	void update();
	void render();
	void run();
	bool running() { return isRunning;}

	
};