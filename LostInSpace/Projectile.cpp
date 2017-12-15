#include "Projectile.h"

Projectile::Projectile(sf::Texture * texture, float rotationAngle, sf::Vector2f position, sf::Vector2f movement1, float speed, int damage)
{
	body.setSize(sf::Vector2f(34.0f, 32.f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
	body.setRotation(rotationAngle);
	movement = movement1;
	this->speed = speed;
	dmg = damage;
	movement.x = movement.x * speed;
	movement.y = movement.y * speed;
}

Projectile::~Projectile()
{
}

void Projectile::update(float dTime)
{
	body.move(sf::Vector2f(movement.x * dTime, movement.y * dTime));
}