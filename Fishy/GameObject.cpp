//GameObject.cpp
#include "stdafx.h"

#include "GameObject.h"
#include "Sprite.h"


//#include "BoxCollider.h"
//#include "CircleCollider.h"

GameObject::GameObject()
{
}

GameObject::GameObject(sf::Vector2f p_xPosition, Sprite * p_pxSprite)
: m_xPosition(p_xPosition), m_pxSprite(p_pxSprite)
{
	m_bDestroyable = false;
}

GameObject::GameObject(sf::Vector2f p_xPosition, BoxCollider * p_pxCollider, Sprite * p_pxSprite)
: m_xPosition(p_xPosition), m_pxCollider(p_pxCollider), m_pxSprite(p_pxSprite)
{
	m_bDestroyable = false;
}

GameObject::GameObject(sf::Vector2f p_xPosition, CircleCollider * p_pxCircleCollider, Sprite * p_pxSprite)
: m_xPosition(p_xPosition), m_pxCircleCollider(p_pxCircleCollider), m_pxSprite(p_pxSprite)
{
	m_bDestroyable = false;
}

GameObject::~GameObject()
{
}

const sf::Vector2f &GameObject::GetPosition() const
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
Sprite* GameObject::GetSprite()
{
	return m_pxSprite;
}

void GameObject::SetNewSprite(Sprite* p_pxNewSprite)
{
	m_pxSprite = p_pxNewSprite;
}

bool GameObject::HasCollider() const
{
	return m_pxCollider != nullptr;
}
BoxCollider* GameObject::GetCollider()
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

void GameObject::SetDestroyable(bool p_bDestroyable)
{
	m_bDestroyable = p_bDestroyable;
}

bool GameObject::GetDestroyable()
{
	return m_bDestroyable;
}

void GameObject::Update()
{
	//Uppdatera spelobjekt
}
