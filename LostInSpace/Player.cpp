#include "Player.h"

Player::Player()
{

}

Player::Player(sf::Texture * playerTexture, sf::Texture * engineTexture)
{
	rotationAngle = 0.0f;
	body.setSize(sf::Vector2f(170.0f, 102.f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(5000.0f, 5000.0f);
	body.setTexture(playerTexture);
	sf::Vector2f movement(0.0f, 0.0f);
	movementX = 0.0f;
	movementY = 0.0f;
	speed = 10.0f;
	score = 0;
	cooldown = 0.0f;
	hp = 100;
	engineFrame.width = engineTexture->getSize().x / 5;
	engineFrame.height = engineTexture->getSize().y;
	engineFrame.left = 0;
	engineFrame.top = 0;
	engine.setSize(sf::Vector2f((float)engineFrame.width, (float)engineFrame.height));
	engine.setOrigin(engine.getSize().x / 2.0f, 0.f);
	engine.setPosition(5000.0f, 5000.0f);
	engine.setTexture(engineTexture);
	engine.setTextureRect(engineFrame);
	animationCooldown = 0.05f;
}

Player::~Player()
{
}

void Player::update(float deltaTime, sf::RenderWindow & window, sf::Texture *projectileTexture, sf::Sound *bulletFired)
{
	float length;
	float maxVelocity = 10.0f;
	bool isPressedX = false;
	bool isPressedY = false;

	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosition = window.mapPixelToCoords(pixelPos);
	rotationAngle = atan2(body.getPosition().y - mousePosition.y, body.getPosition().x - mousePosition.x) * 180 / 3.14159265;
	body.setRotation(rotationAngle - 90.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (movementY < maxVelocity) // 10 - max velocity
			movementY += 6.0f * deltaTime;
		isPressedY = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (movementY > -maxVelocity)
			movementY -= 6.0f * deltaTime;
		isPressedY = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (movementX < maxVelocity)
			movementX += 6.0f * deltaTime;
		isPressedX = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (movementX > -maxVelocity)
			movementX -= 6.0f * deltaTime;
		isPressedX = true;
	}
	if (isPressedX == false && movementX != 0.0f)
	{
		if (movementX > 0.0f)
			movementX -= 1.5f * deltaTime;
		else movementX += 1.5f * deltaTime;
	}
	if (isPressedY == false && movementY != 0.0f)
	{
		if (movementY > 0.0f)
			movementY -= 1.5f * deltaTime;
		else movementY += 1.5f * deltaTime;
	}
	length = sqrt(movementX * movementX + movementY * movementY);
	if (length == 0.0f)
		length = 1.0f;
	movement.y = movementY;
	movement.x = movementX;
	body.move(movement);

	bool isEngineOn = isPressedX + isPressedY;
	engineUpdate(isEngineOn, deltaTime, rotationAngle);

	if (cooldown > 0.f)
		cooldown -= deltaTime;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown <= 0.f)
	{
		cooldown = 0.25f;
		sf::Vector2f direction;
		float length2 =
			sqrt((mousePosition.x - body.getPosition().x) * (mousePosition.x - body.getPosition().x) + (mousePosition.y - body.getPosition().y) * (mousePosition.y - body.getPosition().y));
		direction.x = (mousePosition.x - body.getPosition().x) / length2;
		direction.y = (mousePosition.y - body.getPosition().y) / length2;
		bullets.push_back(Projectile(projectileTexture, rotationAngle - 90.f, body.getPosition(), direction, 1500.f, 1));
		bulletFired->play();
	}

	for (unsigned int i = 0; i < bullets.size(); ++i)
	{
		bullets[i].update(deltaTime);
		if (canISeeit(bullets[i].getBody()) == false)
		{
			bullets.erase(bullets.begin() + i);
			--i;
			continue;
		}
	}
}

void Player::draw(sf::RenderWindow & window)
{
	for (unsigned int i = 0; i < bullets.size(); ++i)
		window.draw(bullets[i].getBody());
	window.draw(engine);
	window.draw(body);
}

bool Player::canISeeit(sf::RectangleShape object) //czy obiekt jest widoczny na ekranie
{
	if (object.getPosition().x >(body.getPosition().x + 910 + object.getSize().x) ||
		object.getPosition().x < (body.getPosition().x - 910 - object.getSize().x) ||
		object.getPosition().y >(body.getPosition().y + 540 + object.getSize().y) ||
		object.getPosition().y < (body.getPosition().y - 540 - object.getSize().y))
		return false;
	return true;
}

bool Player::canISeeit(sf::Sprite object) //czy obiekt jest widoczny na ekranie
{
	if (object.getPosition().x >(body.getPosition().x + 960) ||
		object.getPosition().x < (body.getPosition().x - 1160) ||
		object.getPosition().y >(body.getPosition().y + 540) ||
		object.getPosition().y < (body.getPosition().y - 660))
		return false;
	return true;
}

void Player::gotDamaged(int dmg)
{
	hp -= dmg;
	if (hp < 0)
		hp = 0;
}

bool Player::gotHealed(int heal) //zwraca falsz gdy gracz ma pelny pasek zycia, aby nie mogl wtedy brac apteczek
{
	if (hp == 100)
		return false;
	hp += heal;
	if (hp > 100)
		hp = 100;
	return true;
}

bool Player::didItHit(sf::RectangleShape object) //zwraca prawde, jezeli pociski trafily obiekt
{
	for (unsigned int i = 0; i < bullets.size(); ++i)
	{
		if (isColliding(bullets[i].getBody(), object))
		{
			bullets.erase(bullets.begin() + i);
			return true;
		}
	}
	return false;
}

void Player::engineUpdate(bool isEngineOn, float dTime, float rotationAngle) //zarzadza animacja "wydechu" statku
{
	animationCooldown -= dTime;
	if (isEngineOn && animationCooldown <= 0.f)
	{
		animationCooldown = 0.05f;
		engineFrame.left += engineFrame.width;
		if (engineFrame.left >= 435)
			engineFrame.left -= 2 * engineFrame.width;
	}
	else if (isEngineOn == false && animationCooldown <= 0.f)
	{
		animationCooldown = 0.05f;
		engineFrame.left -= engineFrame.width;
		if (engineFrame.left < 0)
			engineFrame.left += engineFrame.width;
	}
	engine.setTextureRect(engineFrame);
	engine.setRotation(rotationAngle - 90.f);
	engine.move(movement);
}
