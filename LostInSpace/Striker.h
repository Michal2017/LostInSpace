#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

class Striker
{
public:
	Striker(sf::Texture *texture, sf::Vector2f position);
	~Striker();
	void update(sf::Vector2f spaceshipPosition, float dTime);
	sf::RectangleShape getBody() { return body; };
	int dealDamage() { return damage; }
	void gotDamaged() { hp -= 1; }
	int showHp() { return hp; }

private:
	sf::RectangleShape body;
	float speed;
	int damage;
	int hp;
};
