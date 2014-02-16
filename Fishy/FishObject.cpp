// FishObject
#include "stdafx.h"


FishObject::FishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite , Collider* p_Collider )
	: GameObject(p_Position, p_Sprite, p_Collider)
{
	m_fAttackpower = 0.0f;
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
		m_CurrentState[i] = false;
	}

	m_CurrentState[p_State] = true;
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
		m_Direction[i] = false;
	}
	m_Direction[p_Direction] = true;
}

eDirection FishObject::GetDirection()
{
	for(int i = 0; i < DirectionCount; i++)
	{
		if(m_Direction[i] == true)
		{
			return (eDirection)i ;
		}
	}
	return FacingRight;
}

void FishObject::SetVelocityX(float p_VelocityX)
{
	m_Velocity.x = p_VelocityX;
}
void FishObject::SetVelocityY(float p_VelocityY)
{
	m_Velocity.y = p_VelocityY;
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

void FishObject::SetAttackPower(float p_fAttackpower)
{
	m_fAttackpower = p_fAttackpower;
}
float FishObject::GetAttackPower()
{
	return m_fAttackpower;
}