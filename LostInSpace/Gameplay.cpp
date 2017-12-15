#include "Gameplay.h"

Gameplay::Gameplay(sf::Font & font, float fxVolume, float musicVolume, int width, int height)
	: score(font)
{
	this->font = font;
	this->fxVolume = fxVolume;
	this->musicVolume = musicVolume;
	this->width = width;
	this->height = height;
}

Gameplay::~Gameplay()
{
}

void Gameplay::loadResources()
{
	//widoki
	view.setSize(originalWidth, originalHeight);
	view = getLetterboxView(view, width, height);
	hud.setSize(originalWidth, originalHeight);
	hud.setCenter(hud.getSize().x / 2, hud.getSize().y / 2);
	hud = getLetterboxView(hud, width, height);
	mouseView.setSize(width, height);
	mouseView.setCenter(mouseView.getSize().x / 2, mouseView.getSize().y / 2);
	/********************************************/

	//tekstury
	playerTexture.loadFromFile("textures/player_texture.png");
	playerTexture.setSmooth(true);
	engineTexture.loadFromFile("textures/engine_exhaust.png");
	engineTexture.setSmooth(true);
	backgroundTexture.loadFromFile("background/game_background.png");
	background.setPosition(0.0f, 0.0f);
	greenProjectileTexture.loadFromFile("textures/green_projectile.png");
	redProjectileTexture.loadFromFile("textures/red_projectile.png");
	aimTexture.loadFromFile("textures/aim.png");
	/********************************************/

	//obiekty
	background.setTexture(backgroundTexture);
	player = Player(&playerTexture, &engineTexture);
	myMouse.setTexture(aimTexture);
	/********************************************/
}

void Gameplay::eventHandle(sf::RenderWindow & window)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Gameplay::update(float deltaTime, sf::RenderWindow & window)
{
	if (!isPaused) //jezeli gra nie jest w trybie pauzy
	{
		myMouse.setPosition((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y); //uaktualnienie kursora

		window.setView(view);
		player.update(deltaTime, window, &greenProjectileTexture);

		view.setCenter(player.getPosition()); //ustawienie kamary na statku gracza
	}
	else // jezeli gra jest w trybie pauzy
	{

	}
}

void Gameplay::draw(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);

	window.setView(hud); //tlo
	window.draw(background);

	window.setView(view); //obiekty
	player.draw(window);

	window.setView(mouseView); //mysz
	window.draw(myMouse);

	window.setView(hud); //interfejs
	window.draw(score.getDrawable());

	window.display();
}
