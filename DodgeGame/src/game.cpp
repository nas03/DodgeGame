#include "game.h"
#include "game_object.h"
#include "const.h"
#include "character.h"
#include "time.h"

Game::Game()
{}
Game::~Game()
{}

bool Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL cannot be initialized: " << SDL_GetError() << std::endl;
	}
	else
	{
		window = SDL_CreateWindow("Dodge Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window cannot be created: " << SDL_GetError() << std::endl;
			isRunning = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				std::cout << "Renderer cannot be created: " << SDL_GetError() << std::endl;
				isRunning = false;
			}
		}
	}
	return isRunning;
}

void Game::newGame()
{
	delete player;
	player = new Character(renderer,"assets/character.png");
}

void Game::update()
{
	cnt++;
	handleInput();
	player -> Render();
	std::cout << cnt << std::endl;
}
void Game::handleInput()
{
	const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
	if (currentKeyState[SDL_SCANCODE_A] || currentKeyState[SDL_SCANCODE_LEFT])
	{
		player->moveLeft();
	}
	if (currentKeyState[SDL_SCANCODE_D] || currentKeyState[SDL_SCANCODE_RIGHT])
	{
		player->moveRight();
	}
	if (currentKeyState[SDL_SCANCODE_S] || currentKeyState[SDL_SCANCODE_DOWN])
	{
		player -> moveDown();
	}
	if (currentKeyState[SDL_SCANCODE_W] || currentKeyState[SDL_SCANCODE_UP])
	{
		player -> moveUp();
	}
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
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	player -> Render();
	SDL_RenderPresent(renderer);
}
void Game::run()
{
	newGame();
		while (1)
	{
		capTimer.start();
		if (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				break;
			}
		}

		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		update();
		render();
		++countedFrames;

		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	clean();

}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}