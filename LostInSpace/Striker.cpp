#include "Striker.h"

Striker::Striker(sf::Texture * texture, sf::Vector2f position)
{
	body.setSize(sf::Vector2f(54.f, 84.f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	speed = 100.f;
	damage = 10;
	hp = 3;
}

Striker::~Striker()
{
}

void Striker::update(sf::Vector2f spaceshipPosition, float dTime)
{
	speed += 150 * dTime;
	sf::Vector2f direction;
	float length =
		sqrt((spaceshipPosition.x - body.getPosition().x) * (spaceshipPosition.x - body.getPosition().x) +
		(spaceshipPosition.y - body.getPosition().y) * (spaceshipPosition.y - body.getPosition().y));
	direction.x = (spaceshipPosition.x - body.getPosition().x) / length * speed * dTime;
	direction.y = (spaceshipPosition.y - body.getPosition().y) / length * speed * dTime;
	body.move(direction);
	float rotationAngle = atan2(body.getPosition().y - spaceshipPosition.y, body.getPosition().x - spaceshipPosition.x) * 180 / 3.14159265;
	body.setRotation(rotationAngle - 90.f);
}
