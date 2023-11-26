#pragma once

//Including Other Header Files.
#include "Battleship.h"
#include "Bullet.h"
#include"Enemy.h"

// Sfml.
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

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

	//Points
	unsigned points;

public:

	// Intializer
	Game();
	~Game();

	//Extra
	void initsystem();

	// Basic Function
	void run();
	void Pollevent();



	//Initialiser
	void inittexture();
	void initenemies();

	//Update
	void update();
	void ShipMovement();
	void updatebullets();
	void updateenemy();
	void updateplayer();

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
};

