// EnemyFishObject.cpp
#include "stdafx.h"
#include "EnemyFishObject.h"
#include "AnimatedSprite.h"
#include "LightSource.h"
#include "PlayerFishObject.h"
#include "AIState.h"
#include "AIGlobalState.h"
#include <random>
//
//EnemyFishObject::EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite)
//	: GameObject(p_xPosition, p_pxSprite) 
//{
//}
EnemyFishObject::EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite, Collider* p_pxCollider)
	: FishObject(p_xPosition, p_pxSprite,  p_pxCollider) 
{
	isSafe = false;
	SetSpeed(50);
	//SetState(Moving);
	m_iStateTimer = 0;
	SetCurrentLevel(0);
	//SetScale(1.f);
	//m_pxCollider->SetExtention(m_pxCollider->GetExtension()*GetScale());
	SetType("Enemy");
	m_pAIStateMachine = new AIStateMachine<EnemyFishObject>(this);

	m_pAIStateMachine->SetCurrentState(IdleState::Instance());
	m_pAIStateMachine->SetGlobalState(AIGlobalState::Instance());

	GlowRectangle = sf::VertexArray(sf::Quads, 4);
	
	GlowTexture = new sf::Texture;
	GlowTexture->loadFromFile("../data/sprites/enemy2_glow_spritesheet3.png", sf::IntRect(0,0,680,300));

	GlowRectangle[0].position = (sf::Vector2f(0.f,0.f));
	GlowRectangle[1].position = sf::Vector2f(265.f,0.f);
	GlowRectangle[2].position = sf::Vector2f(265.f, 231.f);
	GlowRectangle[3].position = sf::Vector2f(0.f,231.f);

	GlowRectangle[0].color = sf::Color::Red;
	GlowRectangle[1].color = sf::Color::Red;
	GlowRectangle[2].color = sf::Color::Red;
	GlowRectangle[3].color = sf::Color::Red;

	GlowRectangle[0].texCoords = sf::Vector2f(0, 0);
	GlowRectangle[1].texCoords = sf::Vector2f(680+0, 0);
	GlowRectangle[2].texCoords = sf::Vector2f(680+0, 300+0);
	GlowRectangle[3].texCoords = sf::Vector2f(0, 300+0);

}
EnemyFishObject::~EnemyFishObject()
{
	if (m_pAIStateMachine != nullptr)
	{
		delete m_pAIStateMachine;
		m_pAIStateMachine = nullptr;
	}
}

void EnemyFishObject::Update(float deltatime, PlayerFishObject *player)
{
	m_xPlayerPosition = player->GetPosition();
	//2=left 3= right
	m_iPlayerDirection = player->GetDirection();
	m_vPlayerVelocity = player->GetVelocity();
	m_pPlayerLightSource = player->GetLightSource();
	++m_iStateTimer;
	m_pAIStateMachine->Update();



	SetPosition( GetPosition() + GetVelocity()*deltatime );

	if(m_light != nullptr)
	{
		m_light->SetPosition( GetPosition() );
	}

	if(m_pxCollider != nullptr )
	{
		m_pxCollider->SetPosition(GetPosition() );
	}
	setGlowPosition();

}

int EnemyFishObject::random(int min, int max)
{
	int slump;
	slump=rand()%max+(min);
	return slump;
}

void EnemyFishObject::ChangeState()
{
	//	SetState(Idle);
	/*if(GetState() == Moving)
	{
	SetState(Fleeing);
	}
	else if(GetState() == Fleeing)
	{
	SetState(Moving);
	}*/
}


void EnemyFishObject::SetSpawnPosition(sf::Vector2f p_xSpawnPosition)
{
	m_xSpawnPosition = p_xSpawnPosition;
}

sf::Vector2f EnemyFishObject::GetSpawnPosition(sf::Vector2f p_xSpawnPosition)
{
	return m_xSpawnPosition;
}

void EnemyFishObject::SetAttractRadius(float p_fAttractRadius)
{
	m_pxCollider->SetRadius(p_fAttractRadius);
}

void EnemyFishObject::setGlowPosition()
{
	GlowRectangle[0].position = sf::Vector2f(m_pxCollider->GetPosition().x - m_pxCollider->GetExtension().x/2 , m_pxCollider->GetPosition().y - m_pxCollider->GetExtension().y/2);
	GlowRectangle[1].position = sf::Vector2f(m_pxCollider->GetPosition().x + m_pxCollider->GetExtension().x/2 ,  m_pxCollider->GetPosition().y - m_pxCollider->GetExtension().y/2);
	GlowRectangle[2].position = sf::Vector2f(m_pxCollider->GetPosition().x + m_pxCollider->GetExtension().x/2 ,  m_pxCollider->GetPosition().y + m_pxCollider->GetExtension().y /2);
	GlowRectangle[3].position = sf::Vector2f(m_pxCollider->GetPosition().x - m_pxCollider->GetExtension().x /2,  m_pxCollider->GetPosition().y + m_pxCollider->GetExtension().y/2);
	if (this->GetVelocity().x < 0.f)
	{
		sf::Vector2f temp = GlowRectangle[0].position;
		sf::Vector2f temp2 = GlowRectangle[2].position;
		GlowRectangle[0].position = GlowRectangle[1].position;
		GlowRectangle[1].position = temp;
		GlowRectangle[2].position = GlowRectangle[3].position;
		GlowRectangle[3].position = temp2;
	}
}

void EnemyFishObject::OnCollision(GameObject* p_other, sf::Vector2f& p_Offset)
{
	if (GetCollider() != nullptr)
	{


		//std::cout << "EnemyFishObject::OnCollision: " << this->GetType() << "EnemyFishObject::OnCollision other: " << p_other->GetType() << std::endl;
		if (p_other->GetType() == "Player")
		{
			//SetPosition(GetPosition() + p_Offset * 3.f);
			PlayerFishObject *player = dynamic_cast <PlayerFishObject*> (p_other);
			if(player->GetState() == Chewing)
			{
				if(player->GetCurrentAnimation()->GetCurrentFrame() <= 2)
				{
					this->m_pxCollider = nullptr;
					this->~EnemyFishObject();
					m_isDestroyed = true;
				}
			}
			else if (player->GetState() != Chewing)
			{
				if(GetFSM()->CurrentState()->type == "hunting")
				{
					GetFSM()->CurrentState()->Exitstate(this);
				}
			}
			player = nullptr;
		}
		if (p_other->GetType() == "BrownBrick")
		{
			SetPosition(GetPosition() + p_Offset);

			SetVelocity(sf::Vector2f(GetVelocity().x * (-1), GetVelocity().y * (-1)));
		}
	}
}

void EnemyFishObject::Idle()
{
	if (GetSafe())
	{
		SetSafe(false);
	}
	int iRandomX;
	int iRandomY;
	if(GetTimer() > 400)	{ResetTimer();}

	if(GetTimer() == 10)
	{
		iRandomX = random(1, 2);
		//std::cout << iRandomX << std::endl;
		if(iRandomX == 1)
		{
			SetVelocity(sf::Vector2f(GetSpeed() * -1, 0.0f) );
			FlipXLeft(GetScale());
		}
		else if (iRandomX == 2)
		{
			SetVelocity(sf::Vector2f(GetSpeed(), 0.0f));
			FlipXRight(GetScale());
		}
	}
	if(GetTimer() == 100)
	{
		iRandomX = random(1, 2);
		//std::cout << iRandomX << std::endl;
		if(iRandomX == 1)
		{
			SetVelocity(sf::Vector2f(GetSpeed() * -1, 0.0f) );
			FlipXLeft(GetScale());
		}
		else if (iRandomX == 2)
		{
			SetVelocity(sf::Vector2f(GetSpeed(), 0.0f));
			FlipXRight(GetScale());
		}
	}
	if(GetTimer() == 250)
	{
		iRandomY = random(1, 2);
		if (iRandomY == 1)
		{
			SetVelocity(sf::Vector2f(0.0f, GetSpeed()));
		}
		else if (iRandomY == 2)
		{
			SetVelocity(sf::Vector2f(0.0f, GetSpeed()* -1));

		}
	}
}

void EnemyFishObject::Scared()
{
	sf::Vector2f DistanceVector = GetPlayerPosition() - GetPosition();
	float DistanceNumber = DistanceVector.x * DistanceVector.x + DistanceVector.y * DistanceVector.y;
	DistanceVector/=sqrtf(DistanceNumber);
	SetVelocity(-DistanceVector * GetSpeed()*5.f);
	if (GetPosition().x > GetPlayerPosition().x)
	{
		FlipXRight(GetScale());
	}
	if (GetPosition().x < GetPlayerPosition().x)
	{
		FlipXLeft(GetScale());
	}
	if (sqrtf(DistanceNumber) >= 500.f)
	{
		isSafe = true;
	}
}
void EnemyFishObject::Hunting()
{

	sf::Vector2f DistanceVector = GetPlayerPosition() - GetPosition();
	float DistanceNumber = DistanceVector.x * DistanceVector.x + DistanceVector.y * DistanceVector.y;
	DistanceVector/=sqrtf(DistanceNumber);
	SetVelocity(DistanceVector * GetSpeed()*3.f);
	if (GetPlayerPosition().x > GetPosition().x)
	{
		FlipXRight(GetScale());
	}
	if (GetPlayerPosition().x < GetPosition().x)
	{
		FlipXLeft(GetScale());
	}

}

void EnemyFishObject::Attracted()
{
	if(GetPlayerLightSource() != nullptr)
	{
		sf::Vector2f DistanceLightPos = GetPlayerLightSource()->GetPosition() - GetPosition();
		float DistanceNumber = DistanceLightPos.x * DistanceLightPos.x + DistanceLightPos.y * DistanceLightPos.y;

		if (DistanceNumber != 0)
		{
			DistanceLightPos/=sqrtf(DistanceNumber);
			SetVelocity(DistanceLightPos * GetSpeed());
		}
		if (GetVelocity().x < 0)
		{
			FlipXLeft(GetScale());
		}
		if (GetVelocity().x > 0)
		{
			FlipXRight(GetScale());
		}
	}


}