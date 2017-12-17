#include "Instruction.h"



Instruction::Instruction(std::string pathToImage, int width, int height)
{
	this->width = width;
	this->height = height;
	this->pathToImage = pathToImage;
}

Instruction::~Instruction()
{
}

void Instruction::loadResources()
{
	texture.loadFromFile(pathToImage);
	image.setTexture(texture);
	image.setPosition(0.f, 0.f);

	view.setSize(originalWidth, originalHeight);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	view = getLetterboxView(view, width, height);
}

void Instruction::eventHandle(sf::RenderWindow & window)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Instruction::update(float deltaTime, sf::RenderWindow & window)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		isReturnKeyReleased = true;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && isReturnKeyReleased)
	{
		newState = sn::Gameplay;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		newState = sn::MenuState;
	}
}

void Instruction::draw(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	window.setView(view);
	window.draw(image);
	window.display();
}
