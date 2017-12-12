#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "library.h"
#include "Game.h"

int main()
{
	srand(time(NULL));

	const sn::resolution resolutions[14] =
	{
	{ 800, 600 },
	{ 1024, 768 },
	{ 1152, 864 },
	{ 1280, 720 },
	{ 1280, 768 },
	{ 1280, 800 },
	{ 1280, 1024 },
	{ 1360, 768 },
	{ 1366, 768 },
	{ 1440, 900 },
	{ 1536, 864 },
	{ 1600, 900 },
	{ 1680, 1050 },
	{ 1920, 1080 }
	};

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