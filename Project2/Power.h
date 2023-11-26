#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
// Library.
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>

//Main Libray.
#include<iostream>


class Power
{
private:
	sf::Sprite PowerUp;
	sf::Texture txt;
public:
	//Constructor and Destructor.
	Power(sf::RenderWindow* t);
	~Power();


	//Initialiser
	void initvariable(sf::RenderWindow* t);

	//Update and render
	void update();
	void render(sf::RenderTarget* window);


	//Move
	void move();


	//Accesor
	sf::FloatRect getbound();
};

