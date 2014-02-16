// EnemyFishObject.cpp
#include "stdafx.h"
#include "EnemyFishObject.h"
//
//EnemyFishObject::EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite)
//	: GameObject(p_xPosition, p_pxSprite) 
//{
//}
EnemyFishObject::EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite, Collider* p_pxCollider)
	: FishObject(p_xPosition, p_pxSprite,  p_pxCollider) 
{
	SetSpeed(50);
	SetState(Idle);
	StateTimer = 0;
}
EnemyFishObject::~EnemyFishObject()
{
	//Delete Sprite
	if(GetSprite() != nullptr)
	{
		delete  GetSprite();
	}
	
	//Delete Collider
	if(GetCollider() != nullptr)
	{
		delete  GetCollider();
	}
	
}

void EnemyFishObject::Update(float deltatime)
{
	SetVelocity(sf::Vector2f(0.0f, 0.0f));
	StateTimer++;
	if(StateTimer >= 500)
	{
		ChangeState();
		StateTimer = 0;
	}
	if(GetState() == Moving)
	{
		if(StateTimer > 250)
		{
			SetVelocity(sf::Vector2f(deltatime * -GetSpeed(), 0.0f) );
		}
		else
		{
			SetVelocity(sf::Vector2f(deltatime * GetSpeed(), 0.0f) );
		}
	}

	SetPosition( GetPosition() + GetVelocity() );

	if(HasCollider() )
	{
		m_pxCollider->SetPosition(GetPosition() );
	}
}

void EnemyFishObject::ChangeState()
{
	if(GetState() == Idle)
	{
		SetState(Moving);
	}
	else
	{
		SetState(Idle);
	}
}

void EnemyFishObject::SetSpawnPosition(sf::Vector2f p_xSpawnPosition)
{
	m_xSpawnPosition = p_xSpawnPosition;
}

sf::Vector2f EnemyFishObject::GetSpawnPosition(sf::Vector2f p_xSpawnPosition)
{
	return m_xSpawnPosition;
}

void EnemyFishObject::SetAttractRadius(float p_fAttractRadius)
{
	m_pxCollider->SetRadius(p_fAttractRadius);
}




