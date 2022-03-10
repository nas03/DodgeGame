#include "game.h"

#pragma once
Game* game = nullptr;
const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;
int main(int argc, char* argv[])
{
	game = new Game();
	game->init("Dodge Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	return 0;
}
