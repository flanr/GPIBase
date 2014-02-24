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

	//m_fPlayerSpeed = 80.0f;
	//m_fDash = 30.0f;
	//for(int i = 0; i < StateCount; i++)
	//{
	//	m_CurrentState[i] = false;
	//}
	//m_CurrentState[Idle] = true;
	m_Health = 90;
	m_Energy = 90;

	SetSpeed(250.0f);
	m_Healthtimer = 10;
	m_iAttacktimer = 15;
	m_SlowingDown = false;
	SetDirection(FacingRight);
	SetPlayerScale(0.2f);
	m_Experience = 0;

};
void PlayerFishObject::ExperienceGain(int x)
{
	m_Experience += x;
	cout << "Experience :: " << GetExperience() << endl;
}

int PlayerFishObject::GetExperience()
{
	return m_Experience;
}

void PlayerFishObject::SetPlayerScale(float x)
{
	SetScale(x);

	std::map<std::string, AnimatedSprite*>::iterator it = m_mpAnimations.begin();
	while(it != m_mpAnimations.end() )
	{
		it->second->setScale(GetScale(),GetScale());
		it++;
	}

	//->scale(Scale,Scale);
	if (m_pxCollider->GetExtension().x >= 237 && m_pxCollider->GetExtension().y >= 195)
	{
		m_pxCollider->SetExtention(m_pxCollider->GetExtension()*GetScale());
	}
   

}

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
	/*if(GetCollider() != nullptr)
	{
	delete  GetCollider();
	}*/
}

void PlayerFishObject::Update(InputManager *p_pxInputManager, float p_Deltatime)
{
	//Note to myself try std::map<std::string, vector<sf::Intrect>> m_Rects so you load a big sprite and cut rects depending on animations
	SetVelocity(sf::Vector2f(0.0f, 0.0f));
	UpdateHealth();
	if(GetState() == Death)
	{
		cout << "DEAD!" << endl;
	}
	else if(GetState() == Attack )
	{
		m_pxCurrentAnimation->SetActiveAnimation("Dash");
		UpdateAttack(p_Deltatime);
	}
	else if(GetState() == Chewing )
	{
		UpdateChewing(p_Deltatime);
	}
	else 
	{
		UpdateInput(p_pxInputManager, p_Deltatime);
	}

	if(GetState() == Sneak)
	{
		UpdateSneak(p_Deltatime);
	}
	if (p_pxInputManager->IsDownK(sf::Keyboard::H))
	{
		if (m_Health >= 100)
		{
			m_Health = 0;
		}
		m_Health ++;
	}

	SetPosition( GetPosition() + GetVelocity() );
	//m_PlayerView.move(GetVelocity() );
	m_PlayerView.setCenter(GetPosition() );


	if(m_pxCurrentAnimation != nullptr) 
	{
		m_pxCurrentAnimation->Update(p_Deltatime);
		m_pxCurrentAnimation->setOrigin(m_pxCurrentAnimation->getTextureRect().width / 2.0f, m_pxCurrentAnimation->getTextureRect().height / 2.0f);
	}

	if(HasCollider() ) 
	{
		m_pxCollider->SetPosition(GetPosition() );
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
	SetPlayerScale(GetScale());
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

void PlayerFishObject::UpdateInput(InputManager *p_pxInputManager, float p_Deltatime)
{
	SetState(Idle);
	m_pxCurrentAnimation->SetActiveAnimation("Idle");
	if(p_pxInputManager->IsDownK(sf::Keyboard::Up) && p_pxInputManager->IsDownK(sf::Keyboard::Right)
		|| p_pxInputManager->IsDownK(sf::Keyboard::W) && p_pxInputManager->IsDownK(sf::Keyboard::D ))
	{
		SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed(), p_Deltatime * -GetSpeed() ) );
		SetState(Moving);
		SetDirection(FacingUpRight);
		FlipXRight(GetScale());
	}
	else if(p_pxInputManager->IsDownK(sf::Keyboard::Up) && p_pxInputManager->IsDownK(sf::Keyboard::Left)
		|| p_pxInputManager->IsDownK(sf::Keyboard::W) && p_pxInputManager->IsDownK(sf::Keyboard::A ))
	{
		SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed(), p_Deltatime * -GetSpeed() ) );
		SetState(Moving);
		SetDirection(FacingUpLeft);
		FlipXLeft(GetScale());
	}
	else if(p_pxInputManager->IsDownK(sf::Keyboard::Down) && p_pxInputManager->IsDownK(sf::Keyboard::Right)
		|| p_pxInputManager->IsDownK(sf::Keyboard::S) && p_pxInputManager->IsDownK(sf::Keyboard::D ))
	{
		SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed(), p_Deltatime * GetSpeed() ) );
		SetState(Moving);
		SetDirection(FacingDownRight);
		FlipXRight(GetScale());
	}
	else if(p_pxInputManager->IsDownK(sf::Keyboard::Down) && p_pxInputManager->IsDownK(sf::Keyboard::Left )
		|| p_pxInputManager->IsDownK(sf::Keyboard::S) && p_pxInputManager->IsDownK(sf::Keyboard::A ))
	{
		SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed(), p_Deltatime * GetSpeed() ) );
		SetState(Moving);
		SetDirection(FacingDownLeft);
		FlipXLeft(GetScale());
	}
	else
	{
		if(p_pxInputManager->IsDownK(sf::Keyboard::Right) || p_pxInputManager->IsDownK(sf::Keyboard::D)  )
		{
			SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed(), 0.0f) );
			SetState(Moving);
			SetDirection(FacingRight);
			FlipXRight(GetScale());
		}
		else if(p_pxInputManager->IsDownK(sf::Keyboard::Left) || p_pxInputManager->IsDownK(sf::Keyboard::A) )
		{
			SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed(), 0.0f) );
			SetState(Moving);
			SetDirection(FacingLeft);
			FlipXLeft(GetScale());
		}
		else if(p_pxInputManager->IsDownK(sf::Keyboard::Up) || p_pxInputManager->IsDownK(sf::Keyboard::W) )
		{
			SetVelocity(sf::Vector2f(0.0f , p_Deltatime * -GetSpeed()) );
			SetState(Moving);
			SetDirection(FacingUp);
		}
		else if(p_pxInputManager->IsDownK(sf::Keyboard::Down) || p_pxInputManager->IsDownK(sf::Keyboard::S) )
		{
			SetVelocity(sf::Vector2f(0.0f , p_Deltatime * GetSpeed()) );
			SetState(Moving);
			SetDirection(FacingDown);
		}
	}

	if(p_pxInputManager->IsDownOnceK(sf::Keyboard::Space) )
	{
		if(!(GetDirection() == FacingDown || GetDirection() == FacingUp ) )
		{
			SetState(Attack);
		}
	}
	else if(p_pxInputManager->IsDownK(sf::Keyboard::LShift)
		|| p_pxInputManager->IsDownK(sf::Keyboard::RShift) 
		|| p_pxInputManager->IsDownK(sf::Keyboard::LControl) 
		|| p_pxInputManager->IsDownK(sf::Keyboard::RControl))
	{
		SetState(Sneak);
	}

	//std::cout << GetState();
}

void PlayerFishObject::UpdateIdle(float p_Deltatime)
{

}
//void PlayerFishObject::UpdateMovement(float p_Deltatime)
//{
//	if( GetDirection() == FacingLeft )
//	{
//		SetVelocityX(p_Deltatime * -GetSpeed() );
//	}
//	if( GetDirection() == FacingRight )
//	{
//		SetVelocityX(p_Deltatime * GetSpeed() );
//	}
//	if( GetDirection() == FacingUp )
//	{
//		SetVelocityY(p_Deltatime * -GetSpeed() );
//	}
//	if( GetDirection() == FacingDown )
//	{
//		SetVelocityY(p_Deltatime * GetSpeed() );
//	}
//}

void PlayerFishObject::UpdateAttack(float p_Deltatime)
{
	if(GetDirection() == FacingRight )
	{
		SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed() * GetAttackPower(), 0.0f) );
	}
	else if(GetDirection()  == FacingLeft )
	{
		SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed() * GetAttackPower(), 0.0f) );
	}
	else if(GetDirection() == FacingUp)
	{
		SetVelocity(sf::Vector2f(0.0f, p_Deltatime * -GetSpeed() * GetAttackPower()) );
	}
	else if(GetDirection()  == FacingDown)
	{
		SetVelocity(sf::Vector2f( 0.0f, p_Deltatime * GetSpeed() * GetAttackPower() ) );
	}
	else if(GetDirection() == FacingUpRight )
	{
		SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed() * GetAttackPower(), p_Deltatime * -GetSpeed() * GetAttackPower() ) );
	}
	else if(GetDirection()  == FacingUpLeft )
	{
		SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed() * GetAttackPower(), p_Deltatime * -GetSpeed() * GetAttackPower() ) );
	}
	else if(GetDirection() == FacingDownRight)
	{
		SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed() * GetAttackPower(), p_Deltatime * GetSpeed() * GetAttackPower()) );
	}
	else if(GetDirection()  == FacingDownLeft)
	{
		SetVelocity(sf::Vector2f( p_Deltatime * -GetSpeed() * GetAttackPower(), p_Deltatime * GetSpeed() * GetAttackPower() ) );
	}

	if(m_SlowingDown)
	{
		SetAttackPower( GetAttackPower() - 0.5f);
	}
	else
	{
		SetAttackPower( GetAttackPower() + 0.5f);
		if(GetAttackPower() > 4.f)
		{
			m_SlowingDown = true;
		}
	}

	m_iAttacktimer--;
	if(m_iAttacktimer == 0)
	{
		SetState(Idle);
		m_iAttacktimer = 15;
		SetAttackPower(0.0f);
		m_SlowingDown = false;
	}
}

void PlayerFishObject::UpdateSneak(float p_Deltatime)
{
	SetVelocity(GetVelocity() * 0.25f );
}
void PlayerFishObject::UpdateChewing(float p_Deltatime)
{
	//return m_PlayerView.getViewport();
}

void PlayerFishObject::SetHealth(int p_Health)
{
	if(p_Health <= 100)
	{
		m_Health = p_Health;
	}
}

int PlayerFishObject::GetHealth()
{
	return m_Health;
}

void PlayerFishObject::SetEnergy(int p_Energy)
{
	m_Energy = p_Energy;
}

int PlayerFishObject::GetEnergy()
{
	return m_Energy;
}

void PlayerFishObject::UpdateHealth()
{
	if(GetState() != Death)
	{
		if(m_Healthtimer == 0)
		{
			m_Health--;
			m_Healthtimer = 100;
			if(GetHealth() == 0)
			{
				SetState(Death);
			}
		}
		else
		{
			m_Healthtimer--;
		}
	}
}
