#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "library.h"

class MenuButton
{
public:
	MenuButton(std::string text, sf::Font & font, int size);
	~MenuButton();
	void setPosition(sf::Vector2f position, bool center = false);
	virtual void setPosition(sf::Vector2f position1, sf::Vector2f position2, bool center = false);
	virtual void setActive();
	virtual void setInactive();
	virtual void update();
	virtual void draw(sf::RenderWindow & window); //rysuje obiekt
private:
	sf::Text button;
	void centerPosition();
};

