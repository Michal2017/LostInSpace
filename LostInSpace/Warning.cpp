#include "Warning.h"

Warning::Warning(int windowWidth, sf::Font & font, float textHeight, std::string textString, unsigned int fontSize)
	:text(textString, font, fontSize)
{
	text.setFillColor(sf::Color::Yellow);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(5.f);
	sf::FloatRect *textRect = new sf::FloatRect;
	*textRect = text.getLocalBounds();
	text.setOrigin(textRect->left + textRect->width / 2.0f, textRect->top + textRect->height / 2.0f);
	text.setPosition(sf::Vector2f(windowWidth / 2.0f, textHeight));
	delete textRect;
	isVisable = false;
	green = 255;
	animationFlag = 1;
}

Warning::~Warning()
{
}

void Warning::update(float deltaTime, sf::Vector2f spaceshipPosition, sf::Vector2f areaSize)
{
	if (spaceshipPosition.x < 0.f || spaceshipPosition.x > areaSize.x || spaceshipPosition.y < 0.f || spaceshipPosition.y > areaSize.y)
	{
		isVisable = true;
		animate(deltaTime);
	}
	else isVisable = false;
}

void Warning::draw(sf::RenderWindow & window)
{
	if (isVisable)
		window.draw(text);
}

void Warning::animate(float deltaTime)
{
	if (animationFlag)
		green -= (int)(deltaTime * 100);
	else green += (int)(deltaTime * 100);
	if (green > 255)
	{
		green = 255;
		animationFlag = 1;
	}
	else if (green < 0)
	{
		green = 0;
		animationFlag = 0;
	}
	text.setFillColor(sf::Color(255, green, 0));
}
