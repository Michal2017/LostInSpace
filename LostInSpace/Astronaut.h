#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <cstdlib>

class Astronaut
{
public:
	Astronaut();
	Astronaut(sf::Texture *astronautTexture);
	~Astronaut();
	sf::RectangleShape getBody() { return body; }
	sf::Vector2f getPosition() { return body.getPosition(); }
	void update(float deltaTime);
	void relocate();

private:
	sf::RectangleShape body;
};

