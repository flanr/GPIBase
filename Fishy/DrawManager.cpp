// DrawManager.cpp
#include "stdafx.h"
#include "Slider.h"
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
	m_pWindow->clear(sf::Color::Transparent);	
}

void DrawManager::DrawSpriteEffect(sf::Sprite * p_pSprite, sf::RenderStates * p_pEffect)
{
	m_pWindow->draw(*p_pSprite, *p_pEffect);
}
void DrawManager::Draw(sf::Sprite *p_sprite)
{
	m_pWindow->draw(*p_sprite);
}

void DrawManager::DrawRect(sf::RectangleShape rect)
{
	m_pWindow->draw(rect);
}
void DrawManager::DrawSlider(Slider slider)
{
	DrawRect(slider.m_FullSlider);
	DrawRect(slider.m_EmptySlider);
	
}

void DrawManager::DisplayWindow()
{
	m_pWindow->display();
}