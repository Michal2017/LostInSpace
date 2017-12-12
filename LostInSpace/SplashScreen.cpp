#include "SplashScreen.h"

SplashScreen::SplashScreen(std::string pathToImage, int width, int height, int originalWidth, int originalHeight)
{
	this->pathToImage = pathToImage;
	this->width = width;
	this->height = height;
	this->originalWidth = originalWidth;
	this->originalHeight = originalHeight;
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::loadResources()
{
	texture.loadFromFile(pathToImage);
	image.setTexture(texture);
	image.setPosition(0.f, 0.f);
	square.setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
	square.setFillColor(sf::Color(0, 0, 0, 255));
	square.setPosition(0.f, 0.f);
	alpha = 254;
	a = -1;
	view.setSize(originalWidth, originalHeight);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	view = getLetterboxView(view, width, height);
}

void SplashScreen::eventHandle(sf::RenderWindow & window)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void SplashScreen::update(float deltaTime)
{
	if (alpha >= 255) //po zakonczeniu animowania
	{
		newState = sn::MenuState; //przejdz do nowego stanu
	}
	else //animuj
	{
		alpha = alpha + a * 100 * deltaTime;
		if (alpha < 0)
		{
			a = 1;
			alpha = 0;
		}
		square.setFillColor(sf::Color(0, 0, 0, alpha));
	}
}

void SplashScreen::draw(sf::RenderWindow & window)
{
	window.setView(view);
	window.draw(image);
	window.draw(square);
	window.display();
}