#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "library.h"

class MenuButton
{
public:
	MenuButton(std::string text, sf::Font & font, int size);
	~MenuButton();
	virtual void setPosition(sf::Vector2f position, bool center = false);
	virtual void setActive();
	virtual void setInactive();
	virtual void update();
	sf::Text getDrawable();
private:
	sf::Text button;
	void centerPosition();
};

