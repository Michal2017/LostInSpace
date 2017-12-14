#include <iostream>
#include <string>
#include <fstream>

#include "library.h"
#include "Game.h"

int main()
{
	srand(time(NULL));

	std::fstream config; //obiekt wczytujacy plik konfiguracyjny
	float musicVolume, fxVolume;
	bool isFullScr = false;
	short windowResolution = 0;

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
		config.open("config", std::ios::out | std::ios::trunc); //utworz nowy plik konfiguracyjny
		config << 25;
		config << " ";
		config << 75;
		config << " ";
		config << false;
		config << " ";
		config << 0;
		config.close();
	}

	Game game(resolutions[windowResolution].x, resolutions[windowResolution].y, isFullScr, "Lost in Space");

	game.run();

	return 0;
}