#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Warning
{
public:
	Warning(int windowWidth, sf::Font &font, float textHeight, std::string textString, unsigned int fontSize);
	~Warning();
	void update(float deltaTime, sf::Vector2f spaceshipPosition, sf::Vector2f areaSize);
	void draw(sf::RenderWindow &window);

private:
	sf::Vector2f position;
	sf::Text text;
	bool isVisable;
	void animate(float deltaTime);
	int green;
	bool animationFlag;
};