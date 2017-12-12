#pragma once

namespace sn
{
	enum GameState { None, SplashScreen, MenuState, OptionMenu, Instruction, Gameplay, GameOver };

	struct resolution
	{
		int x;
		int y;
	};
}