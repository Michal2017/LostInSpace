#include "Score.h"

Score::Score(sf::Font & font)
	: score("WYNIK 0", font, 50)
{
	score.setFillColor(sf::Color::Red);
	score.setPosition(sf::Vector2f(1540.f, 30.f));
	score.setOutlineColor(sf::Color::White);
	score.setOutlineThickness(3.0f);
}

Score::~Score()
{
}

void Score::update(int value)
{
	score.setString("WYNIK " + std::to_string(value));
}

sf::Text Score::getDrawable()
{
	return score;
}
