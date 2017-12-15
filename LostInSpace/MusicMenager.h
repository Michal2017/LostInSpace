#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <string>

class MusicMenager //Zarzadza muzyka w calej aplikacji.
{
public:
	MusicMenager(float musicVolume);
	~MusicMenager();
	enum trackName { MainMenu = 0, Gameplay = 1 };
	void play(trackName name);
	void setVolume(float musicVolume);

private:
	sf::Music track;
	std::map < trackName, std::string > playlist;
	float musicVolume;
};

