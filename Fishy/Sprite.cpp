// Sprite.cpp

#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite(sf::Texture *Texture, int x, int y, int width, int height)
{
	m_Sprite->setTexture(*Texture);
	m_Sprite->setTextureRect(sf::IntRect(x, y, width, height) );
}
	Sprite::~Sprite()
{
}

sf::Sprite* Sprite::getSfSprite()
{
	return m_Sprite;
}
