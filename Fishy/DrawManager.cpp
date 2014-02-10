// DrawManager.cpp
#include "stdafx.h"
#include "DrawManager.h"

DrawManager::DrawManager(sf::RenderWindow *p_Window)
{
	m_pWindow = p_Window;
}

DrawManager::~DrawManager()
{
}

void DrawManager::ClearWindow()
{
	//Change color to whatever
	m_pWindow->clear(sf::Color(0x00,0x50,0x00,0xff));	
}

void DrawManager::DrawSpriteEffect(sf::Sprite * p_pSprite, sf::RenderStates * p_pEffect)
{
	m_pWindow->draw(*p_pSprite, *p_pEffect);
}
void DrawManager::Draw(sf::Sprite *p_sprite)
{
	m_pWindow->draw(*p_sprite);
}


void DrawManager::DisplayWindow()
{
	m_pWindow->display();
}