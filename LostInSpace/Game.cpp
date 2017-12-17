#include "Game.h"

Game::Game(int width, int height, bool isFullScreen, std::string windowTitle, int fxVolume, int musicVolume)
	: window(sf::VideoMode(width, height), windowTitle, (sf::Style::Close)), musicMenager(musicVolume)
{
	this->width = width;
	this->height = height;
	this->isFullScreen = isFullScreen;
	this->windowTitle = windowTitle;
	this->fxVolume = fxVolume;
	this->musicVolume = musicVolume;
	if (isFullScreen)
	{
		window.create((sf::VideoMode(width, height)), windowTitle, (sf::Style::Fullscreen)); //przelaczenie okna na tryb pelnoekranowy
	}
	window.setFramerateLimit(60); //maksymalna ilosc klatek na sekunde = 60
	window.setMouseCursorVisible(false);
}


Game::~Game()
{
}

void Game::run() //urochomienie gry
{
	musicMenager.play(MusicMenager::trackName::MainMenu);

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
		activeState->update(deltaTime, window);
		activeState->draw(window);
		changeState(activeState->changeTo());
	}
}

void Game::changeState(sn::GameState newState)
{
	if (newState == sn::None); //brak zmiany stanu gry
	else if (newState == sn::MenuState)
	{
		std::unique_ptr<MenuState> menuState(new MenuState("background/menu_background.png", font, width, height, fxVolume));
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
		std::unique_ptr<ApplyOptions> applyOptions(new ApplyOptions(fxVolume, musicVolume, isFullScreen, width, height, musicMenager));
		activeState = std::move(applyOptions);
		activeState->loadResources();
	}
	else if (newState == sn::Instruction)
	{
		std::unique_ptr<Instruction> instruction(new Instruction("background/instruction.png", width, height));
		activeState = std::move(instruction);
		activeState->loadResources();
	}
	else if (newState == sn::Gameplay)
	{
		sf::Texture loadingT;
		loadingT.loadFromFile("background/loading.png");
		sf::Sprite loading;
		loading.setTexture(loadingT);
		window.clear(sf::Color::Black);
		window.draw(loading);
		window.display(); //wyswietla ekran ladowania
		std::unique_ptr<Gameplay> gameplay(new Gameplay(font, fxVolume, musicVolume, width, height, musicMenager));
		activeState = std::move(gameplay);
		activeState->loadResources();
	}
	else if (newState == sn::GameOver)
	{
		std::unique_ptr<GameOver> gameOver(new GameOver("background/game_background.png", font, width, height));
		activeState = std::move(gameOver);
		activeState->loadResources();
	}
	else if (newState == sn::Quit)
	{
		window.close();
	}
}