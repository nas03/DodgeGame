#include "game.h"
#include "texture.h"
#include "game_object.h"
#include "projectile.h"
GameObject* character;
SDL_Renderer* Game::renderer = nullptr;
Projectile* projectile;
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
			}
			
			character = new GameObject("assets/character.png",0,0);
		}
	}
}


void Game::update()
{
	cnt++;
	projectile->ProjectileUpdate();
	character->Update();
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
void Game::render()
{
	SDL_RenderClear(renderer);
	
	character->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}