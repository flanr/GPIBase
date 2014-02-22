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
	SetState(Moving);
	m_iStateTimer = 0;
	//SetScale(0.2f);
	//m_pxCollider->SetExtention(m_pxCollider->GetExtension()*GetScale());
}
EnemyFishObject::~EnemyFishObject()
{
	//Delete Sprite
	if(GetSprite() != nullptr)
	{
		delete  GetSprite();
	}
	
	////Delete Collider
	//if(GetCollider() != nullptr)
	//{
	//	delete  GetCollider();
	//}
	//
}

void EnemyFishObject::Update(float deltatime)
{

	SetVelocity(sf::Vector2f(0.0f, 0.0f));
	m_iStateTimer++;
	if(m_iStateTimer >= 500)
	{
		ChangeState();
		m_iStateTimer = 0;
	}
	if(GetState() == Moving)
	{
		if(m_iStateTimer > 250)
		{
			SetVelocity(sf::Vector2f(deltatime * -GetSpeed(), 0.0f) );
			//SetScale(GetScale());
			FlipXLeft(1.0f);
			
		}
		else
		{
			SetVelocity(sf::Vector2f(deltatime * GetSpeed(), 0.0f) );
			//SetScale(GetScale());
			FlipXRight(1.f);
			
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




