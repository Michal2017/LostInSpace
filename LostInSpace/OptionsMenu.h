#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

#include "State.h"
#include "MenuButton.h"
#include "OptionsButton.h"

class OptionsMenu : public State //ekran opcji
{
public:
	OptionsMenu(std::string pathToImage, sf::Font & font, int width, int height);
	~OptionsMenu();
	virtual void loadResources();
	virtual void eventHandle(sf::RenderWindow & window);
	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow & window);

private:
	std::string boolToString(bool a);
	sf::Event event;
	sf::Texture menuBackgroundTexture;
	sf::Sprite menuBackground;
	sf::View view;
	sf::Font font;
	std::string pathToImage;
	std::vector<std::unique_ptr<MenuButton>> buttons; //tablica z przyciskami
	short activeButton = 0; //aktywny przycisk, odnosi sie do elementu tablicy buttons
	bool downKeyIsReleased = true;
	bool upKeyIsReleased = true;
	bool returnKeyIsReleased = false;
	int musicVolume; //stale do wczytania z pliku konfiguracyjnego
	int fxVolume;
	short windowResolution;
	bool isFullScr;
};

