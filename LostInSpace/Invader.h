#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include "Projectile.h"
#include "library.h"

class Invader
{
public:
	Invader(sf::Texture *texture, sf::Vector2f position, sf::Sound &copySound);
	~Invader();
	void update(float dTime, sf::Vector2f spaceshipPosition, sf::Texture *bulletTexture);
	void draw(sf::RenderWindow &window);
	bool didItHit(sf::RectangleShape object);
	void gotDamaged() { hp -= 1; }
	int showHP() { return hp; }
	sf::RectangleShape getBody() { return body; }
	int dealDamage() { return damage; }
	bool canISeeit(sf::RectangleShape object);

private:
	sf::RectangleShape body;
	sf::Sound fire;
	float rotationAngle;
	float speed;
	float dodgeSpeed;
	float dodgeDistance;
	float globalCd;
	float fullAutoCd;
	bool is90or270; //false - 90 stopni, true - 270 stopni
	int hp;
	short whichBullet;
	int damage;
	std::vector < Projectile > bullets;
};
