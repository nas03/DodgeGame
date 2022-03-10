#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int cnt = 0;
	bool isRunning = true;

public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullScr);
	void handleEvents();
	void clean();
	void update();
	void render();
	bool running() { return isRunning;}
};