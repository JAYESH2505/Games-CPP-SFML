#include "Bullet.h"



// Constructor and Destructor
Bullet::Bullet(sf::Texture* texture, float posx, float posy, float dirx, float diry, float Movementspeed)
{
	this->bullet.setTexture(*texture);
	
	this->direction.x = dirx;
	this->direction.y = diry;
	this->Movementspeed = Movementspeed;
	this->bullet.setPosition(posx, posy);
	this->bullet.setScale(0.1f, 0.1f);
}

Bullet::~Bullet()
{

}




//Update and render
void Bullet::update()
{
	// Movement
	this->bullet.move(this->Movementspeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->bullet);
}


const sf::FloatRect Bullet::getbound() const
{
	return this->bullet.getGlobalBounds();
}