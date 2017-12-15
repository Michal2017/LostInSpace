#include "MedKit.h"

MedKit::MedKit(sf::Texture * texture, sf::Vector2f position)
{
	body.setSize(sf::Vector2f(100.0f, 100.f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
	power = 20;
}

MedKit::~MedKit()
{
}

void MedKit::update(float deltaTime)
{
	body.rotate(20 * deltaTime);
}
