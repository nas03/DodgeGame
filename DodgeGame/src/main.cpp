#include "game.h"

int main(int argc, char* argv[])
{
	Game* game = new Game();
		if (game -> init())
		{
			game -> gameMenu();
			if (game ->running() == true) game -> run();
			else if (game ->howToPlayRunning() == true) game -> howToPlay();
		}
	return 0;
}
