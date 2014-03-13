//PowerupObject.cpp

#include "stdafx.h"
#include "PowerupObject.h"

PowerupObject::PowerupObject(eType p_eUpgrade, sf::Vector2f p_xPosition, sf::Sprite* p_pxSprite, Collider* p_pxCollider)
: GameObject(p_xPosition,  p_pxSprite, p_pxCollider) 
{
	m_xStartPos = p_xPosition;
	bMovingUp = true;
	m_fMovement = 0.1f;
	SetPowerUpType(p_eUpgrade);
	
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

	if(m_pxCollider != nullptr )
	{
		m_pxCollider->SetPosition(GetPosition() );
	}
}

void PowerupObject::OnCollision(GameObject* p_other, sf::Vector2f& p_Offset)
{
	if (GetCollider() != nullptr)
	{
		if (p_other->GetType() == "Player")
		{
			this->m_pxCollider = nullptr;
			m_isDestroyed = true;
		}
	}
}

void PowerupObject::SetPowerUpType(eType p_powerup)
{
	for(int i = 0; i < TYPECOUNT; i++)
	{
		m_Type[i] = false;
	}
	m_Type[p_powerup] = true;
}

eType PowerupObject::GetPowerUpType()
{
	for(int i = 0; i < TYPECOUNT; i++)
	{
		if(m_Type[i] == true)
		{
			return (eType)i ;
		}
	}
	return (eType)0;
}