#include "Button.h"
#include <iostream>
//#include "GameObject.h"
//#include <SFML/Graphics.hpp>
//#include <string>

bool CButton::m_bMouseButtonHeld = false;

CButton::CButton(std::string _strButtonImageDirectory, ButtonType _eButtonType/* = ButtonType::STANDARD*/, CButton** _pToggledButton/* = nullptr*/)
{
	//GameObject Variables---------------------------------------------------------------------------------
	//Drawing Variables
	m_texDraw.loadFromFile(_strButtonImageDirectory);
	m_sprDraw.setTextureRect(sf::Rect<int>(0, 0, (int)(m_texDraw.getSize().x / 4), (int)(m_texDraw.getSize().y)));

	//Collision Variables
	m_rectfHitbox = sf::Rect<float>(0.0f, 0.0f, (float)(m_sprDraw.getTextureRect().width), (float)(m_sprDraw.getTextureRect().height));

	//Button Variables-------------------------------------------------------------------------------------
	//Button Variables
	m_eButtonType = _eButtonType;
	m_bPressed = false;
	m_ButtonState = -1;
	m_pToggledButton = _pToggledButton;
}

void CButton::SetOrigin(sf::Vector2f _v2fOrigin)
{
	m_v2fOrigin = _v2fOrigin;
}

sf::Vector2u CButton::GetSize() const
{
	return sf::Vector2u((unsigned int)m_sprDraw.getTextureRect().width, (unsigned int)m_sprDraw.getTextureRect().height);
}

bool CButton::Pressed()
{
	return m_ButtonState == 0;
}

bool CButton::Held()
{
	return m_ButtonState == 1;
}

bool CButton::Released()
{
	return m_ButtonState == 2;
}

bool CButton::Hover(sf::RenderWindow& _RenderWindow)
{
	return _RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(_RenderWindow)).x >= m_v2fPosition.x + m_rectfHitbox.left &&
		   _RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(_RenderWindow)).x <= m_v2fPosition.x + m_rectfHitbox.left + m_rectfHitbox.width &&
		   _RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(_RenderWindow)).y >= m_v2fPosition.y + m_rectfHitbox.top &&
		   _RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(_RenderWindow)).y <= m_v2fPosition.y + m_rectfHitbox.top + m_rectfHitbox.height;
}

void CButton::Update(sf::RenderWindow& _RenderWindow, float& _fDeltaTime)
{
	m_ButtonState = -1;
	m_rectfHitbox.left = -m_v2fOrigin.x;
	m_rectfHitbox.top = -m_v2fOrigin.y;

	//Check whether the button has pressed the button or not
	if (CButton::Hover(_RenderWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//When the button is first pressed but not held
			if (!m_bMouseButtonHeld)
			{
				switch (m_eButtonType)
				{
				case ButtonType::SWITCH:
					m_bPressed = !m_bPressed;
					break;
				case ButtonType::TOGGLE:
					if (*m_pToggledButton != this) { *m_pToggledButton = this; }
					break;
				}

				m_ButtonState = 0; 
			}

			if (m_eButtonType == ButtonType::STANDARD) { m_bPressed = true; }
			if (m_ButtonState == -1) { m_ButtonState = 1; }
		}
		else
		{
			//When the button is released
			m_bPressed = false;
			if (m_ButtonState == -1 && m_bMouseButtonHeld)
			{
				m_ButtonState = 2;
			}
		}
	}
	else
	{
		//When the mouse is released
		m_bPressed = false;
	}
	
	//Check whether the mouse button is held or not
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_bMouseButtonHeld) { m_bMouseButtonHeld = true; }
	}
	else
	{
		m_bMouseButtonHeld = false;
	}

	//Set the transformation of the GameObject
	m_sprDraw.setPosition(m_v2fPosition);
	m_sprDraw.setOrigin(m_v2fOrigin);
	m_sprDraw.setScale(m_v2fScale);
	m_sprDraw.setRotation(m_fRotation);

	//Set the m_sprDraw to its first frame 
	m_sprDraw.setTextureRect(sf::Rect<int>(0, m_sprDraw.getTextureRect().top, m_sprDraw.getTextureRect().width, m_sprDraw.getTextureRect().height));
	
	//Draw the base of the button and its icon
	for (int i = 0; i < 2; i++)
	{
		_RenderWindow.draw(m_sprDraw);
		m_sprDraw.setTextureRect
		(
			sf::Rect<int>
			(
				m_sprDraw.getTextureRect().left + m_sprDraw.getTextureRect().width,
				m_sprDraw.getTextureRect().top,
				m_sprDraw.getTextureRect().width,
				m_sprDraw.getTextureRect().height
			)
		);
	}

	/*Determine how a button will change from the pressed or released overlay 
	  depending on it's ButtonType which*/
	switch (m_eButtonType)
	{
	case ButtonType::STANDARD:
	case ButtonType::SWITCH:
		if (m_bPressed)
		{
			//Set the m_sprDraw to its pressed or last frame 
			m_sprDraw.setTextureRect
			(
				sf::Rect<int>
				(
					3 * m_sprDraw.getTextureRect().width,
					m_sprDraw.getTextureRect().top,
					m_sprDraw.getTextureRect().width,
					m_sprDraw.getTextureRect().height
				)
			);
		}
		else
		{
			//Set the m_sprDraw to its unpressed or 3rd frame 
			m_sprDraw.setTextureRect
			(
				sf::Rect<int>
				(
					2 * m_sprDraw.getTextureRect().width,
					m_sprDraw.getTextureRect().top,
					m_sprDraw.getTextureRect().width,
					m_sprDraw.getTextureRect().height
				)
			);
		}
		break;
	case ButtonType::TOGGLE:
		if (*m_pToggledButton == this)
		{
			//Set the m_sprDraw to its pressed or last frame 
			m_sprDraw.setTextureRect
			(
				sf::Rect<int>
				(
					3 * m_sprDraw.getTextureRect().width,
					m_sprDraw.getTextureRect().top,
					m_sprDraw.getTextureRect().width,
					m_sprDraw.getTextureRect().height
				)
			);
		}
		else
		{
			//Set the m_sprDraw to its unpressed or 3rd frame 
			m_sprDraw.setTextureRect
			(
				sf::Rect<int>
				(
					2 * m_sprDraw.getTextureRect().width,
					m_sprDraw.getTextureRect().top,
					m_sprDraw.getTextureRect().width,
					m_sprDraw.getTextureRect().height
				)
			);
		}
		break;
	}
	_RenderWindow.draw(m_sprDraw);

	//Set the m_sprDraw to its first frame
	m_sprDraw.setTextureRect(sf::Rect<int>(0, m_sprDraw.getTextureRect().top, m_sprDraw.getTextureRect().width, m_sprDraw.getTextureRect().height));
}