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
	m_fPlayerSpeed = 80.0f;
};

void PlayerFishObject::Update(InputManager *p_pxInputManager, float p_Deltatime)
{
	m_fVelocity = sf::Vector2f(0.0f, 0.0f);
	if(p_pxInputManager->IsDownK(sf::Keyboard::Right))
	{
		m_fVelocity.x = p_Deltatime * m_fPlayerSpeed;
	}
	if(p_pxInputManager->IsDownK(sf::Keyboard::Left))
	{
		m_fVelocity.x = p_Deltatime * -m_fPlayerSpeed;
	}
	if(p_pxInputManager->IsDownK(sf::Keyboard::Up))
	{
		m_fVelocity.y = p_Deltatime * -m_fPlayerSpeed;
	}
	if(p_pxInputManager->IsDownK(sf::Keyboard::Down))
	{
		m_fVelocity.y = p_Deltatime * m_fPlayerSpeed;
	}

	SetPosition( GetPosition() + m_fVelocity );
	m_PlayerView.move(m_fVelocity);

	if(HasCollider() ) 
	{
		//move collider
	}

	if(m_pxCurrentAnimation != nullptr) {
		m_pxCurrentAnimation->Update(p_Deltatime);
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

void PlayerFishObject::SetPlayerSpeed(float p_fPlayerSpeed)
{
	m_fPlayerSpeed = p_fPlayerSpeed;
}
float PlayerFishObject::GetPlayerSpeed()
{
	return m_fPlayerSpeed;
}

void PlayerFishObject::InitPlayerView(sf::Vector2f p_Size)
{

	m_PlayerView.setCenter(GetPosition() );
	m_PlayerView.setSize(p_Size);
}

sf::View PlayerFishObject::GetPlayerView()
{
	return m_PlayerView;
}

void PlayerFishObject::SetPlayerViewport(sf::FloatRect p_NewViewPort)
{
	m_PlayerView.setViewport(p_NewViewPort);
}

sf::FloatRect PlayerFishObject::GetPlayerViewport()
{
	return m_PlayerView.getViewport();
}