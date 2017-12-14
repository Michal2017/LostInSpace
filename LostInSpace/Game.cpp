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

	font.loadFromFile("fonts/spartaco.ttf");

	std::unique_ptr<SplashScreen> splashScreen(new SplashScreen("background/made_with_sfml.png", width, height)); //pierwszy stan gry - logo

	activeState = std::move(splashScreen);
	activeState->loadResources();

	while (window.isOpen())
	{
		deltaTime = gameClock.restart().asSeconds();

		activeState->eventHandle(window);
		activeState->update(deltaTime);
		activeState->draw(window); //error dla window.setView(view)
		changeState(activeState->changeTo());
	}
}

void Game::changeState(sn::GameState newState)
{
	if (newState == sn::None); //brak zmiany stanu gry
	else if (newState == sn::MenuState)
	{
		std::unique_ptr<MenuState> menuState(new MenuState("background/menu_background.png", font, width, height));
		activeState = std::move(menuState);
		activeState->loadResources();
	}
	else if (newState == sn::OptionsMenu)
	{
		std::unique_ptr<OptionsMenu> optionsMenu(new OptionsMenu("background/menu_background.png", font, width, height));
		activeState = std::move(optionsMenu);
		activeState->loadResources();
	}
	else if (newState == sn::ApplyOptions)
	{
		std::unique_ptr<ApplyOptions> applyOptions(new ApplyOptions(fxVolume, musicVolume, isFullScreen, width, height));
		activeState = std::move(applyOptions);
		activeState->loadResources();
	}
	else if (newState == sn::Instruction)
	{
		//instrukcja
	}
	else if (newState == sn::Quit)
	{
		window.close();
	}
}

void Game::updateOptions()
{
	std::fstream config;

	config.open("config", std::ios::in); //otworz do odczytu
	if (config.good())
	{
		config >> musicVolume; //glosnosc muzyki
		config >> fxVolume; //glosnosc efektow
		config.close();
	}
}
