#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <list>

#include "State.h"
#include "MusicMenager.h"
#include "Score.h"
#include "Player.h"
#include "Astronaut.h"
#include "Tracker.h"
#include "Animation.h"
#include "MedKit.h"
#include "HPBar.h"
#include "Warning.h"
#include "Striker.h"
#include "Invader.h"
#include "MenuButton.h"

class Gameplay : public State
{
public:
	Gameplay(sf::Font & font, float fxVolume, float musicVolume, int width, int height, MusicMenager & musicMenager);
	~Gameplay();
	virtual void loadResources() override;
	virtual void eventHandle(sf::RenderWindow & window) override;
	virtual void update(float deltaTime, sf::RenderWindow & window) override;
	virtual void draw(sf::RenderWindow & window) override;

private:
	void saveScore();
	static const int numberOfMeteors = 300; //liczba meteorow
	sf::Event event;
	sf::Font font;
	sf::View view; //widok obiektow w grze
	sf::View hud; //widok interfejsu
	sf::View mouseView; //widok kursora
	sf::Texture playerTexture;
	sf::Texture backgroundTexture;
	sf::Texture engineTexture;
	sf::Sprite background; //obrazek w tle
	sf::Texture greenProjectileTexture;
	sf::Texture redProjectileTexture;
	sf::Texture aimTexture;
	sf::Sprite myMouse; //obrazek kursora
	sf::Texture meteor1;
	sf::Texture meteor2;
	sf::Texture meteor3;
	sf::Texture meteor4;
	sf::Texture meteor5;
	sf::Texture meteor6;
	sf::Texture meteor7;
	sf::Sprite meteors[numberOfMeteors];
	sf::Texture astronautTexture;
	sf::Texture trackerTexture;
	sf::Texture explosionTexture;
	sf::Texture fogTexture;
	sf::Texture strikerTexture;
	sf::Texture medKitTexture;
	sf::Texture invaderTexture;
	sf::SoundBuffer astronautCollectedB;
	sf::Sound astronautCollected;
	sf::SoundBuffer bulletFiredB;
	sf::Sound bulletFired;
	sf::SoundBuffer damageTakenB;
	sf::Sound damageTaken;
	sf::SoundBuffer explodedB;
	sf::Sound exploded;
	sf::SoundBuffer medKitTakenB;
	sf::Sound medKitTaken;
	sf::SoundBuffer spaceGunB;
	sf::Sound spaceGun;
	sf::SoundBuffer invaderSpawnB;
	sf::Sound invaderSpawn;
	std::vector < Animation > explosions;
	std::list < sf::Sound > explosionSounds;
	std::vector < Striker > strikers;
	std::vector < Invader > invaders;
	std::vector < MedKit > medKits;
	MusicMenager *musicMenager;
	Player player;
	Score score;
	Astronaut astronaut;
	Tracker tracker;
	Warning outOfArea;
	HPBar hpbar;
	MenuButton pause;
	float fxVolume;
	float musicVolume;
	float invaderSpawnTime = 0.0f;
	int width;
	int height;
	bool isPaused = false;
	bool pKeyIsReleased = true;
};

