#include "MenuButton.h"

MenuButton::MenuButton(std::string text, sf::Font & font, int size)
	: button(text, font, size)
{
		button.setFillColor(sf::Color::White);
		button.setPosition(sf::Vector2f(0.0f, 0.0f));
		button.setOutlineColor(sf::Color::Red);
		button.setOutlineThickness(0.0f);
}

MenuButton::~MenuButton()
{
}

void MenuButton::setPosition(sf::Vector2f position, bool center)
{
	button.setPosition(position);
	if (center)
	{
		centerPosition();
	}
}

void MenuButton::setActive()
{
	button.setOutlineThickness(10.0f);
}

void MenuButton::setInactive()
{
	button.setOutlineThickness(0.0f);
}

void MenuButton::update()
{
}

sf::Text MenuButton::getDrawable()
{
	return button;
}

void MenuButton::centerPosition()
{
	sf::FloatRect textRect = button.getLocalBounds();
	button.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	button.setPosition(sf::Vector2f(originalWidth / 2.0f, button.getPosition().y));
}
