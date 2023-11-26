#include "Battleship.h"

// Initialiser function
void Battleship::inittexture()
{
	//Load texture from file
	if (this->texture.loadFromFile("Texture/Ship1.png"))
		std::cout << "!ERROR Cant LOAD";
}

void Battleship::initspirite()
{
	// Set the texture
	this->Ship.setTexture(this->texture);
	this->Ship.setScale(0.3f, 0.3f);


}

void Battleship::initvariable()
{
	this->MovementSpeed = 3.f;
	this->cooldownmax = 50.f;
	this->cooldown = this->cooldownmax;
	this->hpmax = 10;
	this->hp = this->hpmax;
}




// Constructor and Destructor
Battleship::Battleship()
{
	this->initvariable();
	this->inittexture();
	this->initspirite();
}

Battleship::~Battleship()
{
	
}



//Update and render
void Battleship::update()
{
	this->updateattack();
}

void Battleship::updateattack()
{
	if(this->cooldown<this->cooldownmax)
	this->cooldown += 1.f;
}

void Battleship::Render(sf::RenderTarget& target)
{
	target.draw(this->Ship);
}






// Function
void Battleship::move(const float dirx, const float diry)
{
	this->Ship.move(this->MovementSpeed * dirx, this->MovementSpeed * diry);

}

const bool Battleship::canattack()
{
	if (this->cooldown >= this->cooldownmax)
	{
		this->cooldown = 0.f;
		return true;
	}
	return false;
}

const sf::Vector2f& Battleship::getpos() const
{
	// TODO: insert return statement here
	return this->Ship.getPosition();
}

sf::FloatRect Battleship::getBound() const
{
	return this->Ship.getGlobalBounds();
}

const int& Battleship::gethp() const
{
	// TODO: insert return statement here
	return this->hp;
}

const int& Battleship::gethpmax() const
{
	// TODO: insert return statement here
	return this->hpmax;
}

void Battleship::setposition(const float x, const float y)
{
	Ship.setPosition(x, y);
}

void Battleship::sethp(int hp)
{
	this->hp = hp;
}

void Battleship::looshp(const int value)
{

	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Battleship::initgui()
{
}


