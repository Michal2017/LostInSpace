#pragma once

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "library.h"
#include "projectile.h"

class Player
{
public:
	Player();
	Player(sf::Texture *playerTexture, sf::Texture *engineTexture);
	~Player();
	sf::RectangleShape getBody() { return body; }
	sf::Vector2f getPosition() { return body.getPosition(); }
	sf::Vector2f getMovement() { return movement; }
	void update(float deltaTime, sf::RenderWindow & window, sf::Texture *projectileTexture/*, sf::Sound *bulletFired*/);
	void draw(sf::RenderWindow & window);
	bool canISeeit(sf::RectangleShape object);
	bool canISeeit(sf::Sprite object);
	void gotDamaged(int dmg);
	bool gotHealed(int heal);
	int showHP() { return hp; };
	bool didItHit(sf::RectangleShape object);
	int showScore() { return score; }

private:
	sf::RectangleShape body;
	sf::Vector2f movement;
	sf::RectangleShape engine;
	sf::IntRect engineFrame;
	float rotationAngle;
	float speed;
	float movementX;
	float movementY;
	float cooldown;
	float animationCooldown;
	int hp;
	int score;
	std::vector < Projectile > bullets;
	void engineUpdate(bool isEngineOn, float dTime, float rotationAngle);
};

