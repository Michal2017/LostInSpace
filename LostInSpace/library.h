#pragma once

//zawiera globalne stale, struktury itp. 

namespace sn //sn - state names
{
	enum GameState { None, SplashScreen, MenuState, OptionsMenu, Instruction, Gameplay, GameOver, Quit };

	struct resolution
	{
		int x;
		int y;
	};
}

const int originalWidth = 1920;
const int originalHeight = 1080; //rozdzielczosc w jakiej byla projektowana gra