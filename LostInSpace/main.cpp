#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "library.h"
#include "Game.h"

int main()
{
	srand(time(NULL));

	std::fstream config; //obiekt wczytujacy plik konfiguracyjny
	float musicVolume = 25.f, fxVolume = 75.f;
	bool isFullScr = false;
	short windowResolution = 0;

	config.open("config", std::ios::in); //otworz do odczytu
	if (config.good())
	{
		std::cout << "cfg loaded" << std::endl;
		config >> musicVolume; //glosnosc muzyki
		config >> fxVolume; //glosnosc efektow
		config >> isFullScr; //czy aktywny jest tryb pelnoekranowy
		config >> windowResolution; //rozmiar okna - wartosc odnosi sie do elementu tablicy resolutions
		config.close();
	}

	Game game(resolutions[windowResolution].x, resolutions[windowResolution].y, isFullScr, "Lost in Space");

	game.run();

	return 0;
}