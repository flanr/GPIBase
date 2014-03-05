//GameObject.cpp
#include "stdafx.h"

#include "GameObject.h"
#include "LightSource.h"

//#include "Collider.h"

GameObject::GameObject(sf::Vector2f p_xPosition, sf::Sprite * p_pxSprite, Collider * p_pxCollider)
	: m_pxSprite(p_pxSprite), m_pxCollider(p_pxCollider), m_sType("GameObject")
{
	SetPosition(p_xPosition);
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
	if(m_pxSprite != nullptr)
	{
		m_pxSprite->setPosition(p_xPosition);
	}
}

void GameObject::Move(const sf::Vector2f &p_Offset)
{
	m_pxSprite->move(p_Offset);
	if(HasLight() )
	{
		m_light->Move(p_Offset);
	}
}
void GameObject::Move(float p_OffsetX, float p_OffsetY)
{
	m_pxSprite->move(p_OffsetX, p_OffsetY);
	if(HasLight() )
	{
		m_light->Move(p_OffsetX, p_OffsetY);
	}
}

sf::Vector2f GameObject::GetLightPosition()
{
	return m_light->GetPosition();
}
void GameObject::SetLightPosition(const sf::Vector2f &p_xPosition)
{
	m_light->SetPosition(p_xPosition);
}
void GameObject::SetLightPositionX(const float &p_Xposition)
{
	m_light->SetPosition(sf::Vector2f(p_Xposition, GetLightPosition().y) );
}
void GameObject::SetLightPositionY(const float &p_Yposition)
{
	m_light->SetPosition(sf::Vector2f(GetLightPosition().x, p_Yposition) );
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
	if (GetCollider() != nullptr)
	{
		GetCollider()->SetPosition(GetPosition());
	}
}

void GameObject::AddLightSource(LightSource *p_light)
{
	m_light = p_light;
}


bool GameObject::HasLight() const
{
	return m_light != nullptr;
}

LightSource* GameObject::GetLightSource()
{
	return m_light;
}

void GameObject::OnCollision(GameObject* p_xOther, sf::Vector2f& p_Offset)
{
	std::cout << "GameObject::OnCollision: GameObject A: " << GetType() << " GameObject B: " << p_xOther->GetType() << std::endl;
}
