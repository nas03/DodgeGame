#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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
#include "menu.h"
#include "music.h"
#include "missile.h"
#pragma once

class Game{
private:
	SDL_Window* window = NULL;
	int cnt = 0;
	bool isRunning = true;
	bool pause = false;
	bool explode = false;
	SDL_Renderer* renderer = NULL;
	Background* background = NULL;
	Character* player  = NULL;
	Fireball* fireball  = NULL;
	Missile* missile = NULL;
	Background* boom = NULL;
	Mix_Music* music = NULL;
	Music* audio;
	SDL_Event e;
	std::list<Fireball*> fireballList;
	Text* text= NULL;
	Menu* menu;
	

	Timer fpsTimer;
	Timer capTimer;
	int missileCd;
	int score = 0;
	int bestScore = 0;
	unsigned int fireballRate;
	unsigned int countedFrames;
	float avgFPS;
public:
	Game();
	~Game();
	bool init();
	void newGame();
	void levelUp();
	void checkScreenCollisions(GameObject* obj);
	void iterateList();
	void handleInput();
	void update();
	void render();
	void run();
	void clean();
	

	
};