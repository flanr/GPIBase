// FishObject
#include "stdafx.h"


FishObject::FishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite , Collider* p_Collider )
	: GameObject(p_Position, p_Sprite, p_Collider)
{
	m_fDashpower = 0.0f;
	m_fSpeed = 0.0f; 
	m_Velocity = sf::Vector2f(0.0f, 0.0f);

	for(int i = 0; i < StateCount; i++)
	{
		m_CurrentState[i] = false;
	}
	m_CurrentState[Idle] = true;

};

void FishObject::SetState(eState p_State)
{
	for(int i = 0; i < StateCount; i++)
	{
		if(p_State == i)
		{
			m_CurrentState[i] = true;
		}
		else 
		{
			m_CurrentState[i] = false;
		}
	}
}

int FishObject::GetState()
{
	for(int i = 0; i < StateCount; i++)
	{
		if(m_CurrentState[i] == true)
		{
			return i;
		}
	}
	return 0;
}

void FishObject::SetDirection(eDirection p_Direction)
{
	for(int i = 0; i < DirectionCount; i++)
	{
		if(p_Direction == i)
		{
			m_Direction[i] = true;
		}
		else 
		{
			m_Direction[i] = false;
		}
	}
}
int FishObject::GetDirection()
{
	for(int i = 0; i < DirectionCount; i++)
	{
		if(m_Direction[i] == true)
		{
			return i;
		}
	}
	return 0;
}

void FishObject::SetVelocity(sf::Vector2f p_Velocity)
{
	m_Velocity = p_Velocity;
}

sf::Vector2f FishObject::GetVelocity()
{
	return m_Velocity;
}


void FishObject::SetSpeed(float p_fPlayerSpeed)
{
	m_fSpeed = p_fPlayerSpeed;
}
float FishObject::GetSpeed()
{
	return m_fSpeed;
}

void FishObject::SetDashPower(float p_fDashpower)
{
	m_fDashpower = p_fDashpower;
}
float FishObject::GetDashPower()
{
	return m_fDashpower;
}