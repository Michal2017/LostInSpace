#include "MenuState.h"

MenuState::MenuState(std::string pathToImage, std::string pathToFont)
{
}

MenuState::~MenuState()
{
}

void MenuState::loadResources()
{
}

void MenuState::eventHandle(sf::RenderWindow & window)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void MenuState::update(float deltaTime)
{
}

void MenuState::draw(sf::RenderWindow & window)
{
}
