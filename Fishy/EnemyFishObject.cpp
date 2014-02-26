// EnemyFishObject.cpp
#include "stdafx.h"
#include "EnemyFishObject.h"
#include "PlayerFishObject.h"
//
//EnemyFishObject::EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite)
//	: GameObject(p_xPosition, p_pxSprite) 
//{
//}
EnemyFishObject::EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite, Collider* p_pxCollider)
	: FishObject(p_xPosition, p_pxSprite,  p_pxCollider) 
{
	SetSpeed(50);
	SetState(Moving);
	m_iStateTimer = 0;
	m_collisionManager = new CollisionManager;
	//SetScale(0.2f);
	//m_pxCollider->SetExtention(m_pxCollider->GetExtension()*GetScale());
	SetType("Enemy");
}
EnemyFishObject::~EnemyFishObject()
{
	//Delete Sprite
	
	if(GetSprite() != nullptr)
	{
		delete  GetSprite();
	}
	
	/*if (m_collisionManager != nullptr)
	{
		delete m_collisionManager;
		m_collisionManager = nullptr;
	}*/
	////Delete Collider
	//if(GetCollider() != nullptr)
	//{
	//	delete  GetCollider();
	//}
	//
}

void EnemyFishObject::Update(float deltatime, PlayerFishObject *player)
{

	SetVelocity(sf::Vector2f(0.0f, 0.0f));

	float delta_x = m_xPosition.x - player->GetPosition().x;
	float delta_y = m_xPosition.y - player->GetPosition().y;
	sf::Vector2f distance_to_light;
	distance_to_light.x = delta_x;
	distance_to_light.y = delta_y;


	m_iStateTimer++;
	if(m_iStateTimer >= 400)
	{		
		m_iStateTimer = 0;
	}
	if ((player->GetPosition().x > m_xPosition.x) && (player->GetDirection() == FacingRight))
	{
		SetState(Attack);
	}
	else if ((player->GetPosition().x > m_xPosition.x) && (player->GetDirection() == FacingRight))
	{
		SetState(Fleeing);
	}

	if(GetState() == Idle)
	{

		if(m_iStateTimer > 250)
		{
			SetVelocity(sf::Vector2f(deltatime * -GetSpeed(), 0.0f) );
			//SetScale(GetScale());
			FlipXLeft(1.0f);
			
		}
		else
		{
			SetVelocity(sf::Vector2f(deltatime * GetSpeed(), 0.0f) );
			//SetScale(GetScale());
			FlipXRight(1.f);
			
		}
	}

	if(GetState() == Fleeing)
	{

		//	if (fabs(delta_x) <= 200 && fabs(delta_y) <= 200 && (player->GetPosition().x > m_xPosition.x) && (player->GetDirection() == FacingRight))
		//{
		//	//distace to player
		//	m_velocity += distance_to_light * GetSpeed();

		//	m_xPosition += m_velocity * deltatime;
		//}

		//if (fabs(delta_x) <= 200 && fabs(delta_y) <= 200 && (player->GetPosition().x < m_xPosition.x) && (player->GetDirection() == FacingLeft))
		//{
		//	//distace to player
		//	m_velocity += distance_to_light * GetSpeed();

		//	m_xPosition += m_velocity * deltatime;
		//}

		SetVelocity(sf::Vector2f(0.0f, deltatime * GetSpeed()) );
	};

	if(GetState() == Attack)
	{
		SetVelocity(sf::Vector2f(0.0f, deltatime * -GetSpeed()) );
	};

	SetPosition( GetPosition() + GetVelocity() );
	if (m_collisionManager->b_playerVsenemy)
	{
		m_pxCollider = nullptr;
		m_collisionManager->SetPlayerVsEnemy(false);
	}
	if(m_pxCollider != nullptr )
	{
		m_pxCollider->SetPosition(GetPosition() );
	}

}

void EnemyFishObject::ChangeState()
{

	if(GetState() == Moving)
	{
		SetState(Fleeing);
	}
	else if(GetState() == Fleeing)
	{
		SetState(Moving);
	}
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
void EnemyFishObject::OnCollision(GameObject* p_other)
{
	//std::cout << "EnemyFishObject::OnCollision: " << this->GetType() << "EnemyFishObject::OnCollision other: " << p_other->GetType() << std::endl;
	if (p_other->GetType() == "Player")
	{
		this->m_pxCollider = nullptr;
		this->~EnemyFishObject();
	}
	

}