#include "Gameplay.h"

Gameplay::Gameplay(sf::Font & font, float fxVolume, float musicVolume, int width, int height, MusicMenager & musicMenager)
	: score(font), outOfArea(originalWidth, font, 400, "OUT OF AREA", 50)
{
	this->musicMenager = &musicMenager;
	this->font = font;
	this->fxVolume = fxVolume;
	this->musicVolume = musicVolume;
	this->width = width;
	this->height = height;
}

Gameplay::~Gameplay()
{
}

void Gameplay::loadResources()
{
	//widoki
	view.setSize(originalWidth, originalHeight);
	view = getLetterboxView(view, width, height);
	hud.setSize(originalWidth, originalHeight);
	hud.setCenter(hud.getSize().x / 2, hud.getSize().y / 2);
	hud = getLetterboxView(hud, width, height);
	mouseView.setSize(width, height);
	mouseView.setCenter(mouseView.getSize().x / 2, mouseView.getSize().y / 2);
	/********************************************/

	//tekstury
	playerTexture.loadFromFile("textures/player_texture.png");
	playerTexture.setSmooth(true);
	engineTexture.loadFromFile("textures/engine_exhaust.png");
	engineTexture.setSmooth(true);
	backgroundTexture.loadFromFile("background/game_background.png");
	background.setPosition(0.0f, 0.0f);
	greenProjectileTexture.loadFromFile("textures/green_projectile.png");
	redProjectileTexture.loadFromFile("textures/red_projectile.png");
	aimTexture.loadFromFile("textures/aim.png");
	astronautTexture.loadFromFile("textures/astro_texture.png");
	astronautTexture.setSmooth(true);
	meteor1.loadFromFile("textures/meteor1.png");
	meteor2.loadFromFile("textures/meteor2.png");
	meteor3.loadFromFile("textures/meteor3.png");
	meteor4.loadFromFile("textures/meteor4.png");
	meteor5.loadFromFile("textures/meteor5.png");
	meteor6.loadFromFile("textures/meteor6.png");
	meteor7.loadFromFile("textures/meteor7.png");
	trackerTexture.loadFromFile("textures/arrow_texture.png");
	trackerTexture.setSmooth(true);
	explosionTexture.loadFromFile("textures/explosion_animation.png");
	fogTexture.loadFromFile("textures/SmokeFrames.png");
	strikerTexture.loadFromFile("textures/alien1_texture.png");
	medKitTexture.loadFromFile("textures/mediKit.png");
	medKitTexture.setSmooth(true);
	invaderTexture.loadFromFile("textures/alien2_texture.png");
	/********************************************/

	//dzwieki
	astronautCollectedB.loadFromFile("music/astro_taken.ogg");
	astronautCollected.setBuffer(astronautCollectedB);
	astronautCollected.setVolume(fxVolume);
	bulletFiredB.loadFromFile("music/bullet_fired.wav");
	bulletFired.setBuffer(bulletFiredB);
	bulletFired.setVolume(fxVolume);
	damageTakenB.loadFromFile("music/alarm_sound.ogg");
	damageTaken.setBuffer(damageTakenB);
	damageTaken.setVolume(fxVolume);
	explodedB.loadFromFile("music/explosion.ogg");
	exploded.setBuffer(explodedB);
	exploded.setVolume(fxVolume);
	medKitTakenB.loadFromFile("music/mediKit.wav");
	medKitTaken.setBuffer(medKitTakenB);
	medKitTaken.setVolume(fxVolume);
	spaceGunB.loadFromFile("music/spaceGunSound.ogg");
	spaceGun.setBuffer(spaceGunB);
	spaceGun.setVolume(fxVolume);
	invaderSpawnB.loadFromFile("music/invaderSpawn.wav");
	invaderSpawn.setBuffer(invaderSpawnB);
	invaderSpawn.setVolume(fxVolume);
	/********************************************/

	//obiekty
	background.setTexture(backgroundTexture);
	player = Player(&playerTexture, &engineTexture);
	myMouse.setTexture(aimTexture);
	astronaut = Astronaut(&astronautTexture);
	astronaut.relocate();
	tracker = Tracker(&trackerTexture);
	for (int i = 0; i < numberOfMeteors; i++) //losowanie tekstur meteorow
	{
		int a = rand() % 7;
		if (a == 0)
			meteors[i].setTexture(meteor1);
		else if (a == 1)
			meteors[i].setTexture(meteor2);
		else if (a == 2)
			meteors[i].setTexture(meteor3);
		else if (a == 3)
			meteors[i].setTexture(meteor4);
		else if (a == 4)
			meteors[i].setTexture(meteor5);
		else if (a == 5)
			meteors[i].setTexture(meteor6);
		else if (a == 6)
			meteors[i].setTexture(meteor7);
		meteors[i].setPosition((float)(rand() % 10000), (float)(rand() % 10000));
	}
	for (int i = 0; i < 10; ++i)
	{
		float x = rand() % 10001;
		float y = rand() % 10001;
		medKits.push_back(MedKit(&medKitTexture, sf::Vector2f(x, y)));
	}
	/********************************************/

	musicMenager->play(MusicMenager::trackName::Gameplay); //muzyka
}

void Gameplay::eventHandle(sf::RenderWindow & window)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Gameplay::update(float deltaTime, sf::RenderWindow & window)
{
	if (!isPaused) //jezeli gra nie jest w trybie pauzy
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //wyjscie z gry po nacisnieciu Esc
		{
			backToMenu();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) //koniec pauzy
		{
			isPaused = true;
		}
		window.setView(mouseView);
		myMouse.setPosition((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y); //uaktualnienie kursora

		window.setView(view);
		player.update(deltaTime, window, &greenProjectileTexture);

		tracker.update(player.getBody(), astronaut.getBody());

		view.setCenter(player.getPosition()); //ustawienie kamery na statku gracza
	}
	else // jezeli gra jest w trybie pauzy
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //wyjscie z gry po nacisnieciu Esc
		{
			backToMenu();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) //koniec pauzy
		{
			isPaused = false;
		}

		window.setView(mouseView);
		myMouse.setPosition((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y); //uaktualnienie kursora
	}
}

void Gameplay::draw(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);

	window.setView(hud); //tlo
	window.draw(background);

	window.setView(view); //obiekty
	for (int i = 0; i < numberOfMeteors; i++)
	{
		if (player.canISeeit(meteors[i]))
			window.draw(meteors[i]);
	}
	for (unsigned int i = 0; i < medKits.size(); ++i)
	{
		if (player.canISeeit(medKits[i].getBody()))
			window.draw(medKits[i].getBody());
	}
	if (player.canISeeit(astronaut.getBody()))
		window.draw(astronaut.getBody());
	for (unsigned int i = 0; i < strikers.size(); ++i)
	{
		window.draw(strikers[i].getBody());
	}
	for (unsigned int i = 0; i < explosions.size(); ++i)
	{
		window.draw(explosions[i].getBody());
	}
	player.draw(window);
	for (unsigned int i = 0; i < invaders.size(); ++i)
		invaders[i].draw(window);

	window.setView(mouseView); //mysz
	window.draw(myMouse);

	window.setView(hud); //interfejs
	outOfArea.draw(window);
	window.draw(score.getDrawable());
	window.draw(tracker.getBody());
	hpbar.drawBar(window);

	window.display();
}

void Gameplay::backToMenu()
{
	musicMenager->play(MusicMenager::trackName::MainMenu);
	newState = sn::MenuState;
}
