#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <string.h>
#include <list>
#include "character.h"
#include "time.h"
#include "fireball.h"
#include "background.h"
#include "text.h"
#include "const.h"
#pragma once

class Game{
private:
	SDL_Window* window;
	int cnt = 0;
	bool isRunning = true;
	SDL_Renderer* renderer;
	Background* background;
	Character* player;
	Fireball* fireball;
	SDL_Event e;
	std::list<Fireball*> fireballList;
	Text* text;

	Timer fpsTimer;
	Timer capTimer;

	unsigned int score;
	unsigned int bestScore;
	unsigned int fireballRate;
	unsigned int countedFrames;
	float avgFPS;
public:
	Game();
	~Game();
	bool init();
	void newGame();
	void checkScreenCollisions(GameObject* obj);
	void iterateList();
	void handleInput();
	void clean();
	void update();
	void render();
	void run();
	bool running() { return isRunning;}

	
};