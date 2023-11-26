#pragma once

//Library.
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

#include<iostream>


class Battleship
{
private:
	// Player
	sf::Sprite Ship;
	sf::Texture texture;

	float MovementSpeed;
	float cooldown;
	float cooldownmax;
	// Private function
	void inittexture();
	void initspirite();

	//Variable.
	int hp;
	int hpmax;

public:
	// Constructor and Destructor
	Battleship();
	~Battleship();

	void initvariable();

	//Update and render
	void update();
	void updateattack();
	void Render(sf::RenderTarget& target);


	//Function
	void move(const float dirx, const float diry);
	const bool canattack();

	// Accesor

	const sf::Vector2f& getpos() const;
	sf::FloatRect getBound() const;
	const int& gethp() const;
	const int& gethpmax() const;


	//modify
	void setposition(const float x, const float y);
	void sethp(int hp);
	void looshp(const int value);

	void initgui();
};

