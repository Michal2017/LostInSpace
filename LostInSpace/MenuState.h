#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

#include "State.h"
#include "MenuButton.h"

class MenuState : public State //ekran menu
{
public:
	MenuState(std::string pathToImage, sf::Font & font, int width, int height, float fxVolume);
	~MenuState();
	void loadResources();
	void eventHandle(sf::RenderWindow & window);
	void update(float deltaTime, sf::RenderWindow & window);
	void draw(sf::RenderWindow & window);

private:
	sf::Event event;
	sf::Texture menuBackgroundTexture;
	sf::Sprite menuBackground;
	sf::View view;
	sf::Font font;
	sf::SoundBuffer buttonSwitchSoundB;
	sf::Sound buttonSwitchSound;
	std::string pathToImage;
	std::vector<MenuButton> buttons; //tablica z przyciskami
	short activeButton = 0; //aktywny przycisk, odnosi sie do elementu tablicy buttons
	bool downKeyIsReleased = true;
	bool upKeyIsReleased = true;
	bool returnKeyIsReleased = false;
	float fxVolume;
};

