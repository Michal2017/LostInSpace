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
	int oFSize = 50;
	int fSize = 100;

	menuBackgroundTexture.loadFromFile(pathToImage);
	menuBackground.setTexture(menuBackgroundTexture);

	view.setSize(originalWidth, originalHeight);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	view = getLetterboxView(view, width, height);

	std::fstream config;

	config.open("config", std::ios::in); //otworz do odczytu
	if (config.good())
	{
		config >> musicVolume; //glosnosc muzyki
		config >> fxVolume; //glosnosc efektow
		config >> isFullScr; //czy aktywny jest tryb pelnoekranowy
		config >> windowResolution; //rozmiar okna - wartosc odnosi sie do elementu tablicy resolutions
		config.close();
	}

	//stworzenie przyciskow
	buttons.push_back(MenuButton("GLOSNOSC FX", font, oFSize));
	values.push_back(OptionsButton((std::to_string(fxVolume) + "%"), font, oFSize));
	buttons.push_back(MenuButton("GLOSNOSC MUZYKI", font, oFSize));
	values.push_back(OptionsButton((std::to_string(musicVolume) + "%"), font, oFSize));
	buttons.push_back(MenuButton("PELNY EKRAN", font, oFSize));
	values.push_back(OptionsButton(boolToString(isFullScr), font, oFSize));
	buttons.push_back(MenuButton("ROZDZIELCZOSC", font, oFSize));
	values.push_back(OptionsButton((std::to_string(resolutions[windowResolution].x) + " x " + std::to_string(resolutions[windowResolution].y)), font, oFSize));
	buttons.push_back(MenuButton("ZATWIERDZ", font, fSize));
	values.push_back(OptionsButton("", font, fSize));
	buttons.push_back(MenuButton("COFNIJ", font, fSize));
	values.push_back(OptionsButton("", font, fSize));

	//konfiguracja przyciskow
	int i = 0;
	buttons[i].setActive();
	values[i].setActive();
	buttons[i].setPosition(sf::Vector2f(770.f, 150.f));
	values[i++].setPosition(sf::Vector2f(1300.f, 150.f));
	buttons[i].setPosition(sf::Vector2f(630.f, 300.f));
	values[i++].setPosition(sf::Vector2f(1300.f, 300.f));
	buttons[i].setPosition(sf::Vector2f(750.f, 450.f));
	values[i++].setPosition(sf::Vector2f(1300.f, 450.f));
	buttons[i].setPosition(sf::Vector2f(680.f, 600.f));
	values[i++].setPosition(sf::Vector2f(1300.f, 600.f));
	buttons[i].setPosition(sf::Vector2f(0.0f, 850.f), true);
	values[i++].setPosition(sf::Vector2f(0.0f, 850.f));
	buttons[i].setPosition(sf::Vector2f(0.0f, 1000.0f), true);
	values[i++].setPosition(sf::Vector2f(0.0f, 1000.0f));

}

void OptionsMenu::eventHandle(sf::RenderWindow & window)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void OptionsMenu::update(float deltaTime, sf::RenderWindow & window)
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

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && leftKeyIsReleased == true) //zmiana ustawien klawiszem A lub strzalka w lewo
	{
		int i = 0;
		leftKeyIsReleased = false;
		if (activeButton == i++)
		{
			fxVolume -= 5.f;
			if (fxVolume < 0.f)
			{
				fxVolume = 0.f;
			}
			values[activeButton].updateValue(std::to_string(fxVolume) + "%");
		}
		else if (activeButton == i++)
		{
			musicVolume -= 5.f;
			if (musicVolume < 0.f)
			{
				musicVolume = 0.f;
			}
			values[activeButton].updateValue(std::to_string(musicVolume) + "%");
		}
		else if (activeButton == i++)
		{
			if (isFullScr == true)
			{
				isFullScr = false;
			}
			else
			{
				isFullScr = true;
			}
			values[activeButton].updateValue(boolToString(isFullScr));
		}
		else if (activeButton == i++)
		{
			windowResolution -= 1;
			if (windowResolution < 0)
			{
				windowResolution = 13;
			}
			values[activeButton].updateValue(std::to_string(resolutions[windowResolution].x) + " x " + std::to_string(resolutions[windowResolution].y));
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && rightKeyIsReleased == true) //zmiana ustawien klawiszem D lub strzalka w prawo
	{
		int i = 0;
		rightKeyIsReleased = false;
		if (activeButton == i++)
		{
			fxVolume += 5.f;
			if (fxVolume > 100.f)
			{
				fxVolume = 100.f;
			}
			values[activeButton].updateValue(std::to_string(fxVolume) + "%");
		}
		else if (activeButton == i++)
		{
			musicVolume += 5.f;
			if (musicVolume > 100.f)
			{
				musicVolume = 100.f;
			}
			values[activeButton].updateValue(std::to_string(musicVolume) + "%");
		}
		else if (activeButton == i++)
		{
			if (isFullScr == true)
			{
				isFullScr = false;
			}
			else
			{
				isFullScr = true;
			}
			values[activeButton].updateValue(boolToString(isFullScr));
		}
		else if (activeButton == i++)
		{
			windowResolution += 1;
			if (windowResolution > 13)
			{
				windowResolution = 0;
			}
			values[activeButton].updateValue(std::to_string(resolutions[windowResolution].x) + " x " + std::to_string(resolutions[windowResolution].y));
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rightKeyIsReleased = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		leftKeyIsReleased = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && returnKeyIsReleased == true) //gdy wcisniety zostanie klawisz Enter
	{
		if (activeButton == (buttons.size() - 2)) //jezeli aktywny jest guzik "zatwierdz"
		{
			std::fstream config;
			config.open("config", std::ios::out | std::ios::trunc);
			if (config.good())
			{
				config << musicVolume;
				config << " ";
				config << fxVolume;
				config << " ";
				config << isFullScr;
				config << " ";
				config << windowResolution;
				config.close();
			}

			newState = sn::ApplyOptions;
		}
		else if (activeButton == buttons.size() - 1) //jezeli aktywny jest guzik "cofnij"
		{
			newState = sn::MenuState;
		}
	}

	for (size_t i = 0; i < buttons.size(); ++i) //wizualne uaktualnienie aktywnego przycisku
	{
		if (i == activeButton)
		{
			buttons[i].setActive();
			values[i].setActive();
		}
		else
		{
			buttons[i].setInactive();
			values[i].setInactive();
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
		window.draw(buttons[i].getDrawable());
		window.draw(values[i].getDrawable());
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
