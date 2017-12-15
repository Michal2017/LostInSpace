#include "Invader.h"

Invader::Invader(sf::Texture * texture, sf::Vector2f position, sf::Sound & copySound)
	: fire(copySound)
{
	body.setSize(sf::Vector2f(256.f, 256.f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	is90or270 = 0;
	dodgeDistance = 0.f;
	speed = 0.f;
	dodgeSpeed = 500.f;
	globalCd = 1.5f;
	fullAutoCd = 0.2f;
	hp = 10;
	whichBullet = 0;
	damage = 2;
}

Invader::~Invader()
{
}

void Invader::update(float dTime, sf::Vector2f spaceshipPosition, sf::Texture * bulletTexture)
{
	sf::Vector2f direction;
	sf::Vector2f dodgeDirection;
	sf::Vector2f bulletsDir;
	float length =
		sqrt((spaceshipPosition.x - body.getPosition().x) * (spaceshipPosition.x - body.getPosition().x) +
		(spaceshipPosition.y - body.getPosition().y) * (spaceshipPosition.y - body.getPosition().y));
	speed = 0.7f * length;
	direction.x = (spaceshipPosition.x - body.getPosition().x) / length;
	direction.y = (spaceshipPosition.y - body.getPosition().y) / length;
	bulletsDir = direction;
	if (is90or270 == 0) //90
	{
		dodgeDirection.x = -direction.y;
		dodgeDirection.y = direction.x;
	}
	else //270
	{
		dodgeDirection.x = direction.y;
		dodgeDirection.y = -direction.x;
	}
	direction.x *= speed * dTime;
	direction.y *= speed * dTime;
	body.move(direction);
	dodgeDirection.x *= dodgeSpeed * dTime;
	dodgeDirection.y *= dodgeSpeed * dTime;
	body.move(dodgeDirection);
	dodgeDistance += sqrt(dodgeDirection.x * dodgeDirection.x + dodgeDirection.y * dodgeDirection.y);
	if (dodgeDistance >= 1000.f)
	{
		dodgeDistance = 0.f;
		if (is90or270)
			is90or270 = false;
		else is90or270 = true;
	}
	float rotationAngle = atan2(body.getPosition().y - spaceshipPosition.y, body.getPosition().x - spaceshipPosition.x) * 180 / 3.14159265;
	body.setRotation(rotationAngle - 90.f);
	if (globalCd <= 0.f)
	{
		if (fire.getStatus() == sf::Sound::Stopped)
			fire.play();
		if (fullAutoCd <= 0.f)
		{
			whichBullet += 1;
			bullets.push_back(Projectile(bulletTexture, rotationAngle - 90.f, body.getPosition(), bulletsDir, 2000.f, 10));
			fullAutoCd = 0.2f;
		}
		else fullAutoCd -= dTime;
		if (whichBullet == 3)
		{
			whichBullet = 0;
			globalCd = 1.5f;
		}
	}
	else globalCd -= dTime;

	for (unsigned int i = 0; i < bullets.size(); ++i)
	{
		bullets[i].update(dTime);
		if (canISeeit(bullets[i].getBody()) == false)
		{
			bullets.erase(bullets.begin() + i);
			--i;
			continue;
		}
	}
}

void Invader::draw(sf::RenderWindow & window)
{
	for (unsigned int i = 0; i < bullets.size(); ++i)
		window.draw(bullets[i].getBody());
	window.draw(body);
}

bool Invader::didItHit(sf::RectangleShape object)
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

bool Invader::canISeeit(sf::RectangleShape object)
{
	if (object.getPosition().x > (body.getPosition().x + 1920 + object.getSize().x) ||
		object.getPosition().x < (body.getPosition().x - 1920 - object.getSize().x) ||
		object.getPosition().y >(body.getPosition().y + 1080 + object.getSize().y) ||
		object.getPosition().y < (body.getPosition().y - 1080 - object.getSize().y))
		return false;
	return true;
}
