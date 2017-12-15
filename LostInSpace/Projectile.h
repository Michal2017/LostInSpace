#pragma once

#include <SFML/Graphics.hpp>

class Projectile
{
public:
	Projectile(sf::Texture *texture, float rotationAngle, sf::Vector2f position, sf::Vector2f movement1, float speed, int damage);
	~Projectile();
	sf::RectangleShape getBody() { return body; }
	void update(float dTime);
	int showDmg() { return dmg; }

private:
	sf::RectangleShape body;
	sf::Vector2f movement;
	float speed;
	int dmg;
};

