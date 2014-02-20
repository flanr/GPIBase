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
	SetCircle(m_sprite->getGlobalBounds().width/2);
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
void Button::MouseMove(int x, int y)
{
	
}

//{ //((x > xx - m_ButtonQuit.GetCircle().getRadius() & x < xx + m_ButtonQuit.GetCircle().getRadius() ) && (y > yy - m_ButtonQuit.GetCircle().getRadius()  && y < yy + m_ButtonQuit.GetCircle().getRadius() ) )
//	
//	return (x > m_circle.
//}

void Button::MouseDown(int x, int y)
{

}
void Button::MouseUp()
{

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
