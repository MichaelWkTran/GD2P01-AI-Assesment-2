#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <string>

#pragma once
enum class ButtonType
{
	STANDARD,
	SWITCH,
	TOGGLE
};

class CButton : public CGameObject
{
private:
	//Button Variables
	ButtonType m_eButtonType;
	bool m_bPressed;
	int m_ButtonState;
	CButton** m_pToggledButton;

public:
	static bool m_bMouseButtonHeld;

	CButton(std::string _strButtonImageDirectory, ButtonType _eButtonType = ButtonType::STANDARD, CButton** _pToggledButton = nullptr);

	void SetOrigin(sf::Vector2f _v2fOrigin);
	sf::Vector2u GetSize() const;

	bool Pressed();
	bool Held();
	bool Released();
	bool Hover(sf::RenderWindow& _RenderWindow);

	void Update(sf::RenderWindow& _RenderWindow, float& _fDeltaTime);
};