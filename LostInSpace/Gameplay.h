#pragma once

#include "State.h"
#include "Score.h"
#include "Player.h"

class Gameplay : public State
{
public:
	Gameplay(sf::Font & font, float fxVolume, float musicVolume, int width, int height);
	~Gameplay();
	virtual void loadResources() override;
	virtual void eventHandle(sf::RenderWindow & window) override;
	virtual void update(float deltaTime, sf::RenderWindow & window) override;
	virtual void draw(sf::RenderWindow & window) override;

private:
	sf::Event event;
	sf::Font font;
	sf::View view;
	sf::View hud;
	sf::View mouseView;
	sf::Texture playerTexture;
	sf::Texture backgroundTexture;
	sf::Texture engineTexture;
	sf::Sprite background;
	sf::Texture greenProjectileTexture;
	sf::Texture redProjectileTexture;
	sf::Texture aimTexture;
	sf::Sprite myMouse;
	Player player;
	Score score;
	float fxVolume;
	float musicVolume;
	int width;
	int height;
	bool isPaused = false;
};

