#include "stdafx.h"
#include "Button.h"


Button::Button(void)
{
	m_sprite = nullptr;
	m_circle;	
}



void Button::SetButtonOrigin()
{
	m_sprite->setOrigin(m_sprite->getGlobalBounds().width/2,m_sprite->getGlobalBounds().height/2);
	m_circle.setOrigin(m_sprite->getPosition().x, m_sprite->getPosition().y);
}

void Button::SetCircle(float radius)
{
	m_circle.setRadius(radius);
}
void Button::SetSprite(sf::Sprite *sprite)
{
	m_sprite = sprite;
	SetButtonOrigin();
}
void Button::SetPosition(float x, float y)
{
	m_sprite->setPosition(x,y);
	m_circle.setPosition(x,y);
}

sf::Sprite* Button::GetSprite()
{
	return m_sprite;
}
sf::CircleShape Button::GetCircle()
{
	return m_circle;
}

Button::~Button(void)
{
}
