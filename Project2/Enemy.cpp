#include "Enemy.h"

//Initialiser.
void Enemy::initshape()
{
	switch (type)
	{
	case 1:
		this->txt.loadFromFile("Texture/Meteor.png");
		this->shape.setTexture(this->txt);
		break;
	case 2:
		this->txt.loadFromFile("Texture/Asteroid.png");
		this->shape.setTexture(this->txt);
		this->shape.setScale(.2f, .2f);
		break;
	case 3:
		this->txt.loadFromFile("Texture/Moon.png");
		this->shape.setTexture(this->txt);
		this->shape.setScale(.2f, .2f);
		break;
	}

}

void Enemy::initvariable()
{
	this->type = rand()%3+1;
	this->pointcount = this->type*5;
	
	this->damage = this->pointcount;
	this->points = this->pointcount;
	this->speed = 1;
	
}



//Constructor and Destructor.
Enemy::Enemy(float posx,float posy)
{
	this->shape.setPosition(posx, posy);
	this->initvariable();
	this->initshape();
}

Enemy::~Enemy()
{

}

//Update and Render.
void Enemy::update()
{
	shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}


//Accessor.
sf::FloatRect Enemy::getbound() const
{
	return shape.getGlobalBounds();
}

const int& Enemy::getpoint() const
{
	// TODO: insert return
	//  statement here
	return this->points;
}
