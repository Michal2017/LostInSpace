#include "Game.h"

Game::Game(int width, int height, bool isFullScreen, std::string windowTitle)
	: window(sf::VideoMode(width, height), windowTitle, (sf::Style::Close))
{
	this->width = width;
	this->height = height;
	this->isFullScreen = isFullScreen;
	this->windowTitle = windowTitle;
	window.setFramerateLimit(60); //maksymalna ilosc klatek na sekunde = 60
	window.setMouseCursorVisible(false);
	if (isFullScreen)
	{
		window.create((sf::VideoMode(width, height)), windowTitle, (sf::Style::Fullscreen)); //przelaczenie okna na tryb pelnoekranowy
	}
}


Game::~Game()
{
}

void Game::run() //urochomienie gry
{
	sf::Clock gameClock;
	float deltaTime;

	std::unique_ptr<SplashScreen> splashScreen(new SplashScreen("background/made_with_sfml.png", width, height, originalWidth, originalHeight)); //pierwszy stan gry - logo

	activeState = std::move(splashScreen);
	activeState->loadResources();

	while (window.isOpen())
	{
		deltaTime = gameClock.restart().asSeconds();

		activeState->eventHandle(window);
		activeState->update(deltaTime);
		activeState->draw(window);
		changeState(activeState->changeTo());
	}
}

void Game::changeState(sn::GameState newState)
{
	if (newState == sn::None); //brak zmiany stanu gry
	else if (newState == sn::MenuState)
	{
		window.close();
	}
}