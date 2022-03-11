#pragma once
#include "game.h"
Game* game = nullptr;


const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;



int main(int argc, char* argv[])
{
	Uint32 frameStart;
	int frameTime;
	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;

	game = new Game();
	game->init("Dodge Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
	while (game->running()) {
		frameStart = SDL_GetTicks();
		
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;

		//limit frame rates
		if (FRAME_DELAY > frameStart)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}
	game->clean();
	return 0;
}
