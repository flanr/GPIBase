//GameObject.cpp
#include "stdafx.h"

#include "GameObject.h"

//#include "Collider.h"

//GameObject::GameObject()
//{
//}
//
//GameObject::GameObject(sf::Vector2f p_xPosition, sf::Sprite * p_pxSprite)
//: m_xPosition(p_xPosition), m_pxSprite(p_pxSprite)
//{
//	m_bDestroyed = false;
//}

GameObject::GameObject(sf::Vector2f p_xPosition, sf::Sprite * p_pxSprite, Collider * p_pxCollider)
: m_xPosition(p_xPosition), m_pxSprite(p_pxSprite), m_pxCollider(p_pxCollider)
{
	m_bDestroyed = false;
}

GameObject::~GameObject()
{
}

sf::Vector2f GameObject::GetPosition()
{
	return m_xPosition;
}
void GameObject::SetPosition(const sf::Vector2f &p_xPosition)
{
	m_xPosition = p_xPosition;
}

bool GameObject::HasSprite() const
{
	return m_pxSprite != nullptr;
}
sf::Sprite* GameObject::GetSprite()
{
	return m_pxSprite;
}

//void GameObject::SetNewSprite(sf::Sprite* p_pxNewSprite)
//{
//	m_pxSprite = p_pxNewSprite;
//}

bool GameObject::HasCollider() const
{
	return m_pxCollider != nullptr;
}
Collider* GameObject::GetCollider()
{
	
	return m_pxCollider;
}

void GameObject::SetDestroyed(bool p_bDestroyed)
{
	m_bDestroyed = p_bDestroyed;
}

bool GameObject::GetDestroyed()
{
	return m_bDestroyed;
}

void GameObject::Update()
{
	//Uppdatera spelobjekt
}