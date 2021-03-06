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
		window = SDL_CreateWindow("Space Mission", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	missileCd = 50;
	invincibleCd = 20;
	invincibleTime = 10;
	health = 3;
	score = 0;
	fireballRate = 30;
	Iactive = false;
	bestScore = save -> getMaxScore();
	//Create obj
	background = new Background(renderer,"assets/background.jpeg",0,0);
	healthBar3 = new Background(renderer, "assets/HEALTH3.png",130,200);
	healthBar2 = new Background(renderer, "assets/HEALTH2.png",130,200);
	healthBar1 = new Background(renderer, "assets/HEALTH1.png",130,200);

	if (chooseCharacter == 1)
	{
		player = new Character(renderer,"assets/player.png");
		player -> setSpeed(10);
	}	
	if (chooseCharacter == 2)
	{
		player = new Character(renderer,"assets/player2.png");
		player -> setSpeed(5);
		addHealth = true;
	}

	if (addHealth)
	{
		health = 5;
		healthBar4 = new Background(renderer, "assets/HEALTH4.png",130,200);
		healthBar5 = new Background(renderer, "assets/HEALTH5.png",130,200);
	}
	else health = 3;
	text = new Text (renderer);
	missile = new Missile(renderer,"assets/missile.png");
	invincible = new Invincible(renderer, "assets/invincible.png");
	
	//Create music
	Mix_VolumeMusic(20);
	music = Mix_LoadMUS("assets/spaceMusic.mp3");
	Mix_FadeInMusic(music,-1,2000);
	audio ->playMusic("assets/newGame.wav");
	if (music == NULL)
	{
		std::cout << "Cant load music" <<Mix_GetError() <<std::endl;
	}
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(music, -1);
	}
	
	//Update best score
	if(score >= bestScore)
	{
		bestScore++;
	}
	
	//Empty fireball list
	if (!fireballList.empty())
	{
		fireballList.erase(fireballList.begin(), fireballList.end());
	}
	save -> writeHaveSaved(0);
	
}

void Game::loadSavedGame()
{
	delete player;
	delete text;
	//Init var
	std::vector <int> effect = save -> getEffect();
	chooseCharacter = effect[1];
	missileCd = effect[3];
	invincibleCd = effect[4];
	invincibleTime = effect[5];
	health = effect[2];
	score = effect[0];
	fireballRate = 30;
	Iactive = false;
	bestScore = save -> getMaxScore();
	//Create obj
	background = new Background(renderer,"assets/background.jpeg",0,0);
	if (health == 1) healthBar1 = new Background(renderer, "assets/HEALTH1.png",130,200);
	if (health == 3) healthBar3 = new Background(renderer, "assets/HEALTH3.png",130,200);
	if (health == 2) healthBar2 = new Background(renderer, "assets/HEALTH2.png",130,200);
	if (health == 4) healthBar4 = new Background(renderer, "assets/HEALTH4.png",130,200);
	if (health == 5) healthBar5 = new Background(renderer, "assets/HEALTH5.png",130,200);

	text = new Text (renderer);
	missile = new Missile(renderer,"assets/missile.png");
	invincible = new Invincible(renderer, "assets/invincible.png");
	
	//Create music
	Mix_VolumeMusic(20);
	music = Mix_LoadMUS("assets/spaceMusic.mp3");
	Mix_FadeInMusic(music,-1,2000);
	audio ->playMusic("assets/newGame.wav");
	if (music == NULL)
	{
		std::cout << "Cant load music" <<Mix_GetError() <<std::endl;
	}
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(music, -1);
	}
	//getData
	std::vector <int> playerPos = save -> getPlayer();
	std::vector < std::vector <int> > fireballPos = save -> getFireball();
	if (chooseCharacter == 1)
	{
		player = new Character(renderer, playerPos[0],playerPos[1],"assets/player.png");
		player -> setSpeed(10);
	}	
	if (chooseCharacter == 2)
	{
		player = new Character(renderer, playerPos[0],playerPos[1],"assets/player2.png");
		player -> setSpeed(5);
		addHealth = true;
	}
	if (!fireballList.empty())
	{
		fireballList.erase(fireballList.begin(), fireballList.end());
	}
	for (int i = 0 ; i < fireballPos.size(); i++)
	{
		fireball = new Fireball(renderer, fireballPos[i][0] , fireballPos[i][1]);
		fireballList.push_back(fireball);
	}
}

void Game::update()
{
	
	handleInput();
	
	//Create Fireball
	if (countedFrames % fireballRate == 0)
	{
		fireball = new Fireball(renderer);
		fireballList.push_back(fireball);
	}
	
	iterateList();
	checkScreenCollisions(player);
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
			saveGame();
			loadSavedGame();
		}
	}
	if(currentKeyState[SDL_SCANCODE_I])
	{
		if (invincibleCd <= 0)
		{
			Iactive = true;
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
	invincible -> Render();
	//Render health bar
	if (health == 3) healthBar3 -> Render();
	if (health == 2) healthBar2 -> Render();
	if (health == 1) healthBar1 -> Render();
	if (health == 4) healthBar4 -> Render();
	if (health == 5) healthBar5 -> Render();
	//Render pause img
	if (pause == true)
	{
		pauseGame -> Render();
		menu -> Render();
		saved -> Render();
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
	//Render invi cd
	if(invincibleCd >= 0)
	{
		text -> drawText(std::to_string(invincibleCd),150,250,35);
	}
	else if (invincibleCd < 0)
	{
		text -> drawText("READY!",150,250,35);
	}
	//Render fireball + check if collide with character
	for(Fireball* currentFireball : fireballList)
	{
		currentFireball->Render();
		if ((currentFireball->checkCollision(player->getMainCollider(), player->getLeftCollider(), player->getRightCollider())) )
		{	
				if (Iactive)
				{
					saveGame();
					loadSavedGame();
					return;
				}
				else if (!Iactive)
				{
					audio ->playMusic("assets/hit.wav");
					health--;
					if (health <= 0){
						audio -> playMusic("assets/gameOver.wav");
						save -> writeScore(bestScore);
						gameOver = new Background(renderer,"assets/gameOver.png",SCREEN_WIDTH/2 - 300,SCREEN_HEIGHT/2-200);
						SDL_RenderClear(renderer);
						gameOver -> Render();
						SDL_RenderPresent(renderer);
						SDL_Delay(2000);
						newGame();
						bestScore = save -> getMaxScore();
						return;
					}
					else if (health > 0)
					{
						int tempHealth = health;
						int	*nHealth = &health;
						int tempScore = score;
						int *nScore = &score;
						int tempCd = missileCd;
						int *nCd = &missileCd;
						save -> writeScore(bestScore);
						newGame();
						*nHealth = tempHealth;
						*nScore = tempScore;
						*nCd = tempCd;
						bestScore = save -> getMaxScore();
						return;
					}
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
	for (currentFireball = fireballList.begin(); currentFireball != fireballList.end();currentFireball++)
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
				bestScore++ ;
			}
			score++;
			
			//missile cd  = score increment
			missileCd--;
			invincibleCd--;
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
	haveSaved = save -> getHaveSaved();
	if(haveSaved == 1 && loadSaveGame == 1)loadSavedGame();
	else
	{
		newGame();
		haveSaved = 1;
		loadSaveGame = 0;
	}
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

		render();
		
		//Continue game
		if (e.key.keysym.sym == SDLK_c)
		{
			audio -> playMusic("assets/continue.wav");
			pause = false;
		}
		
		//Pause game 
		if (e.key.keysym.sym == SDLK_p) 
		{
			pause = true;
			audio -> playMusic("assets/pause.wav");
			pauseGame = new Menu(renderer,"assets/pause.png");
			menu = new Background(renderer,"assets/menu.png",430,400);
			saved = new Background(renderer, "assets/save.png",510,500);
		}
		
		
		
		//Return to menu when pause
		if (pause)
		{
			Button* toMenu = new Button();
			Button* saveButton = new Button();
			saveButton -> setPosition(510, 500);
			toMenu ->setPosition(430,400);
			if ((toMenu ->handleEvent(&e,200,100) == true) && e.type == SDL_MOUSEBUTTONDOWN)
			{  
				audio -> playMusic("assets/click.wav");
				pause = false;
				runGame = false;
				runHowToPlay = false;
				runChooseChar = false;
				gameMenu();
				if (running()) run();
				if (howToPlayRunning()) howToPlay();
				if (chooseCharRunning()) chooseChar();
				break;
			}
			if ((saveButton -> handleEvent(&e,60,60) == true) && e.type == SDL_MOUSEBUTTONDOWN)
			{
				audio -> playMusic("assets/click.wav");
				saveGame();
			}
		}
		
		//Delay when use missile
		if (explode == true){
			audio -> playMusic("assets/explosionSound.wav");
			SDL_Delay(2000);
		}
		explode = false;
		
		//FPS
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
	std::cout << "game Menu: " << std::endl;
	Mix_VolumeMusic(50);
	music = Mix_LoadMUS("assets/menuMusic.mp3");
	if (music == NULL)
	{
		std::cout <<"Cant load menu music: " <<SDL_GetError()<<std::endl;
	}
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(music, -1);
	}

	startMenu = new Background(renderer, "assets/startMenu.png",0,0);
	
	//Render start menu
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	startMenu -> Render();
	SDL_RenderPresent(renderer);
	
	const Uint8* choose = SDL_GetKeyboardState(NULL);
	while(1)
	{
		if (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				break;
			}
		}
		
		//Play button
		Button* play = new Button();
		play -> setPosition(480, 380);
		if (play ->handleEvent(&e,100,100) && e.type == SDL_MOUSEBUTTONDOWN)
		{
			save -> writeHaveSaved(0);
			audio -> playMusic("assets/click.wav");
			Mix_FadeOutMusic(2000);
			Mix_HaltMusic();
			runGame = true;
			break;
		}
		
		//How to play button
		Button* howPlay = new Button();
		howPlay -> setPosition(320,380);
		if (howPlay -> handleEvent(&e,100,100) && e.type == SDL_MOUSEBUTTONDOWN)
		{
			audio -> playMusic("assets/click.wav");
			runHowToPlay = true;
			howToPlayRunning();
			break; 
		}
		//Choose skin button
		Button* chooseSkin = new Button();
		chooseSkin -> setPosition(10,10);
		if (chooseSkin -> handleEvent(&e,45,45) && e.type == SDL_MOUSEBUTTONDOWN)
		{
			audio -> playMusic("assets/click.wav");
			runChooseChar = true;
			chooseChar();
			break;
		}
		Button* playSavedgame = new Button();
		playSavedgame -> setPosition(645,380);
		int canPlay = save -> getHaveSaved();
		if (playSavedgame -> handleEvent(&e,100,100) && e.type == SDL_MOUSEBUTTONDOWN && canPlay == 1)
		{
			audio -> playMusic("assets/click.wav");
			loadSaveGame = 1;
			runGame = true;
			break;
		}
	}
}
void Game::howToPlay()
{
	std::cout <<"How to play" << std::endl;
	delete text;
	text = new Text(renderer);
	Background* back = new Background(renderer,"assets/back.png",20,20);
	Background* bg = new Background(renderer, "assets/cosmic.jpg",0,0);
	while(1)
	{
		if (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				break;
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);
		
		//Render 
		bg -> Render();
		back -> Render();
		text -> drawText("Dodge the Fireball",350,260,30);
		text -> drawText("Press M to fire the missile",300,310,30);
		text -> drawText("Press I to be Invincible", 350,350,30);
		text -> drawText("Press P to pause",350,390,30);
		text -> drawText("Press C to continue",330,430,30);
		text -> drawText("Press ESC to quit",350,470,30);
		
		SDL_RenderPresent(renderer);
		
		//Return to menu
		Button* returnToMenuButton = new Button();
		returnToMenuButton -> setPosition(20,20);
		if (returnToMenuButton ->handleEvent(&e,210,117) && e.type == SDL_MOUSEBUTTONDOWN)
		{
			audio -> playMusic("assets/click.wav");
			runGame = false;
			runHowToPlay = false;	
			runChooseChar = false;
			gameMenu();
			if (running()) run();
			if (howToPlayRunning()) howToPlay();
			if (chooseCharRunning()) chooseChar();
			break;
		}
	}
}
void Game::chooseChar()
{
	text = new Text(renderer);
	std::cout << "choose Char" << std::endl;
	Background* char1 = new Background(renderer, "assets/player.png",200,300);
	Background* char2 = new Background(renderer, "assets/player2.png",650,300);
	Background* back = new Background(renderer, "assets/back.png",20,20);
	Background* bg = new Background(renderer, "assets/cosmic.jpg",0,0);
	
	while(1)	
	{
		if(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				break;
			}
		}
		
		SDL_SetRenderDrawColor(renderer,0,0,255,255);
		SDL_RenderClear(renderer);
		bg -> Render();
		char1 -> Render();
		char2 -> Render();
		back -> Render();
		
		text -> drawText("Increase Speed",180,560,25);
		text -> drawText("Increase Health",630,560,25);
		SDL_RenderPresent(renderer);
		
		Button* choose1 = new Button();
		Button* choose2 = new Button();
		Button* backButton = new Button();
		backButton -> setPosition(20,20);
		choose1 -> setPosition(200,300);
		choose2 -> setPosition(650,300);
		
		if (choose1 ->handleEvent(&e,200,200) && e.type == SDL_MOUSEBUTTONDOWN)
		{
			audio -> playMusic("assets/click.wav");
			chooseCharacter = 1;
		}
		if (choose2 ->handleEvent(&e,200,200) && e.type == SDL_MOUSEBUTTONDOWN)
		{
			audio -> playMusic("assets/click.wav");
			chooseCharacter = 2;
		}
		if (backButton -> handleEvent(&e,210,117) && e.type == SDL_MOUSEBUTTONDOWN)
		{
			audio -> playMusic("assets/click.wav");
			runGame = false;
			runHowToPlay = false;	
			runChooseChar = false;
			gameMenu();
			if (running()) run();
			if (howToPlayRunning()) howToPlay();
			if (chooseCharRunning()) chooseChar();
			break;
		}
	}
}

void Game::saveGame()
{
	
	std::vector <std::vector <int> > fireballMap;
	int id = 0;
	for(Fireball* currentFireball : fireballList)
	{
		fireballMap.push_back(std::vector <int> ());
		fireballMap[id].push_back(currentFireball -> getX());
		fireballMap[id].push_back(currentFireball -> getY());
		id++;
	}
	save -> writeFireball(fireballMap);
	save -> writePlayer(player -> getX(), player -> getY());
	save -> writeEffect(score,chooseCharacter, health, missileCd, invincibleCd, invincibleTime);
	save -> writeScore(bestScore);
	save -> writeHaveSaved(1);
}
void Game::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	std::cout << "Game cleaned" << std::endl;
}