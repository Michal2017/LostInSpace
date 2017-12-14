#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(std::string pathToImage, sf::Font & font, int width, int height)
{
	this->pathToImage = pathToImage;
	this->font = font;
	this->width = width;
	this->height = height;
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::loadResources()
{
	typedef std::unique_ptr<MenuButton> Button;

	int oFSize = 50;
	int fSize = 100;

	menuBackgroundTexture.loadFromFile(pathToImage);
	menuBackground.setTexture(menuBackgroundTexture);

	view.setSize(originalWidth, originalHeight);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	view = getLetterboxView(view, width, height);

	std::fstream config;
	try
	{
		config.open("config", std::ios::in); //otworz do odczytu
		if (config.good())
		{
			config >> musicVolume; //glosnosc muzyki
			config >> fxVolume; //glosnosc efektow
			config >> isFullScr; //czy aktywny jest tryb pelnoekranowy
			config >> windowResolution; //rozmiar okna - wartosc odnosi sie do elementu tablicy resolutions
			config.close();
		}
		else
		{
			throw 1;
		}
	}
	catch (int e)
	{
		
	}

	//stworzenie przyciskow
	buttons.push_back(std::move(Button(new OptionsButton("GLOSNOSC FX", (std::to_string(fxVolume) + "%"), font, oFSize))));
	buttons.push_back(std::move(Button(new OptionsButton("GLOSNOSC MUZYKI", (std::to_string(musicVolume) + "%"), font, oFSize))));
	buttons.push_back(std::move(Button(new OptionsButton("PELNY EKRAN", boolToString(isFullScr), font, oFSize))));
	buttons.push_back(std::move(Button(new OptionsButton("ROZDZIELCZOSC", (std::to_string(resolutions[windowResolution].x) + " x " + std::to_string(resolutions[windowResolution].y)), font, oFSize))));
	buttons.push_back(std::move(Button(new MenuButton("ZATWIERDZ", font, fSize))));

	//konfiguracja przyciskow
	int i = 0;
	buttons[i]->setActive();
	buttons[i++]->setPosition(sf::Vector2f(770.f, 150.f), sf::Vector2f(1300.f, 150.f));
	buttons[i++]->setPosition(sf::Vector2f(630.f, 300.f), sf::Vector2f(1300.f, 300.f));
	buttons[i++]->setPosition(sf::Vector2f(750.f, 450.f), sf::Vector2f(1300.f, 450.f));
	buttons[i++]->setPosition(sf::Vector2f(680.f, 600.f), sf::Vector2f(1300.f, 600.f));
	buttons[i++]->setPosition(sf::Vector2f(800.f, 850.f), true);
}

void OptionsMenu::eventHandle(sf::RenderWindow & window)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void OptionsMenu::update(float deltaTime)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) //sprawdzenie czy nie jest wcisniety klawisz enter
	{
		returnKeyIsReleased = true;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && downKeyIsReleased == 1) //wczytanie wejscia z klawiatury (ze strzalek lub W / S)
	{
		activeButton += 1;
		downKeyIsReleased = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		downKeyIsReleased = true;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && upKeyIsReleased == 1)
	{
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

	for (size_t i = 0; i < buttons.size(); ++i) //wizualne uaktualnienie aktywnego przycisku
	{
		if (i == activeButton)
		{
			buttons[i]->setActive();
		}
		else
		{
			buttons[i]->setInactive();
		}
	}
}

void OptionsMenu::draw(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	window.setView(view);
	window.draw(menuBackground);

	for (size_t i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->draw(window);
	}

	window.display();
}

std::string OptionsMenu::boolToString(bool a)
{
	if (a)
	{
		return "ON";
	}
	else
	{
		return "OFF";
	}
}
