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
#include "button.h"
#pragma once

class Game{
private:
	//Init
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	int cnt = 0;
	bool isRunning = true;
	bool runGame = false;
	bool runHowToPlay = false;
	bool runChooseChar = false;
	int chooseCharacter = 1;
	//Game 
	Background* background = NULL;
	Character * player     = NULL;
	//Fireball
	Fireball  * fireball   = NULL;
	std::list<Fireball*> fireballList;
	unsigned int fireballRate;
	//Invincible
	//Invincible* power = NULL;
	//std::list<Invincible* > powerList;
	//unsigned int powerRate;
	//Missile
	Missile   * missile    = NULL;
	Background* boom       = NULL;
	bool explode = false;
	int missileCd;
	//Menu
	Background* startMenu  = NULL;
	Background* howToPlayBG = NULL;
	//Health Bar
	int health = 3;
	Background* healthBar3 = NULL;
	Background* healthBar2 = NULL;
	Background* healthBar1 = NULL;
	Background* healthBar4 = NULL;
	Background* healthBar5 = NULL;

	//Effect
	Background* gameOver   = NULL;
	Text	  * text	   = NULL;
	Menu	  * pauseGame = NULL;
	Background	 * menu = NULL;
	bool pause = false;
	bool addHealth = false;
	//Music
	Mix_Music* music = NULL;
	Music* audio;
	//Event
	SDL_Event e;
	//Timer
	Timer fpsTimer;
	Timer capTimer;
	//Score
	int score = 0;
	int bestScore = 0;
	//FPS
	unsigned int countedFrames;
	float avgFPS;
public:
	Game();
	~Game();
	void gameMenu();
	void howToPlay();
	void chooseChar();
	bool init();
	bool running()
	{
		return runGame;
	}
	bool howToPlayRunning()
	{
		return runHowToPlay;
	}
	bool chooseCharRunning()
	{
		return runChooseChar;
	}
	void run();
	
	void newGame();
	
	void levelUp();
	void checkScreenCollisions(GameObject* obj);
	void handleInput();
	void iterateList();
	
	
	void update();
	void render();
	
	void clean();
	
};