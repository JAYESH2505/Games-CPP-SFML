//Library.
#include "Game.h"
#include "Battleship.h"
#include "Enemy.h"

// Intialise item
void Game::initwindow()
{
	this->Window = new sf::RenderWindow(sf::VideoMode(1600,900), "Space Game", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize | sf::Style::Fullscreen );
	this->Window->setFramerateLimit(144);
	this->Window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	
	this->Ship = new Battleship();
	this->Ship->setposition(50.f, 50.f);

}


void Game::inittexture()
{
	this->texture["Bullets"] = new sf::Texture();
	this->texture["Bullets"]->loadFromFile("Texture/bullet.jpg");

	if (this->Back.loadFromFile("Texture/Space_Background$k.jpg"))
		std::cout << "Cant Back" << std::endl;
	this->Background.setTexture(Back);
	this->Background.setScale(.9f, .8f);
	//this->Background.setPosition(this->Window->getSize().x/2.f, this->Window->getSize().y / 2.f);
	
	this->pau.loadFromFile("Texture/Pause.gif");
	this->pauseScreen.setTexture(this->pau);
	this->pauseScreen.setScale(1.f, 1.f);

	this->st.loadFromFile("Texture/Loading.jpg");
	this->StartScreen.setTexture(this->st);
	this->StartScreen.setScale(3.8f, 4.8f);
	this->StartScreen.setPosition(0.f, 0.f);

	this->ch.loadFromFile("Texture/Choice.jpg");
	this->ChoiceScreen.setTexture(this->ch);


	//Sound
	this->Bf.loadFromFile("Music/Bullet.wav");
	this->Sound.setBuffer(this->Bf);

	this->Ex.loadFromFile("Music/Explo.wav");
	this->Explosion.setBuffer(this->Ex);
	
}

void Game::initenemies()
{
	this->spawntimermax = 50.f;
	this->spawntimer = this->spawntimermax;

	//Powerup
	this->timemax = 1000.f;
	this->time = this->timemax;

	//Pause
	this->Pause = false;

	//Start 
	this->start = true;

	//Choice
	this->choice = 0;

	//Mouse
	this->MouseClicked = false;

	

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
void Game::run(int* Reset)
{
	while (this->Window->isOpen())
	{
		if (*Reset == 1)
			return;
		this->Pollevent(Reset);
		if (this->Pause)
		{
			this->render();
		}
		else if (this->start)
		{
			this->render();
		}
		else if (this->choice == 0)
		{
			this->render();
		}
		else {
			if (this->Ship->gethp() > 0) {
				this->update();
			}
			this->render();
		}
	}
}


void Game::Pollevent(int* Reset)
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
			if (sf::Keyboard::Escape == E.key.code)
				this->Window->close();
			else if (sf::Keyboard::Space == E.key.code)
				this->Pause = !this->Pause;
			else if (sf::Keyboard::Enter == E.key.code)
				this->start = false;
			else if (sf::Keyboard::Num1 == E.key.code)
				this->choice = 1;
			else if (sf::Keyboard::Num2 == E.key.code)
				this->choice = 2;
			else if (sf::Keyboard::Tab == E.key.code)
				*Reset = 1;
				
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


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->Ship->canattack()) {
		this->B.push_back(new Bullet(this->texture["Bullets"],this->Ship->getpos().x+this->Ship->getBound().width/2.f, this->Ship->getpos().y, 0.f, -1.f, 5.f));
		this->Bulletsound();
	}
		
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
				this->Explosionsound();
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
			this->Explosionsound();
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

void Game::updatePowerup()
{
	this->time = this->time + 1.f;
	if (this->time > this->timemax)
	{
		this->time = 0.f;
		PUP.push_back(new Power(Window));
	}

	for (auto* i : PUP)
	{
		i->move();
	}	
	for (int i = 0;i < PUP.size();i++)
	{
		bool consume = false;

			if (PUP[i]->getbound().intersects(Ship->getBound()))
			{
				delete PUP[i];
				PUP.erase(PUP.begin() + i);
				consume = true;
				this->IncreaseHp();
			}
		
		if (consume==false && PUP[i]->getbound().top>this->Window->getSize().y)
		{
			
			delete PUP[i];
			PUP.erase(PUP.begin() + i);
		}
	}

}

void Game::updateCursor()
{
	this->spawntimer += 0.5f;
	if (this->spawntimer >= this->spawntimermax)
	{
		this->E.push_back(new Enemy(rand() % this->Window->getSize().x - 50.f, -100.f));
		this->spawntimer = 0.f;
	}
	
	for (int i = 0;i < this->E.size();i++) {
		E[i]->update();
		if (E[i]->getbound().top > this->Window->getSize().y)
		{
			this->Ship->looshp(1);
			this->Explosionsound();
			delete E[i];
			E.erase(E.begin() + i);
			
		}
		
	}
	this->updateMouse();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->MouseClicked == false)
		{
			this->MouseClicked = true;
			bool deleted = false;

			for (int i = 0;i < this->E.size() && deleted == false;i++)
			{

				if (E[i]->getbound().contains(this->MousePosView))
				{

					//Delete enemies
					this->points += this->E[i]->getpoint();
					delete E[i];
					E.erase(E.begin() + i);
					
					deleted = true;
				}

			}
		}
		

	}
	else
	{
		this->MouseClicked = false;
	}
}

void Game::updateMouse()
{
	this->MousePosWindow = sf::Mouse::getPosition(*this->Window);
	this->MousePosView = this->Window->mapPixelToCoords(this->MousePosWindow);
}

void Game::updategui()
{
	std::stringstream ss,gg;
	ss << "Point : " << points;
	gg<<"Point : " << points;
	this->text.setString(ss.str());

	
	float hpper = static_cast<float>(this->Ship->gethp()) / this->Ship->gethpmax();
	this->Hpbar.setSize(sf::Vector2f(300.f*hpper, this->Hpbar.getSize().y));
	
	this->Gameover.setString(gg.str());
	Gameover.setPosition((this->Window->getSize().x - this->Gameover.getGlobalBounds().width) / 2.f, this->Window->getSize().y / 2.f);
}





// Update and Render
void Game::update()
{
	if (choice == 1)
	{
		this->ShipMovement();
		this->Ship->update();
		this->updatebullets();
		this->updateplayer();
		this->updateenemy();
		
	}
	if (choice == 2)
	{
		this->updateCursor();
	}
	this->updatePowerup();
	this->updategui();
	
	
}


void Game::render()
{
	this->Window->clear();
	if (this->start)
	{
		Window->draw(this->StartScreen);
	}
	else if (choice == 0)
	{
		Window->draw(this->ChoiceScreen);
	}
	else {
	// Draw all the stuf
	if (this->Ship->gethp() <= 0) {
		Back.loadFromFile("Texture/GameOver4.png");
		Background.setTexture(Back);
		Background.setPosition(350.f, 0.f);
		Background.setScale(1.5, 1.5f);
		this->renderworld();
		//this->Window->draw(this->Gameover);
	}
	else {
	this->renderworld();
	Ship->Render(*this->Window);
	for (auto* i : this->PUP)
	{
		i->render(Window);
	}
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
	if (this->Pause)
	{
		Window->draw(this->pauseScreen);
	}

	}
	this->Window->display();
}



//Extra

void Game::IncreaseHp()
{
	if (this->Ship->gethp() < this->Ship->gethpmax())
	{
		int n = this->Ship->gethp();
		n = n+1;
		this->Ship->sethp(n);
	}
}
void Game::Bulletsound()
{
	Sound.play();
	Sound.setPlayingOffset(sf::seconds(2.f));
	
}
void Game::Explosionsound()
{
	Explosion.play();
}
void Game::playergui()
{

}
void Game::combat()
{
}


