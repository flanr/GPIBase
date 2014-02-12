// EnemyFishObject.cpp
#include "stdafx.h"
#include "EnemyFishObject.h"
//
//EnemyFishObject::EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite)
//	: GameObject(p_xPosition, p_pxSprite) 
//{
//}
EnemyFishObject::EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite, Collider* p_pxCollider)
	: GameObject(p_xPosition, p_pxSprite,  p_pxCollider) 
{
}
EnemyFishObject::~EnemyFishObject()
{
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

void EnemyFishObject::Update(float deltatime)
{

	if(HasCollider() )
	{
		m_pxCollider->SetPosition(GetPosition() );
	}
	//ADD movement, AI and Animations here
}


