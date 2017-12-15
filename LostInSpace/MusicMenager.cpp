#include "MusicMenager.h"

MusicMenager::MusicMenager(float musicVolume)
{
	this->musicVolume = musicVolume;

	playlist[trackName::MainMenu] = "music/main_menu.ogg";
	playlist[trackName::Gameplay] = "music/level_music.ogg";
}

MusicMenager::~MusicMenager()
{
}

void MusicMenager::play(trackName name)
{
	track.openFromFile(playlist[name]);
	track.setLoop(true);
	track.setVolume(musicVolume);
	track.play();
}

void MusicMenager::setVolume(float musicVolume)
{
}
