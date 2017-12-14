#pragma once

#include <SFML/Graphics.hpp>

#include "library.h"

class IButton //interfejs dla klas przyciskow
{
public:
	virtual void setPosition(sf::Vector2f position, bool center = false) = 0;
	virtual void setActive() = 0;
	virtual void setInactive() = 0;
	virtual sf::Text getDrawable() = 0;
};