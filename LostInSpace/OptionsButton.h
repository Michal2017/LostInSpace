#pragma once

#include "IButton.h"

class OptionsButton : public IButton //przycisk w menu z ustawieniami, wyswietlajacy parametry ustawienia
{
public:
	OptionsButton(std::string value, sf::Font & font, int size);
	~OptionsButton();
	virtual void setPosition(sf::Vector2f position, bool center = false) override;
	virtual void setActive() override;
	virtual void setInactive() override;
	virtual sf::Text getDrawable() override { return button; }
	void updateValue(std::string newString);

private:
	sf::Text button;
};

