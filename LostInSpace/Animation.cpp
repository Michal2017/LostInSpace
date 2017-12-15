#include "Animation.h"

Animation::Animation(sf::Texture * texture, float time, int rows, int columns, sf::Vector2f position)
{
	this->time = time;
	this->rows = rows - 1;
	row = 0;
	this->columns = columns - 1;
	column = 0;
	totalTime = 0.f;
	image.width = texture->getSize().x / columns;
	image.height = texture->getSize().y / rows;
	image.left = 0;
	image.top = 0;
	body.setTexture(texture);
	body.setSize(sf::Vector2f((float)image.width, (float)image.height));
	body.setOrigin((float)image.width / 2, (float)image.height / 2);
	body.setTextureRect(image);
	body.setPosition(position);
}

Animation::~Animation()
{
}

bool Animation::update(float time) //true gdy animacja sie skonczy
{
	totalTime += time;
	if (totalTime >= this->time)
	{
		totalTime -= this->time;
		row++;
		if (row > rows)
		{
			row = 0;
			column++;
			if (column > columns)
				return true;
		}
		image.left = image.width * row;
		image.top = image.height * column;
		body.setTextureRect(image);
	}
	return false;
}