#include "MenuState.h"

MenuState::MenuState(std::string pathToImage, sf::Font & font, int width, int height, float fxVolume)
{
	this->pathToImage = pathToImage;
	this->font = font;
	this->width = width;
	this->height = height;
	this->fxVolume = fxVolume;
}

MenuState::~MenuState()
{
}

void MenuState::loadResources()
{
	typedef MenuButton Button;
	int fontSize = 100;

	menuBackgroundTexture.loadFromFile(pathToImage);
	menuBackground.setTexture(menuBackgroundTexture);

	view.setSize(originalWidth, originalHeight);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	view = getLetterboxView(view, width, height);

	//stworzenie przyciskow
	buttons.push_back(Button("ROZPOCZNIJ", font, fontSize));
	buttons.push_back(Button("OPCJE", font, fontSize));
	buttons.push_back(Button("WYJSCIE", font, fontSize));

	//konfiguracja przyciskow
	int i = 0;
	buttons[i].setActive();
	buttons[i++].setPosition(sf::Vector2f(0.0f, 350.0f), true);
	buttons[i++].setPosition(sf::Vector2f(0.0f, 500.0f), true);
	buttons[i++].setPosition(sf::Vector2f(0.0f, 650.0f), true);

	buttonSwitchSoundB.loadFromFile("music/menuSound.wav");
	buttonSwitchSound.setBuffer(buttonSwitchSoundB);
	buttonSwitchSound.setVolume(fxVolume);
}

void MenuState::eventHandle(sf::RenderWindow & window)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void MenuState::update(float deltaTime, sf::RenderWindow & window)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) //sprawdzenie czy nie jest wcisniety klawisz enter
	{
		returnKeyIsReleased = true;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && downKeyIsReleased == 1) //wczytanie wejscia z klawiatury (ze strzalek lub W / S)
	{
		buttonSwitchSound.play();
		activeButton += 1;
		downKeyIsReleased = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		downKeyIsReleased = true;
	}
	
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && upKeyIsReleased == 1)
	{
		buttonSwitchSound.play();
		activeButton -= 1;
		upKeyIsReleased = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		upKeyIsReleased = true;
	}

	if (activeButton == -1)
	{
		activeButton = buttons.size() - 1;
	}
	else if (activeButton == buttons.size())
	{
		activeButton = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && returnKeyIsReleased == 1)
	{
		if (activeButton == 0)
		{
			newState = sn::Instruction;
		}
		else if (activeButton == 1)
		{
			newState = sn::OptionsMenu;
		}
		else if (activeButton == 2)
		{
			newState = sn::Quit;
		}
	}

	for (unsigned int i = 0; i < buttons.size(); ++i) //wizualne uaktualnienie aktywnego przycisku
	{
		if (i == activeButton)
		{
			buttons[i].setActive();
		}
		else
		{
			buttons[i].setInactive();
		}
	}
}

void MenuState::draw(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	window.setView(view);
	window.draw(menuBackground);
	for (unsigned int i = 0; i < buttons.size(); ++i)
	{
		window.draw(buttons[i].getDrawable());
	}
	window.display();
}
