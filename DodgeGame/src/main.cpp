#include "game.h"

int main(int argc, char* argv[])
{
	const int WINDOW_WIDTH = 1080;
	const int WINDOW_HEIGHT = 720;

	Uint32 frameStart;
	int frameTime;
	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;

	Game* game = new Game();
	
	
		if (game -> init())
		{
			game -> run();
		}
	
	game->clean();
	return 0;
}
