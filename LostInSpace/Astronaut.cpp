#include "Astronaut.h"

Astronaut::Astronaut()
{

}

Astronaut::Astronaut(sf::Texture * astronautTexture)
{
	body.setSize(sf::Vector2f(62.f, 100.f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(astronautTexture);
}

Astronaut::~Astronaut()
{
}

void Astronaut::update(float deltaTime)
{
	body.rotate(20 * deltaTime);
}

void Astronaut::relocate()
{
	float x, y;
	x = std::rand() % 10000;
	y = std::rand() % 10000;
	body.setPosition(sf::Vector2f(x, y));
}
