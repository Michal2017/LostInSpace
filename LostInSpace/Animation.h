#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture *texture, float time, int rows, int columns, sf::Vector2f position);
	~Animation();
	bool update(float time);
	sf::RectangleShape getBody() { return body; }

private:
	sf::IntRect image;
	sf::RectangleShape body;
	sf::Vector2f position;
	float time;
	float totalTime;
	int rows;
	int columns;
	int row;
	int column;
};
