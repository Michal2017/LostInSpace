#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "State.h"

class Instruction : public State
{
public:
	Instruction(std::string pathToImage, int width, int height);
	~Instruction();
	virtual void loadResources() override;
	virtual void eventHandle(sf::RenderWindow & window) override;
	virtual void update(float deltaTime, sf::RenderWindow & window) override;
	virtual void draw(sf::RenderWindow & window) override;

private:
	sf::Event event;
	sf::Texture texture;
	sf::Sprite image;
	sf::View view;
	std::string pathToImage;
	bool isReturnKeyReleased = false;
};