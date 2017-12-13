#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "State.h"
#include "MenuButton.h"

class MenuState : public State
{
public:
	MenuState(std::string pathToImage, sf::Font & font);
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
	sf::Font font;
	std::string pathToImage;
	std::vector<MenuButton> buttons; //tablica z przyciskami
	short activeButton = 0; //aktywny przycisk, odnosi sie do elementu tablicy buttons
	bool downKeyIsReleased = true;
	bool upKeyIsReleased = true;
	bool returnKeyIsReleased = false;
};

