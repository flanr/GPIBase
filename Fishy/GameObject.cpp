//GameObject.cpp
#include "stdafx.h"

#include "GameObject.h"
#include "Sprite.h"


//#include "BoxCollider.h"
//#include "CircleCollider.h"

GameObject::GameObject()
{
}

GameObject::GameObject(sf::Vector2f p_xPosition, sf::Sprite * p_pxSprite)
: m_xPosition(p_xPosition), m_pxSprite(p_pxSprite)
{
	m_bDestroyed = false;
}

GameObject::GameObject(sf::Vector2f p_xPosition, BoxCollider * p_pxCollider, sf::Sprite * p_pxSprite)
: m_xPosition(p_xPosition), m_pxCollider(p_pxCollider), m_pxSprite(p_pxSprite)
{
	m_bDestroyed = false;
}

GameObject::GameObject(sf::Vector2f p_xPosition, CircleCollider * p_pxCircleCollider, sf::Sprite * p_pxSprite)
: m_xPosition(p_xPosition), m_pxCircleCollider(p_pxCircleCollider), m_pxSprite(p_pxSprite)
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

void GameObject::SetNewSprite(sf::Sprite* p_pxNewSprite)
{
	m_pxSprite = p_pxNewSprite;
}

bool GameObject::HasBoxCollider() const
{
	return m_pxCollider != nullptr;
}
BoxCollider* GameObject::GetBoxCollider()
{
	
	return m_pxCollider;
}

bool GameObject::HasCircleCollider() const
{
	return m_pxCircleCollider != nullptr;
}

CircleCollider* GameObject::GetCircleCollider()
{

	return m_pxCircleCollider;
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
