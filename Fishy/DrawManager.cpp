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
	m_pWindow->clear(sf::Color(0x00,0x00,0x00,0xff));
	
}

//Change sf::Sprite to our sprite class, it has to be a sf:Drawable
void DrawManager::DrawSprite(sf::Sprite * p_pSprite)
{

	m_pWindow->draw(*p_pSprite);
}
//Change sf::Sprite to our sprite class, it has to be a sf:Drawable
void DrawManager::DrawSprite(sf::Sprite * p_pSprite, sf::RenderStates * p_pEffect)
{
	m_pWindow->draw(*p_pSprite, *p_pEffect);
}

void DrawManager::DisplayWindow()
{
	m_pWindow->display();
	
}