#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <memory>
#include <iostream>

#include "MusicMenager.h"
#include "SplashScreen.h"
#include "MenuState.h"
#include "OptionsMenu.h"
#include "ApplyOptions.h"
#include "Instruction.h"
#include "Gameplay.h"

class Game //Pseudo silnik gry.
{
public:
	Game(int width, int height, bool isFullScreen, std::string windowTitle, int fxVolume, int musicVolume);
	~Game();
	void run();

private:
	sf::RenderWindow window;
	sf::Font font;
	MusicMenager musicMenager;
	int width;
	int height; //rozdzielczosc okna, pobrana z wczytanego pliku konfiguracyjnego
	float fxVolume;
	float musicVolume;
	bool isFullScreen;
	std::string windowTitle;
	std::unique_ptr<State> activeState; //wskaznik na aktywny stan gry
	void changeState(sn::GameState newState); //metoda zarzadzajaca zmiana stanu gry
};