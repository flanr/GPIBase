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
	void Draw(sf::Sprite *p_sprite);
	void DisplayWindow();
private:
	sf::RenderWindow * m_pWindow;

};