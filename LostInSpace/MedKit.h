#pragma once

#include <SFML/Graphics.hpp>

class MedKit
{
public:
	MedKit(sf::Texture *texture, sf::Vector2f position);
	~MedKit();
	void update(float deltaTime);
	sf::RectangleShape getBody() { return body; }
	int getPower() { return power; }

private:
	sf::RectangleShape body;
	int power;
};