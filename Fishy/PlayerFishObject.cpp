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
#include "PowerupObject.h"

PlayerFishObject::PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite , Collider* p_Collider )
	: FishObject(p_Position, p_Sprite, p_Collider)
{

	m_Health = 100;
	m_Energy = 100;

	m_LightbulbPosRelativeToPlayer = sf::Vector2f(204, 43);
	SetSpeed(500.0f);
	m_Healthtimer = 0.f;
	m_iAttacktimer = 0.f;
	SetAttackPower(0.f);
	m_ChewTimer = 0.f;
	m_GrowTimer = 0.f;
	m_DeathTimer = 0.f;
	m_SlowingDown = false;
	SetDirection(FacingRight);
	SetPlayerScale(0.6f);
	SetCurrentLevel(1);
	m_HasGrown = false;
	m_HasFishingRod = false;
	m_PowerupLightCounter = 0;
	m_PowerupSpeedCounter = 0;
	m_PowerupEnergyCounter = 0;
	m_Experience = 0;
	SetType("Player");
	m_Time = m_Clock.restart();
	m_bCanTakeDamage = true;
	SetActive(true);
	m_StageTwo =false;
	m_GameOver = false;
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

	m_pxSprite = nullptr;
	m_pxCurrentAnimation = nullptr;
	if(m_light != nullptr)
	{
		delete m_light;
		m_light = nullptr;
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
			if ((GetDirection() == FacingLeft || GetDirection() == FacingDownLeft || GetDirection() == FacingUpLeft || GetState() == Sneak))
			{

				//m_pxCollider->SetExtention(sf::Vector2f(rect.width * GetScale()*0.5f + (-50), rect.height * GetScale()*0.5f));
				m_pxCollider->SetPositionX(GetPosition().x + 80.f);
				m_pxCollider->SetPositionY(GetPosition().y);

			}
			if (GetDirection() == FacingRight || GetDirection() == FacingDownRight || GetDirection() == FacingUpRight || GetState() == Sneak )
			{
				//m_pxCollider->SetExtention(sf::Vector2f(rect.width * GetScale()*0.5f + (-50), rect.height * GetScale()*0.5f));
				m_pxCollider->SetPositionX(GetPosition().x - 80.f);
				m_pxCollider->SetPositionY(GetPosition().y);
			}
			/*	if (GetDirection() == FacingUp)
			{
			m_pxCollider->SetPositionY(GetPosition().y);
			}
			if (GetDirection() == FacingDown)
			{
			m_pxCollider->SetPositionY(GetPosition().y);
			}*/
		}
		else
		{
			m_pxCollider->SetPosition(GetPosition() );
		}
	}
}

void PlayerFishObject::Update(InputManager *p_pxInputManager, SpriteManager *p_SpriteManager, Camera *p_Camera, float p_Deltatime)
{
	//UpdateCollider();
	SetVelocity(sf::Vector2f(0.0f, 0.0f));
	if(GetState() != Death)
	{
		UpdateHealth(p_Deltatime);
		UpdateEnergy(p_Deltatime);
		UpdateSoundFeedback();
	} 

	if(GetState() == Death)
	{
		UpdateDeath(p_Deltatime, p_Camera);
		cout << "DEAD!" << endl;
	}
	else if(GetState() == Attack )
	{
		UpdateAttack(p_Deltatime);
	}
	else if(GetState() == Growing)
	{
		UpdateGrowing(p_SpriteManager, p_Camera , p_Deltatime);
	}
	else if(GetState() == Chewing )
	{
		UpdateChewing(p_Deltatime);
		if(GetState() != Growing)
		{
			UpdateInput(p_pxInputManager, p_Deltatime);
		}
	}
	else 
	{
		UpdateInput(p_pxInputManager, p_Deltatime);
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
	if(m_HasFishingRod)
	{
		if(m_light != nullptr)
		{
			UpdateLightPosition();
		}
	}


	//cout <<"PlayerPos" << GetPosition().x << " " <<  GetPosition().y <<endl;
	//cout <<"lightPos" << m_light->GetPosition().x << " " <<  m_light->GetPosition().y <<endl;
	//cout <<"FilterPos" << p_Camera->GetFilterSprite()->getPosition().x << " " << p_Camera->GetFilterSprite()->getPosition().y <<endl;
	//cout <<"Velocity " << GetVelocity().x << " " <<  GetVelocity().y <<endl;



	if(m_pxCurrentAnimation != nullptr) 
	{
		if(GetCurrentLevel() < 4)
		{
			if( !((GetState() == Death)  && (m_pxCurrentAnimation->GetCurrentFrame() == 5) ) )
			{
				m_pxCurrentAnimation->Update(p_Deltatime);
				m_pxCurrentAnimation->setOrigin(m_pxCurrentAnimation->getTextureRect().width / 2.0f, m_pxCurrentAnimation->getTextureRect().height / 2.0f);
			}
		}
		else
		{
			if( !((GetState() == Death)  && (m_pxCurrentAnimation->GetCurrentFrame() == 13) ) )
			{
				m_pxCurrentAnimation->Update(p_Deltatime);
				m_pxCurrentAnimation->setOrigin(m_pxCurrentAnimation->getTextureRect().width / 2.0f, m_pxCurrentAnimation->getTextureRect().height / 2.0f);
			}

		}

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

void PlayerFishObject::ExperienceGain(int x)
{
	m_Experience += x;
	//cout << "Experience :: " << GetExperience() << endl;
}

void PlayerFishObject::SetExperience(int p_experience)
{
	m_Experience = p_experience;
}

int PlayerFishObject::GetExperience()
{
	return m_Experience;
}

bool PlayerFishObject::UpdateLevel()
{
	if(GetExperience() == 1)
	{
		SetCurrentLevel(2);
		return true;
	}
	else if(GetExperience() == 4)
	{
		SetCurrentLevel(3);
		return true;
	}
	else if(GetExperience() == 1000)
	{
		SetCurrentLevel(4);
		return true;
	}
	else if(GetExperience() == 1001)
	{
		SetCurrentLevel(5);
		return true;
	}
	else if(GetExperience() == 1002)
	{
		SetCurrentLevel(6);
		return true;
	}
	else if(GetExperience() == 1203)
	{
		SetCurrentLevel(7);
		return true;
	}
	else if(GetExperience() == 1204)
	{
		SetCurrentLevel(8);
		return true;
	}
	else if(GetExperience() == 1205)
	{
		SetCurrentLevel(9);
		return true;
	}

	return false;
}

bool PlayerFishObject::HasGrown()
{
	return m_HasGrown;
}

AnimatedSprite* PlayerFishObject::GetCurrentAnimation()
{
	return m_pxCurrentAnimation;
}

void PlayerFishObject::SetGameStatus(bool p_Status)
{
	m_GameOver = p_Status;
}
bool PlayerFishObject::GetGameStatus()
{
	return m_GameOver;
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
	//Look in gameobjectmanager for intersects with light to toggle light on
	if (p_other->GetType() == "Powerup")
	{
		PowerupObject* powerup = dynamic_cast<PowerupObject*>(p_other);

		if(( powerup->GetPowerUpType() == ROD) )
		{
			SetExperience(1000);
			if(UpdateLevel() )
			{
				m_HasGrown = true;
				SetState(Growing);
				m_StageTwo = true;
				m_HasFishingRod = true;
				m_light->ToggleLightOn(false);
			}
		}
		else if(( powerup->GetPowerUpType() == LIGHT) )
		{
			if(m_PowerupLightCounter < 3)
			{
				m_light->SetRadius(m_light->GetRadius() * 1.1f);
				cout << "LIGHT" << endl;
				m_PowerupLightCounter++;
			}
		}
		else if(( powerup->GetPowerUpType() == SPEED) )
		{
			if (m_PowerupSpeedCounter < 3)
			{
				SetSpeed(GetSpeed() * 1.2f);
				cout << "SPEED" << endl;
				m_PowerupSpeedCounter++;
			}		
		}
		else if(( powerup->GetPowerUpType() == ENERGY) )
		{
			if (m_PowerupEnergyCounter < 3)
			{
				SetEnergy(GetEnergy() * 1.1f);
				cout << "ENERGY" << endl;
				cout << GetEnergy() << endl;
				m_PowerupEnergyCounter++;

				if (m_Energy > 100)
				{
					m_Energy = 100;
				}
			}
		}
		powerup = nullptr;
	}
	if (p_other->GetType() == "Enemy")
	{
		EnemyFishObject* tempptr = dynamic_cast<EnemyFishObject*>(p_other);
		if (tempptr->GetSubType() == "Stage2" )
		{
			DamageCooldown();
			if (m_bCanTakeDamage ==true)
			{
				SetHealth(GetHealth() - GetHealth()*.1 - 5);
				//cout<<GetHealth() << endl;
				m_bCanTakeDamage = false;
				DamageCooldown();
			}

			if (GetCurrentLevel() <= 4 && tempptr->GetScale() >= 0.6 && tempptr->GetScale() <= 0.8)
			{
				if (m_bCanTakeDamage)
				{
					SetHealth(GetHealth() - GetHealth()*.33 - 5);
					//cout<<GetHealth() << endl;
					m_bCanTakeDamage = false;
					DamageCooldown();
				}
			}
			if (GetCurrentLevel() <= 4 && tempptr->GetScale() >= 0.8 && tempptr->GetScale() <= 1.0)
			{
				if (m_bCanTakeDamage)
				{
					SetHealth(GetHealth() - GetHealth()*.5 - 5);
					//cout<<GetHealth() << endl;
					m_bCanTakeDamage = false;
					DamageCooldown();
				}
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
			if(m_pxCurrentAnimation->GetCurrentFrame() >= 1)
			{
				if(GetState() != Chewing )
				{
					SetState(Chewing);
					m_pxCurrentAnimation->SetActiveAnimation("Chew");
					m_SoundManager->PlaySound("chew_sound2.wav");
				}
			}

			//std::cout << GetExperience() << std::endl;
			cout << GetCurrentLevel() << endl;
		}
	}
}

void PlayerFishObject::UpdateInput(InputManager *p_pxInputManager, float p_Deltatime)
{
	if( (GetState() != Sneak) && (GetState() != Chewing )  )
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
			if(GetState() != Chewing )
			{
				SetState(Moving);
				m_pxCurrentAnimation->SetActiveAnimation("Move");
			}
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
			if(GetState() != Chewing )
			{
				SetState(Moving);
				m_pxCurrentAnimation->SetActiveAnimation("Move");
			}
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
			if(GetState() != Chewing )
			{
				SetState(Moving);
				m_pxCurrentAnimation->SetActiveAnimation("Move");
			}
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
			if(GetState() != Chewing )
			{
				SetState(Moving);
				m_pxCurrentAnimation->SetActiveAnimation("Move");
			}
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
				if(GetState() != Chewing )
				{
					SetState(Moving);
					m_pxCurrentAnimation->SetActiveAnimation("Move");
				}
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
				if(GetState() != Chewing )
				{
					SetState(Moving);
					m_pxCurrentAnimation->SetActiveAnimation("Move");
				}
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
				if(GetState() != Chewing )
				{
					SetState(Moving);
					m_pxCurrentAnimation->SetActiveAnimation("Move");
				}
				//SetDirection(FacingUp);
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
				if(GetState() != Chewing )
				{
					SetState(Moving);
					m_pxCurrentAnimation->SetActiveAnimation("Move");
				}
				//SetDirection(FacingDown);
			}
		}
	}

	if(p_pxInputManager->IsDownOnceK(sf::Keyboard::Space) )
	{
		/*if(!(GetDirection() == FacingDown || GetDirection() == FacingUp ) )
		{*/
		SetState(Attack);
		m_pxCurrentAnimation->SetActiveAnimation("Dash");
		/*}*/
	}
	else if(p_pxInputManager->IsDownK(sf::Keyboard::LShift)
		|| p_pxInputManager->IsDownK(sf::Keyboard::RShift) 
		|| p_pxInputManager->IsDownK(sf::Keyboard::LControl) 
		|| p_pxInputManager->IsDownK(sf::Keyboard::RControl))
	{
		SetState(Sneak);
		m_pxCurrentAnimation->SetActiveAnimation("Sneak");
	}
	else if(p_pxInputManager->IsReleasedK(sf::Keyboard::LShift)
		|| p_pxInputManager->IsReleasedK(sf::Keyboard::RShift) 
		|| p_pxInputManager->IsReleasedK(sf::Keyboard::LControl) 
		|| p_pxInputManager->IsReleasedK(sf::Keyboard::RControl))
	{
		SetState(Idle);
		m_pxCurrentAnimation->SetActiveAnimation("Idle");
	}

	if(m_HasFishingRod)
	{
		if (m_StageTwo)
		{
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
		}

	}

}

void PlayerFishObject::UpdateIdle(float p_Deltatime)
{
	//ADD slow movement
	/*if(GetDirection() == FacingRight )
	{
	SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed() / 3.0, 0.0f) );
	}
	else if(GetDirection()  == FacingLeft )
	{
	SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed() * GetAttackPower(), 0.0f) );
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
	}*/
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
	else if(GetDirection() == FacingUpRight )
	{
		SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed() * GetAttackPower() * 0.6f, p_Deltatime * -GetSpeed() * GetAttackPower() * 0.6f ) );
	}
	else if(GetDirection()  == FacingUpLeft )
	{
		SetVelocity(sf::Vector2f(p_Deltatime * -GetSpeed() * GetAttackPower() * 0.6f, p_Deltatime * -GetSpeed() * GetAttackPower()  * 0.6f) );
	}
	else if(GetDirection() == FacingDownRight)
	{
		SetVelocity(sf::Vector2f(p_Deltatime * GetSpeed() * GetAttackPower() * 0.6f, p_Deltatime * GetSpeed() * GetAttackPower() * 0.6f) );
	}
	else if(GetDirection()  == FacingDownLeft)
	{
		SetVelocity(sf::Vector2f( p_Deltatime * -GetSpeed() * GetAttackPower()* 0.6f, p_Deltatime * GetSpeed() * GetAttackPower() * 0.6f) );
	}

	if(m_SlowingDown)
	{
		SetAttackPower( GetAttackPower() - 0.25f);
	}
	else
	{
		SetAttackPower( GetAttackPower() + 1.f);
		if(GetAttackPower() > 4.f)
		{
			m_SlowingDown = true;
		}
	}


	m_iAttacktimer += p_Deltatime;
	if(m_iAttacktimer >= 0.4f)
	{
		SetState(Idle);
		m_pxCurrentAnimation->SetActiveAnimation("Idle");
		m_iAttacktimer = 0;
		SetAttackPower(0.0f);
		m_SlowingDown = false;
	}
}

void PlayerFishObject::UpdateChewing(float p_Deltatime)
{
	m_ChewTimer += p_Deltatime;
	if(m_ChewTimer > 0.4f)
	{
		if(m_HasGrown)
		{
			SetState(Growing);
		}
		else
		{
			SetState(Idle);
			m_pxCurrentAnimation->SetActiveAnimation("Idle");
		}
		m_ChewTimer = 0.f;
	}
}

void PlayerFishObject::UpdateDeath(float p_Deltatime,  Camera *p_Camera)
{
	if(m_pxCurrentAnimation->GetCurrentFrame() == 13)
	{
		if(m_LightSprite != nullptr)
		{
			delete m_LightSprite;
			m_LightSprite =  nullptr;
		}
	}

	if(GetCurrentLevel() >= 4)
	{
		if(m_pxCurrentAnimation->GetCurrentFrame() == 13)
		{
			m_DeathTimer += p_Deltatime;
			if(m_light->GetRadius() > 0)
			{
				m_light->SetRadius(m_light->GetRadius() -11.f);
			}
			if(m_DeathTimer >= 1.5f)
			{
				m_GameOver = true;
			}
		}
	}
	else
	{
		m_DeathTimer += p_Deltatime;
		if(m_DeathTimer >= 1.5f)
		{
			m_GameOver = true;
		}
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
		if(m_pxCurrentAnimation->GetCurrentFrame() == 0) { SetPlayerScale(0.7f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 1) { SetPlayerScale(0.5f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 2) { SetPlayerScale(0.7f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 3) { SetPlayerScale(0.6f); }
		p_Camera->SetZoomStrength(1.010f);
		p_Camera->ZoomOut(p_Camera->GetZoomStrength() );
		p_Camera->SetZoomingOut(true);
	}
	else if(GetCurrentLevel() == 2 || GetCurrentLevel() == 5 || GetCurrentLevel() == 8)
	{
		if(m_pxCurrentAnimation->GetActiveAnimation() != "GrowingLevel" )
		{
			m_pxCurrentAnimation->SetActiveAnimation("GrowingLevel");
		}
		if(m_pxCurrentAnimation->GetCurrentFrame() == 0) { SetPlayerScale(0.6f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 1) { SetPlayerScale(0.5f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 2) { SetPlayerScale(0.7f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 3) { SetPlayerScale(0.8f); }
	}
	else if(GetCurrentLevel() == 3 || GetCurrentLevel() == 6 || GetCurrentLevel() == 9)
	{
		if(m_pxCurrentAnimation->GetActiveAnimation() != "GrowingLevel" )
		{
			m_pxCurrentAnimation->SetActiveAnimation("GrowingLevel");
		}
		if(m_pxCurrentAnimation->GetCurrentFrame() == 0) { SetPlayerScale(0.8f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 1) { SetPlayerScale(0.7f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 2) { SetPlayerScale(0.9f); }
		else if(m_pxCurrentAnimation->GetCurrentFrame() == 3) { SetPlayerScale(1.0f); }
	}

	m_GrowTimer += p_Deltatime;
	if(m_GrowTimer > 0.7)
	{

		SetState(Idle);
		m_pxCurrentAnimation->SetActiveAnimation("Idle");
		m_GrowTimer = 0;
		m_HasGrown = false;
		//p_Camera->SetZoomingOut(false);
		if(GetCurrentLevel() == 2 || GetCurrentLevel() == 5 || GetCurrentLevel() == 8)  
		{ 
			SetPlayerScale(0.8f); 
			if(GetCurrentLevel() == 5)
			{
				m_LightbulbPosRelativeToPlayer = sf::Vector2f(204, 43);
				m_LightbulbPosRelativeToPlayer *= GetScale();
			}
		}
		else if (GetCurrentLevel() == 3 || GetCurrentLevel() == 6 || GetCurrentLevel() == 9) 
		{ 
			SetPlayerScale(1.0f); 
			if(GetCurrentLevel() == 6)
			{
				m_LightbulbPosRelativeToPlayer = sf::Vector2f(204, 43);
			}
		}

		if(GetCurrentLevel() == 4) 
		{ 
			ChangeStageAnimation("Stage2", p_SpriteManager); 
			SetPlayerScale(0.6f);
			m_light->SetRadius(m_light->GetRadius() * 3.0f );
			m_LightbulbPosRelativeToPlayer *= GetScale();
			//m_HasFishingRod = true;
		}
		else if( GetCurrentLevel() == 7)  
		{ 
			//ChangeStageAnimation("Stage3", p_SpriteManager); 
			SetPlayerScale(0.6f);
			m_light->SetRadius(m_light->GetRadius() * 1.2f );
			m_LightbulbPosRelativeToPlayer *= GetScale();
		}
	}
	if(GetDirection() == FacingLeft || GetDirection() == FacingUpLeft || GetDirection() == FacingDownLeft ) 
	{
		FlipXLeft(GetScale() );
	}
	else
		FlipXRight(GetScale() );
}
void PlayerFishObject::UpdateEnergy(float p_Deltatime)
{
	if (m_StageTwo)
	{
		if (m_Energy <= 0)
		{
			m_light->ToggleLightOn(false);

		}else if (m_Energy >= 100)
		{

		}
		{
			if (m_light->GetLightStatus())
			{
				m_Energy = m_Energy - (1 - (.3 * m_PowerupEnergyCounter ));

			}else
			{
				if (m_Energy <= 100)
				{
					m_Energy= m_Energy + 0.8;
				}


			}
		}
	}
}

void PlayerFishObject::UpdateHealth(float p_Deltatime)
{
	if(GetState() != Death)
	{
		if(m_Healthtimer >= 0.5f)
		{
			m_Health--;
			m_Healthtimer = 0.f;
			if(GetHealth() == 0)
			{
				SetState(Death);
				m_pxCurrentAnimation->SetActiveAnimation("Death");
			}
		}
		else
		{
			m_Healthtimer+= p_Deltatime;
		}
	}
}


void PlayerFishObject::DamageCooldown()
{


	if (!m_bCanTakeDamage)
	{
		sf::Time elapsed = m_Clock.getElapsedTime();
		if (elapsed.asSeconds() > 2.f)
		{
			m_bCanTakeDamage = true;
			//m_Time = sf::Time::Zero;
			m_Time = m_Clock.restart();
		}
	}

}

void PlayerFishObject::UpdateLightPosition()
{

	{
		if(GetDirection() == FacingDownLeft || GetDirection() == FacingLeft || GetDirection() == FacingUpLeft)
		{
			SetLightPosition(sf::Vector2f(GetPosition().x - m_LightbulbPosRelativeToPlayer.x, GetPosition().y + m_LightbulbPosRelativeToPlayer.y  ) );
			//SetLightPosition(sf::Vector2f(GetPosition().x - 100, GetPosition().y ) );
		}
		else if(GetDirection() == FacingDownRight || GetDirection() == FacingRight || GetDirection() == FacingUpRight)
		{
			SetLightPosition(sf::Vector2f(GetPosition() + m_LightbulbPosRelativeToPlayer ) );
			//SetLightPosition(sf::Vector2f(GetPosition().x + 100, GetPosition().y ) );
		}
	}

}

bool PlayerFishObject::GetStageTwo()
{
	return m_StageTwo;
}

void PlayerFishObject::UpdateSoundFeedback()
{

	if (m_Health < 25)
	{
		//cout << "Less than 25%" << endl;

	}else if (m_Health < 50)
	{
		//cout << "Less than 50%" << endl;

	}
	else if (m_Health < 75)
	{
		//cout << "Less than 75%" << endl;

	}


}

int PlayerFishObject::GetPowerupLightCount()
{
	return m_PowerupLightCounter;
}

int PlayerFishObject::GetPowerupSpeedCount()
{
	return m_PowerupSpeedCounter;
}

int PlayerFishObject::GetPowerupEnergyCount()
{
	return m_PowerupEnergyCounter;
}
