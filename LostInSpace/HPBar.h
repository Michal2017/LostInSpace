#pragma once

#include <SFML/Graphics.hpp>

class HPBar
{
public:
	HPBar();
	~HPBar();
	void update(int hp);
	void drawBar(sf::RenderWindow &window);
	void animate(float dTime);

private:
	sf::RectangleShape hp;
	sf::RectangleShape background;
	sf::RectangleShape animation;
};
