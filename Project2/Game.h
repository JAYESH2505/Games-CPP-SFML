#pragma once

//Including Other Header Files.
#include "Battleship.h"
#include "Bullet.h"
#include"Enemy.h"
#include "Power.h"

// Sfml.
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>

//Basic C++.
#include<map>
#include<sstream>
#include<iostream>
#include<vector>



class Game
{
private:
	sf::RenderWindow* Window;
	Battleship* Ship;
	std::vector<Power*>PUP;

	//Initialiser.
	void initwindow();
	void initPlayer();

	// Resource 
	std::map<std::string, sf::Texture*>texture;


	//Enemies and Bullets.
	std::vector<Enemy*> E;
	std::vector<Bullet*> B;

	//Enemy Criteria;

	float spawntimer;
	float spawntimermax;

	//PowerUp Criteria
	float time;
	float timemax;

	//Points
	unsigned points;

	//Pause Menu
	sf::Texture pau;
	sf::Sprite pauseScreen;
	bool Pause;

	//Song
	sf::SoundBuffer Bf;
	sf::Sound Sound;
	sf::SoundBuffer Ex;
	sf::Sound Explosion;

	//Start
	bool start;
	sf::Texture st;
	sf::Sprite StartScreen;

	//Choice
	int choice;
	sf::Texture ch;
	sf::Sprite ChoiceScreen;

	//Mouse
	bool MouseClicked;
	sf::Vector2i MousePosWindow;
	sf::Vector2f MousePosView;

	
public:

	// Intializer
	Game();
	~Game();

	//Extra
	void initsystem();

	// Basic Function
	void run(int * Reset);
	void Pollevent(int* Reset);



	//Initialiser
	void inittexture();
	void initenemies();

	//Update
	void update();
	void ShipMovement();
	void updatebullets();
	void updateenemy();
	void updateplayer();
	void updatePowerup();
	void updateCursor();
	void updateMouse();

	//Render
	void render();


	//Gui
	sf::Font font;
	sf::Text text;
	sf::Text Gameover;
	sf::RectangleShape Hpbar;
	sf::RectangleShape Hpbarback;
	void initgui();
	void updategui();
	void rendergui();
	void playergui();

	//World
	sf::Texture Back;
	sf::Sprite Background;
	void renderworld();

	//Others.
	void combat();
	void IncreaseHp();
	void Bulletsound();
	void Explosionsound();
};

