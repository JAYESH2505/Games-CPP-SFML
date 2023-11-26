#include "Power.h"


//Constructor and Destructor
Power::Power(sf::RenderWindow* t)
{
	this->initvariable(t);
}

Power::~Power()
{
}



//Initialiser.
void Power::initvariable(sf::RenderWindow* t)
{
	this->txt.loadFromFile("Texture/Pup.png");
	this->PowerUp.setTexture(this->txt);
	
	this->PowerUp.setPosition(rand() % t->getSize().x - 50.f, -100.f);
}



//Update and render
void Power::update()
{

}

void Power::render(sf::RenderTarget* window)
{
	window->draw(this->PowerUp);
}


//Function
void Power::move()
{
	PowerUp.move(0.f, 1.f);
}



//Accessor.
sf::FloatRect Power::getbound()
{
	return PowerUp.getGlobalBounds();
}
