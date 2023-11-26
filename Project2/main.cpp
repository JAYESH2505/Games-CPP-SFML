// Including Game Header File.

#include "Game.h"
#include<time.h>

int main()
{
	//Intialising Random mod.
	srand(static_cast<unsigned>(time((0))));
	
	Game game;

	game.run();
}