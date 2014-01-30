// Sprite.h
#pragma once


class Sprite{
	friend class DrawManager;
	friend class SpriteManager;
public:
	Sprite(sf::RenderWindow *m_pWindow, int x, int y, int width, int height);
protected:
	
	int m_x;
	int m_y;
	int m_width;
	int m_height;


};