#include "game.h"
#pragma once

SDL_Texture* character;
SDL_Rect srcR, destR;

Game::Game()
{}
Game::~Game()
{}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullScr) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL cannot be initialized: " << SDL_GetError() << std::endl;
	}
	else
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullScr);
		if (window == NULL)
		{
			std::cout << "Window cannot be created: " << SDL_GetError() << std::endl;
			isRunning = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer == NULL)
			{
				std::cout << "Renderer cannot be created: " << SDL_GetError() << std::endl;
				isRunning = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_Surface* tempSurface = IMG_Load("assets/character.png");
				character = SDL_CreateTextureFromSurface(renderer,tempSurface);
				SDL_FreeSurface(tempSurface);
			}
		}
	}
}
void Game::update()
{
	cnt++;
	destR.w = 300;
	destR.h = 150;
	destR.x = 32;
	std::cout << cnt << std::endl;

}
void Game::handleEvents()
{
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type){
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}
void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, character, NULL, &destR);
	SDL_RenderPresent(renderer);
}
