#include "game.h"

int main(int argc, char* argv[])
{
	Game* game = new Game();
		if (game -> init())
		{
			game -> run();
		}
	return 0;
}
