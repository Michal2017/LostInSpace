#include "Gameplay.h"

Gameplay::Gameplay(sf::Font & font, float fxVolume, float musicVolume, int width, int height, MusicMenager & musicMenager)
	: score(font), outOfArea(originalWidth, font, 400, "POZA OBSZAREM", 50)
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

		astronaut.update(deltaTime);

		window.setView(view); //view jest potrzebne, aby poprawnie obracac statkiem w kiedunku kursora
		player.update(deltaTime, window, &greenProjectileTexture, &bulletFired);

		if (isColliding(player.getBody(), astronaut.getBody()) && astronautCollected.getStatus() == sf::Sound::Stopped) //sprawdzenie czy statek uratowal astronaute
		{
			int numberOfStrikers = 3;
			astronautCollected.play();
			player.addScore();
			score.update(player.showScore());
			numberOfStrikers += (int)(player.showScore() / 5);
			astronaut.relocate();
			for (int i = 0; i < numberOfStrikers; ++i) //utworzenie nowych obiektow typu "striker"
			{
				float a = player.getPosition().x, b = player.getPosition().y, r = 970.f, y;
				int ai = a;
				float x = rand() % 1920 + (ai - 970);
				if (i % 2 == 0)
					y = (2.f * b - sqrtf(4.f * r * r - (4.f * (x - a) * (x - a)))) / 2.f;
				else y = (2.f * b + sqrtf(4.f * r * r - (4.f * (x - a) * (x - a)))) / 2.f;
				strikers.push_back(Striker(&strikerTexture, sf::Vector2f(x, y)));
				x = rand() % 10001;
				y = rand() % 10001;
				medKits.push_back(MedKit(&medKitTexture, sf::Vector2f(x, y)));
			}
		}

		for (unsigned int i = 0; i < strikers.size(); ++i) //sprawdzanie kolizji pomiedzy statkiem gracza, a przeciwnikami typu "striker"
		{
			strikers[i].update(player.getPosition(), deltaTime);
			if (isColliding(strikers[i].getBody(), player.getBody()))
			{
				damageTaken.play();
				player.gotDamaged(strikers[i].dealDamage());
				hpbar.update(player.showHP());
				strikers.erase(strikers.begin() + i);
				--i;
			}
		}
		for (unsigned int i = 0; i < strikers.size(); ++i) //sprawdzanie czy gracz trafia pociskami przeciwnikow typu "striker"
		{
			if (player.didItHit(strikers[i].getBody()))
			{
				strikers[i].gotDamaged();
				if (strikers[i].showHp() <= 0)
				{
					explosionSounds.push_back(sf::Sound(exploded));
					explosionSounds.back().play();
					explosions.push_back(Animation(&explosionTexture, 0.001f, 8, 8, strikers[i].getBody().getPosition()));
					strikers.erase(strikers.begin() + i);
					--i;
				}
			}
		}

		invaderSpawnTime += deltaTime; //aktualizowanie czasu, po ktorym maja sie pojawiac przeciwnicy typu "invader"
		if (invaderSpawnTime >= 15.f) //tworzenie nowego obiektu typu "invader" co 15sekund
		{
			invaderSpawn.play();
			invaderSpawnTime = 0.f;
			float a = player.getPosition().x, b = player.getPosition().y, r = 970.f, y;
			int ai = a;
			float x = rand() % 1920 + (ai - 970);
			y = (2.f * b - sqrtf(4.f * r * r - (4.f * (x - a) * (x - a)))) / 2.f; //losowa pozycja na osi XY na okregu wokol statku gracza
			invaders.push_back(Invader(&invaderTexture, sf::Vector2f(x, y), spaceGun));
		}
		for (unsigned i = 0; i < invaders.size(); ++i) //aktualizowanie wszystkich przeciwnikow typu "invader"
		{
			invaders[i].update(deltaTime, player.getPosition(), &redProjectileTexture);
		}
		for (unsigned i = 0; i < invaders.size(); ++i) //sprawdzanie czy gracz trafia pociskami obiekty typu "invader"
		{
			if (player.didItHit(invaders[i].getBody()))
			{
				invaders[i].gotDamaged();
				if (invaders[i].showHP() <= 0)
				{
					explosionSounds.push_back(sf::Sound(exploded));
					explosionSounds.back().play();
					explosions.push_back(Animation(&explosionTexture, 0.001f, 8, 8, invaders[i].getBody().getPosition()));
					invaders.erase(invaders.begin() + i);
					--i;
				}
			}
		}
		for (unsigned i = 0; i < invaders.size(); ++i) //sprawdzanie czy przeciwnicy typu "invader" trafiaja pociskami gracza
		{
			if (invaders[i].didItHit(player.getBody()))
			{
				player.gotDamaged(invaders[i].dealDamage());
				hpbar.update(player.showHP());
			}
		}

		for (unsigned int i = 0; i < medKits.size(); ++i) //sprawdzenie czy gracz zebral apteczke
		{
			if (isColliding(player.getBody(), medKits[i].getBody()))
			{
				if (player.gotHealed(medKits[i].getPower()))
				{
					medKitTaken.play();
					hpbar.update(player.showHP());
					explosions.push_back(Animation(&fogTexture, 0.05f, 3, 5, medKits[i].getBody().getPosition()));
					medKits.erase(medKits.begin() + i);
					--i;
					continue;
				}
			}
			medKits[i].update(deltaTime);
		}

		outOfArea.update(deltaTime, player.getPosition(), sf::Vector2f(10000.f, 10000.f));

		hpbar.animate(deltaTime);

		tracker.update(player.getBody(), astronaut.getBody());

		for (unsigned int i = 0; i < explosions.size(); ++i) //aktualizowanie i usuwanie animacji wybuchow
		{
			if (explosions[i].update(deltaTime))
				explosions.erase(explosions.begin() + i);
		}

		if (explosionSounds.size() >= 1 && explosionSounds.front().getStatus() == sf::Sound::Stopped) //usuwanie z pamieci dzwiekow wybuchow
			explosionSounds.erase(explosionSounds.begin());

		if (player.showHP() == 0) //jezeli gracz stracil wszystkie punkty zdrowia
		{
			newState = sn::MenuState;
			musicMenager->play(MusicMenager::trackName::MainMenu);
		}

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
