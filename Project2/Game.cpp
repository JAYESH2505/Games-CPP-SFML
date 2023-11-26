//Library.
#include "Game.h"
#include "Battleship.h"
#include "Enemy.h"

// Intialise item
void Game::initwindow()
{
	this->Window = new sf::RenderWindow(sf::VideoMode(1600,900), "Space Game", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize | sf::Style::Fullscreen);
	this->Window->setFramerateLimit(144);
	this->Window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	
	this->Ship = new Battleship();
}

//!!!!

void Game::inittexture()
{
	this->texture["Bullets"] = new sf::Texture();
	this->texture["Bullets"]->loadFromFile("Texture/bullet.jpg");

	if (this->Back.loadFromFile("Texture/Space_Background$k.jpg"))
		std::cout << "Cant Back" << std::endl;
	this->Background.setTexture(Back);
	this->Background.setScale(.9f, .8f);
	//this->Background.setPosition(this->Window->getSize().x/2.f, this->Window->getSize().y / 2.f);
	
}

void Game::initenemies()
{
	this->spawntimermax = 50.f;
	this->spawntimer = this->spawntimermax;
}

void Game::initgui()
{
	font.loadFromFile("Fonts/COOPBL.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(24);
	text.setString("Test");
	text.setPosition(this->Window->getSize().x - 100.f - text.getGlobalBounds().width, 25.f);

	Gameover.setFont(font);
	Gameover.setFillColor(sf::Color::Red);
	Gameover.setCharacterSize(100);
	Gameover.setString("Gameover");
	Gameover.setPosition((this->Window->getSize().x - this->Gameover.getGlobalBounds().width) / 2.f, this->Window->getSize().y / 2.f);

	// Player gui
	this->Hpbar.setSize(sf::Vector2f(300.f, 25.f));
	this->Hpbar.setFillColor(sf::Color::Red);
	this->Hpbar.setPosition(sf::Vector2f(20.f, 20.f));

	this->Hpbarback.setSize(sf::Vector2f(300.f, 25.f));
	this->Hpbarback.setFillColor(sf::Color(10, 10, 10, 200));
	this->Hpbarback.setPosition(sf::Vector2f(20.f, 20.f));
}


//Intializer
Game::Game()
{
	this->initwindow();
	this->initPlayer();
	this->inittexture();
	this->initenemies();

	this->initgui();
	initsystem();
}

Game::~Game()
{
	delete this->Window;
	delete this->Ship;

	//Delet texture
	for (auto& i : this->texture)
	{
		delete i.second;
	}
	for (auto& i : B)
	{
		delete i;
	}
	for (auto* i : E)
	{
		delete i;
	}
}

//Points
void Game::initsystem()
{
	points = 0;
}




//Function
void Game::run()
{
	while (this->Window->isOpen() )
	{
		this->Pollevent();
		if(this->Ship->gethp()>0)
			this->update();
		this->render();
	}
}


void Game::Pollevent()
{
	sf::Event E;
	while (this->Window->pollEvent(E))
	{
		switch (E.Event::type)
		{
		case sf::Event::Closed:
			this->Window->close();
			break;
		case sf::Event::KeyPressed:
			if(sf::Keyboard::Escape==E.key.code)
				this->Window->close();
		}
	}
}


//Render
void Game::rendergui()
{
	this->Window->draw(text);
	this->Window->draw(this->Hpbarback);
	this->Window->draw(this->Hpbar);
}

void Game::renderworld()
{
	this->Window->draw(Background);
}



//Update
void Game::ShipMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->Ship->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->Ship->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->Ship->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->Ship->move(0.f, 1.f);

	// Move Player


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && this->Ship->canattack())
		this->B.push_back(new Bullet(this->texture["Bullets"],this->Ship->getpos().x+this->Ship->getBound().width/2.f, this->Ship->getpos().y, 0.f, -1.f, 5.f));
}

void Game::updatebullets()
{
	unsigned counter = 0;
	for (auto* i : this->B)
	{
		i->update();
		// bullet going above screeen
		if (i->getbound().top + i->getbound().height < 0.f)
		{
			delete this->B.at(counter);
			this->B.erase(this->B.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game::updateenemy()
{
	this->spawntimer += 0.5f;
	if (this->spawntimer >= this->spawntimermax)
	{
		this->E.push_back(new Enemy(rand()%this->Window->getSize().x-50.f,-100.f));
		this->spawntimer = 0.f;
	}
	for (int i=0;i<E.size();i++)
	{
		bool enemiesr = false;
		E[i]->update();
		for (int j = 0;j < this->B.size() && enemiesr==false;j++)
		{

			if (this->B[j]->getbound().intersects(this->E[i]->getbound()))
			{
				this->points += this->E[i]->getpoint();
				delete E[i];
				delete B[j];
				E.erase(E.begin() + i);
				B.erase(B.begin() + j);
				enemiesr = true;
			}
		}
		if (enemiesr==false && E[i]->getbound().top>this->Window->getSize().y)
		{
			this->Ship->looshp(1);
			delete E[i];
			E.erase(E.begin() + i);
			std::cout << E.size() << std::endl;
		}
	}
}

void Game::updateplayer()
{
	if (this->Ship->getBound().left < 0.f)
	{
		this->Ship->setposition(0.f, Ship->getBound().top);
	}
	if (this->Ship->getBound().top < 0.f)
	{
		this->Ship->setposition(Ship->getBound().left, 0.f);
	}
	if (this->Ship->getBound().left + Ship->getBound().width >= Window->getSize().x)
	{
		this->Ship->setposition(this->Window->getSize().x - Ship->getBound().width, Ship->getBound().top);
	}
	if (this->Ship->getBound().top + this->Ship->getBound().height >= Window->getSize().y)
	{
		this->Ship->setposition(this->Ship->getBound().left, Window->getSize().y - Ship->getBound().height);
	}
}


void Game::updategui()
{
	std::stringstream ss,gg;
	ss << "Point : " << points;
	gg<<"GAME OVER"<<std::endl<< "  Point : " << points;
	this->text.setString(ss.str());

	
	float hpper = static_cast<float>(this->Ship->gethp()) / this->Ship->gethpmax();
	this->Hpbar.setSize(sf::Vector2f(300.f*hpper, this->Hpbar.getSize().y));
	
	this->Gameover.setString(gg.str());
	Gameover.setPosition((this->Window->getSize().x - this->Gameover.getGlobalBounds().width) / 2.f, this->Window->getSize().y / 2.f);
}





// Update and Render
void Game::update()
{
	this->ShipMovement();
	this->Ship->update();
	this->updateplayer();
	this->updatebullets();

	this->updateenemy();
	this->updategui();
}


void Game::render()
{
	this->Window->clear();
	this->renderworld();
	// Draw all the stuf
	if (this->Ship->gethp() <= 0)
		this->Window->draw(this->Gameover);
	else {

	Ship->Render(*this->Window);
	for (auto* i : this->B)
	{
		i->render(this->Window);
	}
	for (auto *i : this->E)
	{
		i->render(this->Window);
	}
	this->rendergui();
	//this->enemies->render(this->Window);

	// Gameover
	}
	this->Window->display();
}


//Extra
void Game::playergui()
{

}
void Game::combat()
{
}
