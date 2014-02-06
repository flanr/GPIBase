// DrawManager.h
#pragma once

class DrawManager
{
public:
	DrawManager(sf::RenderWindow *p_pWindow);
	~DrawManager();


	void ClearWindow();
	void DrawSprite(sf::Sprite * p_pSprite);
	void DrawSprite(sf::Sprite * p_pSprite, sf::RenderStates * p_pEffect);
	void DisplayWindow();
private:
	sf::RenderWindow * m_pWindow;

};