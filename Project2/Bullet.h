#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
// Library.
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>

//Main Libray.
#include<iostream>

class Bullet
{
private:
	// Variable
	sf::Sprite bullet;
	sf::Texture* texture;

	sf::Vector2f direction;
	float Movementspeed;
public:
	// Constructor and Destructor
	
	Bullet(sf::Texture* texture,float posx,float posy, float dirx, float diry, float Movementspeed);;
	~Bullet();

	// Accesror
	const sf::FloatRect getbound() const;

	//Update and render
	void update();
	void render(sf::RenderTarget* target);
};

