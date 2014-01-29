// DrawManager.h
#pragma once

class DrawManager
{
public:
	DrawManager(sf::RenderWindow *p_Window);
	~DrawManager();


	void ClearWindow();
	//Change sf::Sprite to our sprite class, it has to be a sf:Drawable
	void DrawSprite(sf::Sprite * p_pSprite);
	//Change sf::Sprite to our sprite class, it has to be a sf:Drawable
	void DrawSprite(sf::Sprite * p_pSprite, sf::RenderStates * p_pEffect);
	void DisplayWindow();
private:
	sf::RenderWindow * m_Window;

};