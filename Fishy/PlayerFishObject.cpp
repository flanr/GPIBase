// PlayerFishObject.cpp

#pragma once

#include "FishObject.h"
#include "stdafx.h"
#include "PlayerFishObject.h"
#include "InputManager.h"
#include "GameObject.h"
#include "AnimatedSprite.h"

PlayerFishObject::PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite , Collider* p_Collider )
	: GameObject(p_Position, p_Sprite, p_Collider)
{

};

void PlayerFishObject::Update(float deltatime)
{

	if(m_pxCurrentAnimation != nullptr) {
		m_pxCurrentAnimation->Update(deltatime * 5.0f);
	}
};

void PlayerFishObject::AddAnimation(const std::string &p_sName, AnimatedSprite *p_pxAnimSprite)
{	
	m_mpAnimations.insert(std::pair<std::string,AnimatedSprite*>(p_sName, p_pxAnimSprite));
	if(	m_pxSprite == nullptr) 
	{
		m_pxSprite = p_pxAnimSprite;
		m_pxCurrentAnimation = p_pxAnimSprite;
	}
}