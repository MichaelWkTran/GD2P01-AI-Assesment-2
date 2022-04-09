#include "GameObject.h"
//#include <SFML/Graphics.hpp>
//#include <string>
//#include <deque>
//#include <set>

//Constructors
CGameObject::CGameObject()
{
	//Refrencing variables
	m_pLevel = nullptr;
	m_bDeleteGameObject = false;

	//Transformation variables
	m_v2fScale.x = 1.0f;
	m_v2fScale.y = 1.0f;
	m_fRotation = 0.0f; //Don't use for objects with collision

	//Drawing variables
	m_texDraw.loadFromFile("Assets/Sprites/DefaultSprite.png");
	m_texDraw.setRepeated(true);
	m_sprDraw.setTexture(m_texDraw);
	m_fNextFrameTimer = 0;
	m_bVisible = true;
}

/*virtual */CGameObject::~CGameObject() {}

//Refrencing methods
void CGameObject::AddTag(const std::string _strTag)
{
	m_strTags.insert(_strTag);
}

const bool CGameObject::TagExists(const std::string _strTagName)
{
	if (m_strTags.find(_strTagName) != m_strTags.end()) return true;
	else return false;
}

/*virtual */void CGameObject::DeleteGameObject()
{
	m_bDeleteGameObject = true;
}

//Transformation methods
const sf::Vector2f CGameObject::GetPosition()
{
	return m_v2fPosition;
}

void CGameObject::SetPosition(const sf::Vector2f _v2fNewPosition)
{
	m_v2fPosition = _v2fNewPosition;
}

const sf::Vector2f CGameObject::GetOrigin()
{
	return m_v2fOrigin;
}

const sf::Vector2f CGameObject::GetScale()
{
	return m_v2fScale;
}

void CGameObject::SetScale(const sf::Vector2f _v2fNewScale)
{
	m_v2fScale = _v2fNewScale;
}

const float CGameObject::GetRotation()
{
	return m_fRotation;
}

void CGameObject::SetRotation(const float _fDegrees)
{
	m_fRotation = _fDegrees;
}

//Collision methods
const bool CGameObject::GetIsCollidable()
{
	return m_rectfHitbox != sf::Rect<float>();
}

const sf::Rect<float> CGameObject::GetHitbox()
{
	return m_rectfHitbox;
}

//Drawing methods
bool CGameObject::AnimateSprite
( 
	sf::Sprite& _Sprite, 
	const unsigned int& _uiStartFrameColumn, 
	const unsigned int& _uiStartFrameRow, 
	const unsigned int& _uiFrameCount, 
	const float& _fSecondsPerFrame, 
	const float& _fDeltaTime,
	const int& _iCheckedFrame/* = -1*/
)
{
	//Frame count treats 0 as the first frame so if the animation has 2 frames, set it to 1
	bool bOnCheckedFrame = false;

	m_fNextFrameTimer += _fDeltaTime;

	//Start animation with its first frame of the animation
	if (_Sprite.getTextureRect().top != _uiStartFrameRow * _Sprite.getTextureRect().height)
	{
		_Sprite.setTextureRect
		(
			sf::Rect<int>
			(
				_uiStartFrameColumn * _Sprite.getTextureRect().width,
				_uiStartFrameRow * _Sprite.getTextureRect().height, 
				_Sprite.getTextureRect().width, 
				_Sprite.getTextureRect().height
			)
		);

		m_fNextFrameTimer = 0;
	}

	//Animate the sprite
	if (m_fNextFrameTimer > _fSecondsPerFrame)
	{
		m_sprDraw.setTextureRect
		(
			sf::Rect<int>
			(
				_Sprite.getTextureRect().left + _Sprite.getTextureRect().width,
				_Sprite.getTextureRect().top,
				_Sprite.getTextureRect().width,
				_Sprite.getTextureRect().height
			)
		);
		
		m_fNextFrameTimer = 0;
	}

	//Whether the animation has reached its end
	if (_iCheckedFrame == -1)
	{
		if (m_sprDraw.getTextureRect().left > (int)_uiFrameCount * _Sprite.getTextureRect().width)
			bOnCheckedFrame = true;
	}
	//Whether the frame index of the animation is the same as _iCheckedFrame
	else
	{
		if (m_sprDraw.getTextureRect().left == _uiFrameCount * _Sprite.getTextureRect().width)
			bOnCheckedFrame = true;
	}

	//Repeat to the first frame if there are no frames left
	if (_Sprite.getTextureRect().left > (int)((_uiStartFrameColumn + _uiFrameCount) * _Sprite.getTextureRect().width))
	{
		_Sprite.setTextureRect
		(
			sf::Rect<int>
			(
				_uiStartFrameColumn * _Sprite.getTextureRect().width,
				_uiStartFrameRow * _Sprite.getTextureRect().height, 
				_Sprite.getTextureRect().width, 
				_Sprite.getTextureRect().height
			)
		);
	}

	//Return whether the end of the animation has been reached or the animation is on _iCheckedFrame
	return bOnCheckedFrame;
}

/*virtual */void CGameObject::Update(sf::RenderWindow& _RenderWindow, float& _fDeltaTime)
{
	m_sprDraw.setPosition(m_v2fPosition);
	m_sprDraw.setOrigin(m_v2fOrigin);
	m_sprDraw.setScale(m_v2fScale);
	m_sprDraw.setRotation(m_fRotation);

	_RenderWindow.draw(m_sprDraw);
}