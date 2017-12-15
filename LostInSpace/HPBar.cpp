#include "HPBar.h"

HPBar::HPBar()
{
	hp.setSize(sf::Vector2f(700.f, 30.f));
	hp.setPosition(610.f, 1000.f);
	hp.setFillColor(sf::Color::Red);
	background.setSize(sf::Vector2f(720.f, 40.f));
	background.setPosition(600.f, 995.f);
	background.setFillColor(sf::Color(0, 0, 0, 155));
	animation.setSize(sf::Vector2f(700.f, 30.f));
	animation.setPosition(610.f, 1000.f);
	animation.setFillColor(sf::Color(250, 95, 15));
}

HPBar::~HPBar()
{
}

void HPBar::update(int hp)
{
	float newX = (float)hp * 7.f;
	this->hp.setSize(sf::Vector2f(newX, 30.f));
	if (this->hp.getSize().x > animation.getSize().x)
		animation.setSize(this->hp.getSize());
}

void HPBar::drawBar(sf::RenderWindow &window)
{
	window.draw(background);
	window.draw(animation);
	window.draw(hp);
}

void HPBar::animate(float dTime)
{
	if (hp.getSize().x < animation.getSize().x)
	{
		float newX = animation.getSize().x - 40.f * dTime;
		animation.setSize(sf::Vector2f(newX, 30.f));
	}
}