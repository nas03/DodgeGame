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
	//Init var
	missileCd = 30;
	health = 3;
	score = 0;
	fireballRate = 30;
	//Create obj
	background = new Background(renderer,"assets/background.jpeg",0,0);
	player = new Character(renderer,"assets/player2.png");
	text = new Text (renderer);
	missile = new Missile(renderer,"assets/missile.png");
	
	healthBar3 = new Background(renderer, "assets/HEALTH3.png",130,200);
	healthBar2 = new Background(renderer, "assets/HEALTH2.png",130,200);
	healthBar1 = new Background(renderer, "assets/HEALTH1.png",130,200);
	//Create music
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
	//update bestScore
	if (score > bestScore)
	{
		bestScore = score;
	}
	//Empty fireball list
	if (!fireballList.empty())
	{
		fireballList.erase(fireballList.begin(), fireballList.end());
	}
}

void Game::update()
{
	cnt++;
	handleInput();
	iterateList();
	//Create Fireball
	if (countedFrames % fireballRate == 0)
	{
		fireball = new Fireball(renderer);
		fireballList.push_back(fireball);
	}
	
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
	//If use missile
	if (currentKeyState[SDL_SCANCODE_M])
	{
		if (missileCd <= 0)
		{
			boom = new Background(renderer,"assets/boom.png", SCREEN_WIDTH/2 - 300,SCREEN_HEIGHT/2-200);
			explode = true;
			int tempScore = score;
			int *nScore = &score;
			int tempHealth = health;
			int	*nHealth = &health;
			newGame();
			*nScore = tempScore;
			*nHealth = tempHealth;
		}
	}
}
void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	//Render necessary obj
	background -> Render();
	missile -> Render();
	player -> Render();
	//Render health bar
	if (health == 3) healthBar3 -> Render();
	if (health == 2) healthBar2 -> Render();
	if (health == 1) healthBar1 -> Render();
	//Render pause img
	if (pause == true)
	{
		menu -> Render();
	}
	//Render missile explosion
	if (explode)
	{
		boom -> Render();
	}
	//Render text
	text -> drawText("Score: ", 20,10,20);
	text -> drawText(std::to_string(score),170,10,20);
	text -> drawText("Best Score: ", 20,40,20);
	text -> drawText(std::to_string(bestScore),170,40,20);
	text -> drawText("HEALTH: ",20,200,20);
	//Render missile cd
	if(missileCd >= 0)
	{
		text -> drawText(std::to_string(missileCd),55+30,115,35);
	}
	else if (missileCd < 0)
	{
		text -> drawText("READY!",55+30,115,35);
	}
	//Render fireball + check if collide with character
	for(Fireball* currentFireball : fireballList)
	{
		currentFireball->Render();
		if (currentFireball->checkCollision(player->getMainCollider(), player->getLeftCollider(), player->getRightCollider()))
		{	
			audio ->playMusic("assets/hit.wav");
			health--;
			if (health <= 0){
				audio -> playMusic("assets/gameOver.wav");
				gameOver = new Background(renderer,"assets/gameOver.png",SCREEN_WIDTH/2 - 300,SCREEN_HEIGHT/2-200);
				SDL_RenderClear(renderer);
				gameOver -> Render();
				SDL_RenderPresent(renderer);
				SDL_Delay(2000);
				newGame();
				return;
			}
			else
			{
				int tempHealth = health;
				int	*nHealth = &health;
				int tempScore = score;
				int *nScore = &score;
				int tempCd = missileCd;
				int *nCd = &missileCd;
				newGame();
				*nHealth = tempHealth;
				*nScore = tempScore;
				*nCd = tempCd;
				return;
			}
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
		//Delete fireball when fall out of screen
		if ((*currentFireball)->Box.y > SCREEN_HEIGHT)
		{
			delete(*currentFireball);
			currentFireball++;
			fireballList.erase(fireballList.begin());
			//Update bestscore
			if (score >= bestScore)
			{
				bestScore = score;
			}
			score++;
			//missile cd  = score increment
			missileCd--;
			levelUp();
		}
		(*currentFireball)->Update();
	}
}
void Game::levelUp()
{
	if (score > 500) fireballRate = 5;
	else if (score > 100 ) fireballRate = 15;
	else if (score > 50) fireballRate = 20;
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
void Game::gameMenu()
{
	startMenu = new Background(renderer, "assets/startMenu.jpg",0,0);
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