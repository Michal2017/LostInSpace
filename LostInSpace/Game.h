#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "State.h"
#include "SplashScreen.h"

class Game //Pseudo silnik gry.
{
public:
	Game(int width, int height, bool isFullScreen, std::string windowTitle);
	~Game();
	void run();

private:
	sf::RenderWindow window;
	int width;
	int height; //rozdzielczosc okna, pobrana z wczytanego pliku konfiguracyjnego
	const int originalWidth = 1920;
	const int originalHeight = 1080; //rozdzielczosc w jakiej byla projektowana gra
	float fxVolume;
	float musicVolume;
	bool isFullScreen;
	std::string windowTitle;
	std::unique_ptr<State> activeState; //wskaznik na aktywny stan gry
	void changeState(sn::GameState newState); //metoda zarzadzajaca zmiana stanu gry
};