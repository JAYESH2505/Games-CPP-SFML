// Including Game Header File.

#include "Game.h"
#include<time.h>

#include<SFML/Audio.hpp>
int main()
{
	sf::Music Music;
	Music.openFromFile("Music/On.ogg");
	Music.setVolume(50.f);
	Music.play();
	//Intialising Random mod.
	srand(static_cast<unsigned>(time((0))));

	int* Reset = new int(1);
	while (*Reset) {
	    Reset = new int(0);
		Game game;
		game.run(Reset);
	}
		
	
	Music.stop();


	return 0;
}