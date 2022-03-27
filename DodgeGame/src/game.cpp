#include "game.h"


Game::Game()
{
}
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
	if (TTF_Init() < 0)
	{
		std::cout <<"TTF cannot be created: " <<SDL_GetError() <<std::endl;
		isRunning = false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		isRunning = false;
	}
	return isRunning;
}

void Game::newGame()
{
	delete player;
	delete text;
	missileCd = 30;
	background = new Background(renderer,"assets/background.jpeg",0,0);
	player = new Character(renderer,"assets/player2.png");
	text = new Text (renderer);
	missile = new Missile(renderer,"assets/missile.png");
	Mix_VolumeMusic(20);
	audio ->playMusic("assets/newGame.wav");
	music = Mix_LoadMUS("assets/spaceMusic.mp3");
	if (music == NULL)
	{
		std::cout << "Cant load music" <<Mix_GetError() <<std::endl;
	}

	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(music, -1);
	}
	if (score > bestScore)
	{
		bestScore = score;
	}
	score = 0;
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
	const Uint8*currentKeyState = SDL_GetKeyboardState(NULL);
	if (currentKeyState[SDL_SCANCODE_A] || currentKeyState[SDL_SCANCODE_LEFT])
	{
		player->moveLeft();
		audio ->playMusic("assets/shipMoving.wav");
	}
	if (currentKeyState[SDL_SCANCODE_D] || currentKeyState[SDL_SCANCODE_RIGHT])
	{
		player->moveRight();
		audio ->playMusic("assets/shipMoving.wav");
	}
	if (currentKeyState[SDL_SCANCODE_S] || currentKeyState[SDL_SCANCODE_DOWN])
	{
		player -> moveDown();
		audio ->playMusic("assets/shipMoving.wav");
	}
	if (currentKeyState[SDL_SCANCODE_W] || currentKeyState[SDL_SCANCODE_UP])
	{
		player -> moveUp();
		audio ->playMusic("assets/shipMoving.wav");
	}
	if (currentKeyState[SDL_SCANCODE_M])
	{
		if (missileCd <= 0)
		{
			
			boom = new Background(renderer,"assets/boom.png", SCREEN_WIDTH/2 - 300,SCREEN_HEIGHT/2-200);
			explode = true;
			int tempScore = score;
			int *nScore = &score;
			newGame();
			*nScore = tempScore;
		}
	}
}
void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	background -> Render();
	missile -> Render();
	player -> Render();
	if (pause == true)
	{
		menu -> Render();
	}
	if (explode)
	{
		boom -> Render();
	}
	text -> drawText("Score: ", 0,10,20);
	text -> drawText(std::to_string(score),150,10,20);
	text -> drawText("Best Score: ", 0,40,20);
	text -> drawText(std::to_string(bestScore),150,40,20);
	if(missileCd >= 0)
	{
		text -> drawText(std::to_string(missileCd),55,150,35);
	}
	else if (missileCd < 0)
	{
		text -> drawText("READY!",55,150,35);
	}
	for(Fireball* currentFireball : fireballList)
	{
		currentFireball->Render();
		
		if (currentFireball->checkCollision(player->getMainCollider(), player->getLeftCollider(), player->getRightCollider()))
		{	
			audio ->playMusic("assets/hit.wav");
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
			if (score >= bestScore) bestScore++;
			score++;
			missileCd--;
			levelUp();
		}
		(*currentFireball)->Update();
	}
}
void Game::levelUp()
{
	if (score > 1000) fireballRate = 5;
	else if (score > 500 ) fireballRate = 15;
	else if (score > 100) fireballRate = 20;
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
		if (pause == false) update();
		if (e.key.keysym.sym == SDLK_c)
		{
			audio -> playMusic("assets/continue.wav");
			pause = false;
		}
		if (e.key.keysym.sym == SDLK_p) 
		{
			pause = true;
			audio -> playMusic("assets/pause.wav");
			menu = new Menu(renderer,"assets/pause.png");
		}
		render();
		if (explode == true){
			audio -> playMusic("assets/explosionSound.wav");
			SDL_Delay(2000);
		} 
		explode = false;
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 1000000000)
		{
			avgFPS = 0;
		}
		
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
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	std::cout << "Game cleaned" << std::endl;
}