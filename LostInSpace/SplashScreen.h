#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "State.h"

class SplashScreen : public State //Klasa wyswietlajaca obraz.
{
public:
	SplashScreen(std::string pathToImage, int width, int height); //sciezka do obrazu, rozmiary okna
	~SplashScreen();
	virtual void loadResources() override;
	virtual void eventHandle(sf::RenderWindow & window) override;
	virtual void update(float deltaTime, sf::RenderWindow & window) override;
	virtual void draw(sf::RenderWindow& window) override;

private:
	std::string pathToImage; //sciezka do wzglednej lokalizacji obrazu
	sf::Sprite image;
	sf::RectangleShape square;
	sf::Texture texture;
	sf::Event event;
	sf::View view;
	int alpha;
	int a;
};