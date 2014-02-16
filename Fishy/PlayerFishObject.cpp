// PlayerFishObject.cpp

#pragma once

#include "FishObject.h"
#include "stdafx.h"
#include "PlayerFishObject.h"
#include "InputManager.h"
#include "GameObject.h"
#include "AnimatedSprite.h"

PlayerFishObject::PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite , Collider* p_Collider )
	: FishObject(p_Position, p_Sprite, p_Collider)
{
	SetSpeed(120.0f);
	m_iDashtimer = 15;
	m_SlowingDown = false;

	SetDirectionTrue(FacingRight);
	SetDirectionTrue(FacingDown);
};

PlayerFishObject::~PlayerFishObject()
{
	//delete all Animated sprites
	std::map<std::string, AnimatedSprite*>::iterator it = m_mpAnimations.begin();
	while(it != m_mpAnimations.end() )
	{
		delete it->second;
		it++;
	}
	m_mpAnimations.clear();
	//Delete Collider
	if(GetCollider() != nullptr)
	{
		delete  GetCollider();
	}
}

void PlayerFishObject::Update(InputManager *p_pxInputManager, float p_Deltatime)
{
	//Note to myself try std::map<std::string, vector<sf::Intrect>> m_Rects so you load a big sprite and cut rects depending on animations
	SetVelocity(sf::Vector2f(0.0f, 0.0f));
	if(GetState() == Dash )
	{
		UpdateDash(p_Deltatime);
	}
	else
	{
		if(p_pxInputManager->IsDownK(sf::Keyboard::Right))
		{
			SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed(), 0.0f) );
			if(GetState() != Dash)
			{
				SetState(Moving);
			}
			SetDirectionTrue(FacingRight);
			SetDirectionFalse(FacingLeft);
			FlipXRight();
		}
		if(p_pxInputManager->IsDownK(sf::Keyboard::Left))
		{
			SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed(), 0.0f) );
			if(GetState() != Dash)
			{
				SetState(Moving);
			}
			SetDirectionTrue(FacingLeft);
			SetDirectionFalse(FacingRight);
			FlipXLeft();
		}
		if(p_pxInputManager->IsDownK(sf::Keyboard::Up))
		{
			SetVelocity(sf::Vector2f(0.0f, p_Deltatime * -GetSpeed()) );
			if(GetState() != Dash)
			{
				SetState(Moving);
			}
			SetDirectionTrue(FacingUp);
			SetDirectionFalse(FacingDown);
		}
		if(p_pxInputManager->IsDownK(sf::Keyboard::Down))
		{
			SetVelocity(sf::Vector2f(0.0f, p_Deltatime * GetSpeed()) );
			if(GetState() != Dash)
			{
				SetState(Moving);
			}
			SetDirectionTrue(FacingDown);
			SetDirectionFalse(FacingUp);
		}
		if(p_pxInputManager->IsDownOnceK(sf::Keyboard::Space))
		{
			SetState(Dash);
		}
	}

	SetPosition( GetPosition() + GetVelocity() );
	m_PlayerView.move(GetVelocity() );

	if(HasCollider() ) 
	{
		m_pxCollider->SetPosition(GetPosition() );
	}

	//if(m_CurrentState[Idle])
	//{
	//	/*SetActiveAnimation("Idle");*/
	//}
	//if(m_CurrentState[Moving])
	//{
	//	/*SetActiveAnimation("Move");*/
	//}
	//if(m_CurrentState[Dash])
	//{
	//	/*SetActiveAnimation("Dash");*/
	//}
	if(m_pxCurrentAnimation != nullptr) {
		m_pxCurrentAnimation->Update(p_Deltatime);
		m_pxCurrentAnimation->setOrigin(m_pxCurrentAnimation->getTextureRect().width / 2.0f, m_pxCurrentAnimation->getTextureRect().height / 2.0f);
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

//void PlayerFishObject::SetActiveAnimation(const std::string &p_sName)
//{
//	SetNewSprite(GetAnimation(p_sName) );
//}
//AnimatedSprite* PlayerFishObject::GetAnimation(const std::string &p_sName)
//{
//	std::map<std::string, AnimatedSprite*>::iterator it = m_mpAnimations.find(p_sName);
//
//	if(it == m_mpAnimations.end()) 
//	{
//		it = m_mpAnimations.find(p_sName);
//	}
//	return it->second;
//}

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

void PlayerFishObject::UpdateDash(float p_Deltatime)
{
	if(GetHorizontalDirection() == FacingRight && (GetVerticalDirection() == FacingUp || GetVerticalDirection() == FacingDown) )
		{
			SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed() * GetDashPower(), 0.0f) );
		}
		else if(GetHorizontalDirection()  == FacingLeft && (GetVerticalDirection() == FacingUp || GetVerticalDirection() == FacingDown) )
		{
			SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed() * GetDashPower(), 0.0f) );
		}
	/*	else if(GetVerticalDirection() == FacingUp)
		{
			SetVelocity(sf::Vector2f(0.0f, p_Deltatime * -GetSpeed() * GetDashPower()) );
		}
		else if(GetVerticalDirection()  == FacingDown)
		{
			SetVelocity(sf::Vector2f( 0.0f, p_Deltatime * GetSpeed() * GetDashPower() ) );
		}*/
		if(m_SlowingDown)
		{
			SetDashPower( GetDashPower() - 0.1f);
		}
		else
		{
			SetDashPower( GetDashPower() + 1.f);
			if(GetDashPower() > 5.f)
			{
				m_SlowingDown = true;
			}
		}

		m_iDashtimer--;
		if(m_iDashtimer == 0)
		{
			SetState(Idle);
			m_iDashtimer = 25;
			SetDashPower(0.0f);
			m_SlowingDown = false;
		}
}
