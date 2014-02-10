//AnimatedSprite.cpp

#include "stdafx.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(sf::Texture p_texture, int p_iX, int p_iY, int p_iWidth, int p_iHeight)
	: sf::Sprite(p_texture, sf::IntRect(p_iX, p_iY , p_iWidth , p_iHeight) )
{
	m_fTime = 0.0f;
	m_iCurrentFrame = 0;

}
AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Update(float p_fDeltatime)
{
	m_fTime += p_fDeltatime;

	if (m_fTime >= m_fFrameDuration) 
	{
		m_fTime = 0.0f;
		m_iCurrentFrame = ++m_iCurrentFrame % m_axAnimation.size();
		setTextureRect( m_axAnimation[m_iCurrentFrame]);
	}
}

void AnimatedSprite::SetFrameDuration(float p_fFrameDuration)
{
	m_fFrameDuration = p_fFrameDuration;
}

void AnimatedSprite::AddFrame(sf::IntRect &p_Rect)
{
	m_axAnimation.push_back(p_Rect);
}
