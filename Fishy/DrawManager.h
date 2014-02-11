// DrawManager.h
#pragma once
#include "Slider.h"
class DrawManager
{
public:
	DrawManager(sf::RenderWindow *p_pWindow);
	~DrawManager();


	void ClearWindow();
	void DrawSpriteEffect(sf::Sprite * p_pSprite, sf::RenderStates * p_pEffect);
	void Draw(sf::Sprite *p_sprite);
	void DrawRect(sf::RectangleShape rect);
	void DrawSlider(Slider slider);
	void DisplayWindow();
private:
	sf::RenderWindow * m_pWindow;

};