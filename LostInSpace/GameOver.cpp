#include "GameOver.h"

GameOver::GameOver(std::string pathToImage, sf::Font & font, int width, int height)
	: okButton("OK", font, 100),
	score("SCORE:", font, 250),
	sVal("", font, 250),
	highestScore("BEST:", font, 200),
	hsVal("", font, 200)
{
	this->width = width;
	this->height = height;
	this->pathToImage = pathToImage;
}

GameOver::~GameOver()
{
}

void GameOver::loadResources()
{
	view.setSize(originalWidth, originalHeight);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	view = getLetterboxView(view, width, height);

	texture.loadFromFile(pathToImage);
	image.setTexture(texture);

	int hsValT, sValT;

	scoreFile.open("highScore", std::ios::in);
	if (scoreFile.good())
	{
		scoreFile >> hsValT;
		scoreFile >> sValT;
		scoreFile.close();

		hsVal.updateValue(std::to_string(hsValT));
		sVal.updateValue(std::to_string(sValT));
	}
	else
	{
		hsVal.updateValue("ERROR");
		sVal.updateValue("ERROR");
	}

	okButton.setPosition(sf::Vector2f(0.0f, 800.0f), true);
	okButton.setActive();
	score.setPosition(sf::Vector2f(300.0f, 300.0f));
	sVal.setPosition(sf::Vector2f(1300.0f, 300.0f));
	highestScore.setPosition(sf::Vector2f(300.0f, 550.0f));
	hsVal.setPosition(sf::Vector2f(1300.0f, 550.0f));
}

void GameOver::eventHandle(sf::RenderWindow & window)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void GameOver::update(float deltaTime, sf::RenderWindow & window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		newState = sn::MenuState;
	}
}

void GameOver::draw(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);

	window.draw(image);
	window.draw(score.getDrawable());
	window.draw(sVal.getDrawable());
	window.draw(highestScore.getDrawable());
	window.draw(hsVal.getDrawable());
	window.draw(okButton.getDrawable());

	window.display();
}
