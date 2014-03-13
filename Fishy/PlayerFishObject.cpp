// PlayerFishObject.cpp

#pragma once

#include "FishObject.h"
#include "stdafx.h"
#include "PlayerFishObject.h"
#include "InputManager.h"
#include "GameObject.h"
#include "AnimatedSprite.h"
#include "LightSource.h"
#include "Camera.h"
#include "EnemyFishObject.h"

PlayerFishObject::PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite , Collider* p_Collider )
	: FishObject(p_Position, p_Sprite, p_Collider)
{

	m_Health = 90;
	m_Energy = 90;


	SetSpeed(500.0f);
	m_Healthtimer = 10;
	m_iAttacktimer = 15;
	m_ChewTimer = 64;
	m_GrowTimer = 64;
	m_SlowingDown = false;
	SetDirection(FacingRight);
	SetPlayerScale(0.6f);
	SetCurrentLevel(1);
	m_HasGrown = false;
	m_Experience = 0;
	SetType("Player");

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

	if( m_pxCurrentAnimation != nullptr)
	{
		delete m_pxCurrentAnimation;
		m_pxCurrentAnimation = nullptr;
	}
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
}

void PlayerFishObject::UpdateCollider()
{
	sf::IntRect rect;
	if(GetType() == "Player")
	{
		rect = m_pxCurrentAnimation->getTextureRect();
	}
	if(GetType() == "Player")
	{
		m_pxCollider->SetExtention(sf::Vector2f(rect.width * GetScale()*0.5f, rect.height * GetScale()*0.5f));
		PlayerFishObject* player = static_cast<PlayerFishObject*>(m_pxCollider->GetParent());
		if (player->GetCurrentLevel() >= 4 && player->GetCurrentLevel() < 7)
		{
			m_pxCollider->SetExtention(sf::Vector2f(rect.width * GetScale()*0.4f, rect.height * GetScale()*0.4f));
			if ((GetDirection() == FacingLeft || GetDirection() == FacingDownLeft || GetDirection() == FacingUpLeft))
			{

				//m_pxCollider->SetExtention(sf::Vector2f(rect.width * GetScale()*0.5f + (-50), rect.height * GetScale()*0.5f));
				m_pxCollider->SetPositionX(GetPosition().x + 100.f);
				m_pxCollider->SetPositionY(GetPosition().y);

			}
			if (GetDirection() == FacingRight || GetDirection() == FacingDownRight || GetDirection() == FacingUpRight )
			{
				//m_pxCollider->SetExtention(sf::Vector2f(rect.width * GetScale()*0.5f + (-50), rect.height * GetScale()*0.5f));
				m_pxCollider->SetPositionX(GetPosition().x - 100.f);
				m_pxCollider->SetPositionY(GetPosition().y);
			}
			if (GetDirection() == FacingUp)
			{
				m_pxCollider->SetPositionY(GetPosition().y);
			}
			if (GetDirection() == FacingDown)
			{
				m_pxCollider->SetPositionY(GetPosition().y);
			}
		}
		else
		{
			m_pxCollider->SetPosition(GetPosition() );
		}
	}
}

void PlayerFishObject::Update(InputManager *p_pxInputManager, SpriteManager *p_SpriteManager, Camera *p_Camera, float p_Deltatime)
{
	UpdateCollider();
	SetVelocity(sf::Vector2f(0.0f, 0.0f));
	UpdateHealth();
	if(GetState() == Death)
	{
		m_pxCurrentAnimation->SetActiveAnimation("Death");
		cout << "DEAD!" << endl;
	}
	else if(GetState() == Attack )
	{
		m_pxCurrentAnimation->SetActiveAnimation("Dash");
		UpdateAttack(p_Deltatime);
	}
	else if(GetState() == Chewing )
	{
		m_pxCurrentAnimation->SetActiveAnimation("Chew");
		UpdateChewing(p_Deltatime);
	}
	else if(GetState() == Growing)
	{
		UpdateGrowing(p_SpriteManager, p_Camera , p_Deltatime);
	}
	else 
	{
		UpdateInput(p_pxInputManager, p_Deltatime);
	}

	if(GetState() == Sneak)
	{
		m_pxCurrentAnimation->SetActiveAnimation("Sneak");
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

	Move(GetVelocity() );
	//m_light->SetPosition(GetLightbulbPosition() );

	//if(GetLightbulbPosition() != m_light->GetPosition() )
	//{
	//	
	//	SetLightPosition(GetLightbulbPosition() );
	//	//m_light->SetPosition(GetLightbulbPosition() );
	//  //m_light->SetPosition(GetPosition() );
	//}

	//cout <<"PlayerPos" << GetPosition().x << " " <<  GetPosition().y <<endl;
	//cout <<"lightPos" << m_light->GetPosition().x << " " <<  m_light->GetPosition().y <<endl;
	//cout <<"FilterPos" << p_Camera->GetFilterSprite()->getPosition().x << " " << p_Camera->GetFilterSprite()->getPosition().y <<endl;
	//cout <<"Velocity " << GetVelocity().x << " " <<  GetVelocity().y <<endl;

	if(m_pxCurrentAnimation != nullptr) 
	{
		m_pxCurrentAnimation->Update(p_Deltatime);
		m_pxCurrentAnimation->setOrigin(m_pxCurrentAnimation->getTextureRect().width / 2.0f, m_pxCurrentAnimation->getTextureRect().height / 2.0f);


	}

	if(GetCollider() != nullptr ) 
	{
		UpdateCollider();
	}
	//	/*if (GetCurrentLevel() > 3 && GetCurrentLevel() < 7)
	//	{
	//		if (GetDirection() == FacingLeft || GetDirection() == FacingDownLeft || GetDirection() == FacingUpLeft)
	//		{
	//			m_pxCollider->SetPosition(GetPosition() += sf::Vector2f(100.f, 0.0f));
	//		}
	//		if (GetDirection() == FacingRight || GetDirection() == FacingDownRight || GetDirection() == FacingUpRight)
	//		{
	//			m_pxCollider->SetPosition(GetPosition() -= sf::Vector2f(100.f, 0.0f));
	//		}
	//	}
	//	else
	//	{*/
	//		m_pxCollider->SetPosition(GetPosition() );
	//	//}
	//}

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

void PlayerFishObject::ChangeStageAnimation(const std::string &p_sName, SpriteManager *p_pxSpriteManager)
{
	sf::Vector2f tempPos = GetPosition();
	std::map<std::string, AnimatedSprite*>::iterator it = m_mpAnimations.begin();
	while(it != m_mpAnimations.end() )
	{
		delete it->second;
		it->second = nullptr;
		it++;
	}
	m_mpAnimations.clear();

	if(m_pxSprite != nullptr)
	{
		//delete m_pxSprite;
		m_pxSprite = nullptr;
		m_pxCurrentAnimation = nullptr;
	}

	//ska inte avbryta chewing
	if(p_sName == "Stage2")
	{

		AnimatedSprite *NewAnimSprite = p_pxSpriteManager->LoadAnim("../data/anim/PlayerAnimStage2.txt");		
		AddAnimation(p_sName, NewAnimSprite);
		SetPosition(tempPos);
	}
	else if(p_sName == "Stage3")
	{
		AnimatedSprite *NewAnimSprite = p_pxSpriteManager->LoadAnim("../data/anim/PlayerAnimStage3.txt");		
		AddAnimation(p_sName, NewAnimSprite);
	}
}

void PlayerFishObject::SetHealth(int p_Health)
{
	if(p_Health <= 100)
	
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

void PlayerFishObject::ExperienceGain(int x)
{
	m_Experience += x;
	//cout << "Experience :: " << GetExperience() << endl;
}

int PlayerFishObject::GetExperience()
{
	return m_Experience;
}

bool PlayerFishObject::UpdateLevel()
{
	if(GetExperience() == 1)
	{
		SetCurrentLevel(GetCurrentLevel() + 1);
		return true;
	}
	else if(GetExperience() == 2)
	{
		SetCurrentLevel(GetCurrentLevel() + 1);
		return true;
	}
	else if(GetExperience() == 3)
	{
		SetCurrentLevel(GetCurrentLevel() + 1);
		return true;
	}
	else if(GetExperience() == 4)
	{
		SetCurrentLevel(GetCurrentLevel() + 1);
		return true;
	}
	else if(GetExperience() == 5)
	{
		SetCurrentLevel(GetCurrentLevel() + 1);
		return true;
	}
	else if(GetExperience() == 6)
	{
		SetCurrentLevel(GetCurrentLevel() + 1);
		return true;
	}
	else if(GetExperience() == 7)
	{
		SetCurrentLevel(GetCurrentLevel() + 1);
		return true;
	}
	else if(GetExperience() == 8)
	{
		SetCurrentLevel(GetCurrentLevel() + 1);
		return true;
	}

	return false;
}

bool PlayerFishObject::HasGrown()
{
	return m_HasGrown;
}

void PlayerFishObject::SetSoundManager(SoundManager* p_soundmanager)
{
	m_SoundManager = p_soundmanager;
}

// överlarga oncollision
// du kommer få in en fisk som p_xOther
// if p_xOther.getTypy() == fisk
//		etc etc
//
// Player* p = nullptr;
// GameObject* g = new Player();
// p = static_cast<Player*>(g);

void PlayerFishObject::OnCollision(GameObject* p_other, sf::Vector2f& p_Offset)
{
	if (p_other->GetType() == "BrownBrick")
	{
		SetPosition(GetPosition() + p_Offset);
	}
	if (p_other->GetType() == "Enemy")
	{
		EnemyFishObject* tempptr = dynamic_cast<EnemyFishObject*>(p_other);
		if (tempptr->GetSubType() == "Stage2" )
		{
			if (GetCurrentLevel() <= 4 && tempptr->GetScale() >= 0.8)
			{
				SetHealth(GetHealth() -50);
			}
		}
		if(GetState() == Attack)
		{

			ExperienceGain(1);
			SetHealth(GetHealth() + 10);
			if(UpdateLevel() )
			{
				m_HasGrown = true;
			}
			SetState(Chewing);
			m_SoundManager->PlaySound("chew_sound2.wav");
			//std::cout << GetExperience() << std::endl;
			//cout << GetCurrentLevel() << endl;
		}
	}
}

void PlayerFishObject::UpdateInput(InputManager *p_pxInputManager, float p_Deltatime)
{
	if(GetState() != Sneak )
	{
		SetState(Idle);
		m_pxCurrentAnimation->SetActiveAnimation("Idle");
	}

	if(p_pxInputManager->IsDownK(sf::Keyboard::Up) && p_pxInputManager->IsDownK(sf::Keyboard::Right)
		|| p_pxInputManager->IsDownK(sf::Keyboard::W) && p_pxInputManager->IsDownK(sf::Keyboard::D ))
	{
		SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed(), p_Deltatime * -GetSpeed() ) );
		if(GetState() == Sneak)
		{
			SetVelocity(GetVelocity() * 0.25f );
		}
		else
		{
			SetState(Moving);
			m_pxCurrentAnimation->SetActiveAnimation("Move");
			SetDirection(FacingUpRight);
			FlipXRight(GetScale());
		}
	}
	else if(p_pxInputManager->IsDownK(sf::Keyboard::Up) && p_pxInputManager->IsDownK(sf::Keyboard::Left)
		|| p_pxInputManager->IsDownK(sf::Keyboard::W) && p_pxInputManager->IsDownK(sf::Keyboard::A ))
	{
		SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed(), p_Deltatime * -GetSpeed() ) );
		if(GetState() == Sneak)
		{
			SetVelocity(GetVelocity() * 0.25f );
		}
		else
		{
			SetState(Moving);
			m_pxCurrentAnimation->SetActiveAnimation("Move");
			SetDirection(FacingUpLeft);
			FlipXLeft(GetScale());
		}
	}
	else if(p_pxInputManager->IsDownK(sf::Keyboard::Down) && p_pxInputManager->IsDownK(sf::Keyboard::Right)
		|| p_pxInputManager->IsDownK(sf::Keyboard::S) && p_pxInputManager->IsDownK(sf::Keyboard::D ))
	{
		SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed(), p_Deltatime * GetSpeed() ) );
		if(GetState() == Sneak)
		{
			SetVelocity(GetVelocity() * 0.25f );
		}
		else
		{
			SetState(Moving);
			m_pxCurrentAnimation->SetActiveAnimation("Move");
			SetDirection(FacingDownRight);
			FlipXRight(GetScale());
		}
	}
	else if(p_pxInputManager->IsDownK(sf::Keyboard::Down) && p_pxInputManager->IsDownK(sf::Keyboard::Left )
		|| p_pxInputManager->IsDownK(sf::Keyboard::S) && p_pxInputManager->IsDownK(sf::Keyboard::A ))
	{
		SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed(), p_Deltatime * GetSpeed() ) );
		if(GetState() == Sneak)
		{
			SetVelocity(GetVelocity() * 0.25f );
		}
		else
		{
			SetState(Moving);
			m_pxCurrentAnimation->SetActiveAnimation("Move");
			SetDirection(FacingDownLeft);
			FlipXLeft(GetScale());
		}
	}
	else
	{
		if(p_pxInputManager->IsDownK(sf::Keyboard::Right) || p_pxInputManager->IsDownK(sf::Keyboard::D)  )
		{
			SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed(), 0.0f) );
			if(GetState() == Sneak)
			{
				SetVelocity(GetVelocity() * 0.25f );
			}
			else
			{
				SetState(Moving);
				m_pxCurrentAnimation->SetActiveAnimation("Move");
				SetDirection(FacingRight);
				FlipXRight(GetScale());
			}
		}
		else if(p_pxInputManager->IsDownK(sf::Keyboard::Left) || p_pxInputManager->IsDownK(sf::Keyboard::A) )
		{
			SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed(), 0.0f) );
			if(GetState() == Sneak)
			{
				SetVelocity(GetVelocity() * 0.25f );
			}
			else
			{
				SetState(Moving);
				m_pxCurrentAnimation->SetActiveAnimation("Move");
				SetDirection(FacingLeft);
				FlipXLeft(GetScale());
			}
		}
		else if(p_pxInputManager->IsDownK(sf::Keyboard::Up) || p_pxInputManager->IsDownK(sf::Keyboard::W) )
		{
			SetVelocity(sf::Vector2f(0.0f , p_Deltatime * -GetSpeed()) );
			if(GetState() == Sneak)
			{
				SetVelocity(GetVelocity() * 0.25f );
			}
			else
			{
				SetState(Moving);
				m_pxCurrentAnimation->SetActiveAnimation("Move");
				SetDirection(FacingUp);
			}
		}
		else if(p_pxInputManager->IsDownK(sf::Keyboard::Down) || p_pxInputManager->IsDownK(sf::Keyboard::S) )
		{
			SetVelocity(sf::Vector2f(0.0f , p_Deltatime * GetSpeed()) );
			if(GetState() == Sneak)
			{
				SetVelocity(GetVelocity() * 0.25f );
			}
			else
			{
				SetState(Moving);
				m_pxCurrentAnimation->SetActiveAnimation("Move");
				SetDirection(FacingDown);
			}
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
	else if(p_pxInputManager->IsReleasedK(sf::Keyboard::LShift)
		|| p_pxInputManager->IsReleasedK(sf::Keyboard::RShift) 
		|| p_pxInputManager->IsReleasedK(sf::Keyboard::LControl) 
		|| p_pxInputManager->IsReleasedK(sf::Keyboard::RControl))
	{
		SetState(Idle);
	}
	if(p_pxInputManager->IsDownOnceK(sf::Keyboard::F) )
	{
		if(m_light->GetLightStatus())
		{
			m_light->ToggleLightOn(false);
		}
		else
		{
			m_light->ToggleLightOn(true);
		}
	}
	if(GetDirection() == FacingDownLeft || GetDirection() == FacingLeft || GetDirection() == FacingUpLeft)
	{
		SetLightPosition(sf::Vector2f(GetPosition().x - 100, GetPosition().y ) );
	}
	else if(GetDirection() == FacingDownRight || GetDirection() == FacingRight || GetDirection() == FacingUpRight)
	{
		SetLightPosition(sf::Vector2f(GetPosition().x + 100, GetPosition().y ) );
	}
	else
	{
		SetLightPosition(sf::Vector2f(GetLightPosition().x, GetPosition().y ) );
	}
}

void PlayerFishObject::UpdateIdle(float p_Deltatime)
{
	//ADD slow movement
}

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
	//SetVelocity(GetVelocity() * 0.25f );
}
void PlayerFishObject::UpdateChewing(float p_Deltatime)
{
	m_ChewTimer--;
	if(m_ChewTimer == 0)
	{
		if(m_HasGrown)
		{
			SetState(Growing);
		}
		else
		{
			SetState(Idle);
		}
		m_ChewTimer = 64;
	}
}
void PlayerFishObject::UpdateGrowing(SpriteManager *p_SpriteManager, Camera *p_Camera, float p_Deltatime)
{
	if(GetCurrentLevel() == 4 || GetCurrentLevel() == 7)
	{
		if(m_pxCurrentAnimation->GetActiveAnimation() != "GrowingStage" )
		{
			m_pxCurrentAnimation->SetActiveAnimation("GrowingStage");
		}
		if(m_pxCurrentAnimation->GetCurrentFrame() == 1) { SetPlayerScale(0.8f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 2) { SetPlayerScale(0.5f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 3) { SetPlayerScale(0.8f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 4) { SetPlayerScale(0.4f); }
		p_Camera->SetZoomStrength(1.005f);
		p_Camera->ZoomOut(p_Camera->GetZoomStrength() );
		p_Camera->SetZoomingOut(true);
	}
	else if(GetCurrentLevel() == 2 || GetCurrentLevel() == 5 || GetCurrentLevel() == 8)
	{
		if(m_pxCurrentAnimation->GetActiveAnimation() != "GrowingLevel" )
		{
			m_pxCurrentAnimation->SetActiveAnimation("GrowingLevel");
		}
		if(m_pxCurrentAnimation->GetCurrentFrame() == 1) { SetPlayerScale(0.6f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 2) { SetPlayerScale(0.5f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 3) { SetPlayerScale(0.7f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 4) { SetPlayerScale(0.8f); }

	}
	else if(GetCurrentLevel() == 3 || GetCurrentLevel() == 6 || GetCurrentLevel() == 9)
	{
		if(m_pxCurrentAnimation->GetActiveAnimation() != "GrowingLevel" )
		{
			m_pxCurrentAnimation->SetActiveAnimation("GrowingLevel");
		}
		if(m_pxCurrentAnimation->GetCurrentFrame() == 1) { SetPlayerScale(0.8f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 2) { SetPlayerScale(0.7f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 3) { SetPlayerScale(0.9f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 4) { SetPlayerScale(1.0f); }
	}

	m_GrowTimer--;
	if(m_GrowTimer == 0)
	{

		SetState(Idle);
		m_GrowTimer = 64;
		m_HasGrown = false;
		//p_Camera->SetZoomingOut(false);
		if(GetCurrentLevel() == 2 || GetCurrentLevel() == 5 || GetCurrentLevel() == 8)  { SetPlayerScale(0.8f); }
		else if (GetCurrentLevel() == 3 || GetCurrentLevel() == 6 || GetCurrentLevel() == 9) { SetPlayerScale(1.0f); }

		if(GetCurrentLevel() == 4) 
		{ 
			ChangeStageAnimation("Stage2", p_SpriteManager); 
			SetPlayerScale(0.6f);
		}
		else if( GetCurrentLevel() == 7)  
		{ 
			//ChangeStageAnimation("Stage3", p_SpriteManager); 
			SetPlayerScale(0.6f);
		}
	}
	if(GetDirection() == FacingLeft || GetDirection() == FacingUpLeft || GetDirection() == FacingDownLeft ) 
	{
		FlipXLeft(GetScale() );
	}
	else
		FlipXRight(GetScale() );
}

void PlayerFishObject::UpdateHealth()
{
	if(GetState() != Death)
	{
		if(m_Healthtimer == 0)
		{
			m_Health--;
			m_Healthtimer = 50;
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
