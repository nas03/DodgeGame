#include "game.h"
#include "game_object.h"
#include "const.h"
#include "character.h"
#include "time.h"
#include "fireball.h"
Game::Game()
{}
Game::~Game()
{}

bool Game::init() {
	srand(time(NULL));
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
	background = new Background(renderer,"assets/background.jpeg");
	player = new Character(renderer,"assets/player2.png");
	fireballRate = 30;
	if (countedFrames % fireballRate == 0)
	{
		fireball = new Fireball(renderer);
	}
	if (!fireballList.empty())
	{
		fireballList.erase(fireballList.begin(), fireballList.end());
	}
}

void Game::update()
{
	cnt++;
	handleInput();
	if (countedFrames % fireballRate == 0)
	{
		fireball = new Fireball(renderer);
		fireballList.push_back(fireball);
	}
	iterateList();
	checkScreenCollisions(player);
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
	background -> Render();
	player -> Render();

	for(Fireball* currentFireball : fireballList)
	{
		currentFireball->Render();
		//Check asteroid collision
		if (currentFireball->checkCollision(player->getMainCollider(), player->getLeftCollider(), player->getRightCollider()))
		{
			newGame();
			
			return;
		}
	}
	SDL_RenderPresent(renderer);
}
void Game::checkScreenCollisions(GameObject* obj)
{
	if (obj->x + obj->width > SCREEN_WIDTH)
	{
		obj->x = SCREEN_WIDTH - obj->width;
	}
	if (obj->x < 0)
	{
		obj->x = 0;
	}
	if (obj->y + obj->height > SCREEN_HEIGHT)
	{
		obj->y = SCREEN_HEIGHT - obj->height;
	}
	if (obj->y < 0)
	{
		obj->y = 0;
	}
}
void Game::iterateList()
{
	std::list<Fireball*>::iterator currentFireball;
	for (currentFireball = fireballList.begin(); currentFireball != fireballList.end(); currentFireball++)
	{
		if ((*currentFireball)->Box.y > SCREEN_HEIGHT)
		{
			delete(*currentFireball);
			currentFireball++;
			fireballList.erase(fireballList.begin());
			
		}
		(*currentFireball)->Update();
	}
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
		if (avgFPS > 1000000000)
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