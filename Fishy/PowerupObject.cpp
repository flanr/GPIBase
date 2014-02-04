//PowerupObject.cpp

#include "stdafx.h"
#include "PowerupObject.h"

PowerupObject::PowerupObject(eType p_eUpgrade, sf::Vector2f p_xPosition, BoxCollider* p_pxBoxCollider, sf::Sprite* p_pxSprite)
: GameObject(p_xPosition, p_pxBoxCollider, p_pxSprite) 
{
	m_xStartPos = p_xPosition;
	bMovingUp = true;
	m_fMovement = 0.1f;
	m_eUpgrade = p_eUpgrade;
	
}
PowerupObject::~PowerupObject()
{
}

eType GetType();

void PowerupObject::SetIdleMovement(float p_fMovement)
{
	m_fMovement = p_fMovement;
}
/*void SetGlowEffect()
{
unknown
}*/

void PowerupObject::Update(float p_fDeltatime)
{
	if(bMovingUp)
	{
		if(m_xStartPos.y - GetPosition().y >= 5.0f)
		{
			bMovingUp = false;
		}
		else
		{
			SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y - m_fMovement * p_fDeltatime) );
		}
	}
	else
	{
		if(m_xStartPos.y - GetPosition().y <= -5.0f)
		{
			bMovingUp = true;
		}
		else
		{
			SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y + m_fMovement * p_fDeltatime) );
		}
	}
}