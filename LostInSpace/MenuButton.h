#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "IButton.h"

class MenuButton : public IButton
{
public:
	MenuButton(std::string text, sf::Font & font, int size);
	~MenuButton();
	virtual void setPosition(sf::Vector2f position, bool center = false) override;
	virtual void setActive() override;
	virtual void setInactive() override;
	virtual sf::Text getDrawable() override { return button; } //zwraca obiekt nadajacy sie do narysowania
private:
	sf::Text button;
	void centerPosition();
};