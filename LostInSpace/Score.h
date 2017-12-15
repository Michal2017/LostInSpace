#pragma once

#include <SFML\Graphics.hpp>
#include <string>

class Score
{
public:
	Score(sf::Font & font);
	~Score();
	void update(int value);
	sf::Text getDrawable();

private:
	sf::Text score;
};

