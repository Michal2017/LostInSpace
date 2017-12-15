#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

//zawiera globalne stale, struktury itp. 

bool isColliding(sf::RectangleShape object1, sf::RectangleShape object2);

namespace sn //sn - state names
{
	enum GameState { None, SplashScreen, MenuState, OptionsMenu, ApplyOptions, Instruction, Gameplay, GameOver, Quit };

	struct resolution
	{
		int x;
		int y;
	};
}

const int originalWidth = 1920;
const int originalHeight = 1080; //rozdzielczosc w jakiej byla projektowana gra

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