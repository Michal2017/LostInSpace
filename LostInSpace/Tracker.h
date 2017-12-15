#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class Tracker //Wskazuje w ktorym kierunku powinien sie poruszac gracz, aby odnalezc astronaute.
{
public:
	Tracker();
	Tracker(sf::Texture *arrowTexture);
	~Tracker();
	void update(sf::RectangleShape body1, sf::RectangleShape body2);
	sf::RectangleShape getBody() { return body; }

private:
	sf::RectangleShape body;
	float rotationAngle;
};

