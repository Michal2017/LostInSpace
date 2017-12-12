#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "State.h"

class MenuState : public State
{
public:
	MenuState(std::string pathToImage, std::string pathToFont);
	~MenuState();
	void loadResources();
	void eventHandle(sf::RenderWindow & window);
	void update(float deltaTime);
	void draw(sf::RenderWindow & window);

private:
	sf::Event event;
	sf::Texture menuBackgroundTexture;
	sf::Sprite menuBackground;
	sf::View view;
	std::string pathToImage;
	std::string pathToFont;

};

