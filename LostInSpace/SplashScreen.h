#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "State.h"

class SplashScreen : public State //Klasa wyswietlajaca obraz.
{
public:
	SplashScreen(std::string pathToImage, int width, int height, int originalWidth, int originalHeight); //sciezka do obrazu, rozmiary okna, oryginalna - nieskalowana rozdzielczosc
	~SplashScreen();
	void loadResources();
	void eventHandle(sf::RenderWindow & window);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

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