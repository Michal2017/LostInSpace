#include "library.h"

bool isColliding(sf::RectangleShape object1, sf::RectangleShape object2)
{
	if ((fabs(object1.getPosition().x - object2.getPosition().x) <= (object1.getSize().x / 2.f + object2.getSize().x / 2.f)) &&
		(fabs(object1.getPosition().y - object2.getPosition().y) <= (object1.getSize().y / 2.f + object2.getSize().y / 2.f)))
		return true;

	else
		return false;
}