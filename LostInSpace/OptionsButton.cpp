#include "OptionsButton.h"

OptionsButton::OptionsButton(std::string text, std::string valueS, sf::Font & font, int size)
	: MenuButton(text, font, size), value(valueS, font, size)
{
	value.setFillColor(sf::Color::White);
	value.setOrigin(0.0f, 0.0f);
	value.setPosition(sf::Vector2f(0.0f, 0.0f));
	value.setOutlineColor(sf::Color::Red);
	value.setOutlineThickness(0.0f);
}

OptionsButton::~OptionsButton()
{
}

void OptionsButton::setPosition(sf::Vector2f position1, sf::Vector2f position2, bool center) //position1 - pozycja dla klasy bazowej, position2 - pozycja dla value
{
	MenuButton::setPosition(position1, center);
	value.setPosition(position2);
}

void OptionsButton::setActive()
{
	MenuButton::setActive();
	value.setOutlineThickness(10.0f);
}

void OptionsButton::setInactive()
{
	MenuButton::setInactive();
	value.setOutlineThickness(0.0f);
}

void OptionsButton::update(std::string valueS)
{
	value.setString(valueS);
}

void OptionsButton::draw(sf::RenderWindow & window)
{
	MenuButton::draw(window);
	window.draw(value);
}
