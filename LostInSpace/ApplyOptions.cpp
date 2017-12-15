#include "ApplyOptions.h"

ApplyOptions::ApplyOptions(float & fxVolume, float & musicVolume, bool & isFullScreen, int & width, int & height)
{
	this->fxVolume = &fxVolume;
	this->musicVolume = &musicVolume;
	this->isFullScreen = &isFullScreen;
	this->width = &width;
	this->height = &height;
}

ApplyOptions::~ApplyOptions()
{
}

void ApplyOptions::loadResources()
{
	std::fstream config;
	config.open("config", std::ios::in); //otworz do odczytu
	if (config.good())
	{
		config >> *musicVolume; //glosnosc muzyki
		config >> *fxVolume; //glosnosc efektow
		config >> *isFullScreen; //czy aktywny jest tryb pelnoekranowy
		config >> windowResolution; //rozmiar okna - wartosc odnosi sie do elementu tablicy resolutions
		config.close();
	}
	*width = resolutions[windowResolution].x;
	*height = resolutions[windowResolution].y;
}

void ApplyOptions::eventHandle(sf::RenderWindow & window)
{
	if (*isFullScreen == true)
	{
		window.create(sf::VideoMode(*width, *height), "Lost in Space", (sf::Style::Fullscreen));
	}
	else
	{
		window.create(sf::VideoMode(*width, *height), "Lost in Space", (sf::Style::Close));
	}
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
}

void ApplyOptions::update(float deltaTime, sf::RenderWindow & window)
{
	newState = sn::MenuState;
}

void ApplyOptions::draw(sf::RenderWindow & window)
{
}
