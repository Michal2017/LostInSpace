#pragma once

#include "MenuButton.h"

class OptionsButton : public MenuButton //przycisk w menu z ustawieniami, wyswietlajacy parametry ustawienia
{
public:
	OptionsButton(std::string text, std::string valueS, sf::Font & font, int size); //value - wartosc, ktora mozna zmienic
	~OptionsButton();
	virtual void setPosition(sf::Vector2f position, sf::Vector2f position2, bool center = false);
	void setActive();
	void setInactive();
	void update(std::string valueS);
	void draw(sf::RenderWindow & window); //rysuje obiekt

private:
	sf::Text value;
};

