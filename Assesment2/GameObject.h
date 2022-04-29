#pragma once
#include "UpdatedObject.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <set>

class CGameObject : public CUpdatedObject
{
protected:
	friend class CDebugger;

public:
	//Refrencing variables
	std::set<std::string> m_strTags;

	//Transformation variables
	sf::Vector2f m_v2fPosition;
	sf::Vector2f m_v2fOrigin;
	sf::Vector2f m_v2fScale;
	float m_fRotation; //Don't use for objects with collision

	//Drawing variables
	sf::Texture m_texDraw;
	sf::Sprite m_sprDraw;
	float m_fNextFrameTimer;
	bool m_bVisible;

	//Collision variables
	sf::Rect<float> m_rectfHitbox; //The coordinates of m_rectfHitbox is using the object's local coordinates

	CGameObject();
	virtual ~CGameObject();

	const bool TagExists(const std::string _strTagName);
	const bool GetIsCollidable();

	bool AnimateSprite
	( 
		sf::Sprite& _Sprite,
		const unsigned int& _uiStartFrameColumn,
		const unsigned int& _uiStartFrameRow,
		const unsigned int& _uiFrameCount,
		const float& _fSecondsPerFrame,
		const float& _fDeltaTime,
		const int& _iCheckedFrame = -1
	);
	virtual void Update(sf::RenderWindow& _RenderWindow, float& _fDeltaTime);
};