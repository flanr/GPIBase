// Sprite.h
#pragma once


class Sprite : sf::Sprite
{
	friend class SpriteManager;
public:

	Sprite(sf::Texture *p_Texture, int x, int y, int width, int height);
	~Sprite();
	sf::Sprite* getSfSprite();

protected:
	
	sf::Sprite *m_Sprite;
	sf::Texture *m_Texture;
};