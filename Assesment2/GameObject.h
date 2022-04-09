#include <SFML/Graphics.hpp>
#include <string>
#include <deque>
#include <set>

#pragma once
class CLevel;

class CGameObject
{
protected:
	friend class CLevel;
	friend class CDebugger;

	//Refrencing variables
	CLevel* m_pLevel;
	std::set<std::string> m_strTags;
	bool m_bDeleteGameObject;

	//Transformation variables
	sf::Vector2f m_v2fPosition;
	sf::Vector2f m_v2fOrigin;
	sf::Vector2f m_v2fScale;
	float m_fRotation; //Don't use for objects with collision

	//Collision variables
	sf::Rect<float> m_rectfHitbox; //The coordinates of m_rectfHitbox is using the object's local coordinates

	//Drawing variables
	sf::Texture m_texDraw;
	sf::Sprite m_sprDraw;
	float m_fNextFrameTimer;
	bool m_bVisible;

public:
	//Constructors
	CGameObject();
	virtual ~CGameObject();

	//Refrencing methods
	void AddTag(const std::string _strTag);
	const bool TagExists(const std::string _strTagName);
	virtual void DeleteGameObject();

	//Transformation methods
	const sf::Vector2f GetPosition();
	void SetPosition(const sf::Vector2f _v2fNewPosition);
	const sf::Vector2f GetOrigin();
	const sf::Vector2f GetScale();
	void SetScale(const sf::Vector2f _v2fNewScale);
	const float GetRotation();
	void SetRotation(const float _fDegrees);

	const bool GetIsCollidable();
	const sf::Rect<float> GetHitbox();

	//Drawing methods
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