#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

#include "State.h"
#include "library.h"
#include "MenuButton.h"
#include "OptionsButton.h"

class GameOver : public State
{
public:
	GameOver(std::string pathToImage, sf::Font & font, int width, int height);
	~GameOver();
	virtual void loadResources() override;
	virtual void eventHandle(sf::RenderWindow & window) override;
	virtual void update(float deltaTime, sf::RenderWindow & window) override;
	virtual void draw(sf::RenderWindow & window) override;

private:
	sf::Event event;
	sf::View view;
	sf::Texture texture;
	sf::Sprite image;
	std::string pathToImage;
	std::fstream scoreFile;
	MenuButton okButton;
	MenuButton score;
	OptionsButton sVal;
	MenuButton highestScore;
	OptionsButton hsVal;
};

