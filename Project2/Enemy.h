#pragma once

//Library.
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>

#include<iostream>


class Enemy
{
private:
	//Variable.
	//sf::CircleShape shape;

	sf::Sprite shape;
	sf::Texture txt;

	int type;
	
	int damage;
	int points;
	float speed;
	unsigned pointcount;

	//Initialiser
	void initshape();
	void initvariable();

public:
	Enemy(float posx,float posy);
	~Enemy();

	//Update and Render
	void update();
	void render(sf::RenderTarget* target);


	// Accesor
	sf::FloatRect getbound() const;
	const int& getpoint() const;
};

