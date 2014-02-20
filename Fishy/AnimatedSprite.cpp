//AnimatedSprite.cpp

#include "stdafx.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(sf::Texture *p_texture, int p_iX, int p_iY, int p_iWidth, int p_iHeight)
	: sf::Sprite(*p_texture, sf::IntRect(p_iX, p_iY , p_iWidth , p_iHeight) )
{
	m_fTime = 0.0f;
	m_iCurrentFrame = 0;
	m_AnimType = "Idle";
}
AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Update(float p_fDeltatime)
{
	std::map<std::string, Anim>::iterator it = m_mAllAnimations.find(m_AnimType);
	it = m_mAllAnimations.find(m_AnimType);
	if(it->first == m_AnimType)
	{
		m_fTime += p_fDeltatime;
		if (m_fTime >= it->second.m_fFrameDuration ) 
		{
			m_fTime = 0.0f;
			m_iCurrentFrame = ++m_iCurrentFrame % it->second.m_axAnimation.size();
			setTextureRect( sf::IntRect(it->second.m_axAnimation[m_iCurrentFrame]) );
		}
	}
}

void AnimatedSprite::SetActiveAnimation(const std::string AnimName)
{
	m_AnimType = AnimName;
}

void AnimatedSprite::StoreAnim(const std::string AnimName, Anim p_Anim)
{
	m_mAllAnimations.insert(std::pair<std::string, Anim>(AnimName, p_Anim) );
}
