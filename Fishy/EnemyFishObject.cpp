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
}
void EnemyFishObject::SetAttractRadius(float p_fAttractRadius)
{
}

void EnemyFishObject::Update(float deltatime)
{
}


