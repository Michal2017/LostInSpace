#include "OptionsButton.h"

OptionsButton::OptionsButton(std::string value, sf::Font & font, int size)
	: button(value, font, size)
{
	button.setFillColor(sf::Color::White);
	button.setOrigin(0.0f, 0.0f);
	button.setPosition(sf::Vector2f(0.0f, 0.0f));
	button.setOutlineColor(sf::Color::Red);
	button.setOutlineThickness(0.0f);
}

OptionsButton::~OptionsButton()
{
}

void OptionsButton::setPosition(sf::Vector2f position, bool center)
{
	button.setPosition(position);
}

void OptionsButton::setActive()
{
	button.setOutlineThickness(10.0f);
}

void OptionsButton::setInactive()
{
	button.setOutlineThickness(0.0f);
}

void OptionsButton::updateValue(std::string newString)
{
	button.setString(newString);
}
