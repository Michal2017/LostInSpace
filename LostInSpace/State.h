#pragma once

#include <SFML/Graphics.hpp>

#include "library.h"

class State //Klasa bazowa dla wszystkich stanow gry.
{
public:
	virtual void loadResources() = 0;
	virtual void eventHandle(sf::RenderWindow & window) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow & window) = 0;
	sn::GameState changeTo() { return newState; }

protected:
	int width;
	int height;
	sn::GameState newState = sn::None;
	sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
};