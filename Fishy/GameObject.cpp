//GameObject.cpp
#include "stdafx.h"

#include "GameObject.h"
#include "LightSource.h"

//#include "Collider.h"

GameObject::GameObject(sf::Vector2f p_xPosition, sf::Sprite * p_pxSprite, Collider * p_pxCollider)
	: m_xPosition(p_xPosition), m_pxSprite(p_pxSprite), m_pxCollider(p_pxCollider), m_sType("GameObject")
{
	m_bDestroyed = false;
	m_light = nullptr;
	if(m_pxCollider != nullptr)
		m_pxCollider->SetParent(this);
}

GameObject::~GameObject()
{
}
void GameObject::SetLevelLayer(ELayer layer)
{
	m_LevelLayer = layer ;
}

ELayer GameObject::GetLevelLayer()
{
	return m_LevelLayer;
}



sf::Vector2f GameObject::GetPosition()
{
	return m_pxSprite->getPosition();
}
void GameObject::SetPosition(const sf::Vector2f &p_xPosition)
{
	m_pxSprite->setPosition(p_xPosition);
}

sf::Vector2f GameObject::GetLightPosition()
{
		return m_light->GetPosition();
}
void GameObject::SetLightPosition(const sf::Vector2f &p_xPosition)
{
		m_light->SetPosition(p_xPosition);
}

bool GameObject::HasSprite() const
{
	return m_pxSprite != nullptr;
}
sf::Sprite* GameObject::GetSprite()
{
	return m_pxSprite;
}

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

void GameObject::FlipXLeft(float scale)
{
	if(m_pxSprite != nullptr)
	{
		m_pxSprite->setScale(-scale , scale);
	}
}

void GameObject::FlipXRight(float scale)
{
	if(m_pxSprite != nullptr)
	{
		m_pxSprite->setScale(scale , scale);
	}
}

void GameObject::Update(float deltatime)
{
	//Uppdatera spelobjekt
}

void GameObject::AddLightSource(LightSource *p_light)
{
	m_light = p_light;
}

LightSource* GameObject::GetLightSource()
{
	return m_light;
}

void GameObject::OnCollision(GameObject* p_xOther)
{
	/*std::cout << "GameObject::OnCollision: GameObject A: " << GetType() << " GameObject B: " << p_xOther->GetType() << std::endl;*/
}
