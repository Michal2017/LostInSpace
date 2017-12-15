#pragma once

#include <fstream>

#include "State.h"
#include "library.h"

class ApplyOptions : public State //Klasa aplikujaca ustawienia z pliku konfiguracyjnego.
{
public:
	ApplyOptions(float & fxVolume, float & musicVolume, bool & isFullScreen, int & width, int & height);
	~ApplyOptions();
	virtual void loadResources() override;
	virtual void eventHandle(sf::RenderWindow & window) override;
	virtual void update(float deltaTime, sf::RenderWindow & window) override;
	virtual void draw(sf::RenderWindow & window) override;

private:
	float *fxVolume;
	float *musicVolume;
	bool *isFullScreen;
	int *width;
	int *height;
	short windowResolution; //odnosi sie do elementu tablicy z rozdzielczosciami resolutions
};

