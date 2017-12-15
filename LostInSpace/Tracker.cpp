#include "Tracker.h"

Tracker::Tracker()
{
}

Tracker::Tracker(sf::Texture * arrowTexture)
{
	body.setSize(sf::Vector2f(136.f, 98.f));
	body.setOrigin(body.getSize() / 2.f);
	body.setPosition(110.f, 1000.f);
	body.setTexture(arrowTexture);
}


Tracker::~Tracker()
{
}

void Tracker::update(sf::RectangleShape body1, sf::RectangleShape body2) //w domysle body1 - gracz, body2 - astronauta
{
	rotationAngle = atan2(body1.getPosition().y - body2.getPosition().y, body1.getPosition().x - body2.getPosition().x) * 180 / 3.14159265;
	body.setRotation(rotationAngle - 180.f);
}
