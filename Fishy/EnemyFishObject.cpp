// EnemyFishObject.cpp
#include "stdafx.h"
#include "EnemyFishObject.h"
#include "AnimatedSprite.h"
#include "LightSource.h"
#include "PlayerFishObject.h"
#include "AIState.h"
#include "AIGlobalState.h"
#include <random>
#include <thread>
//
//EnemyFishObject::EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite)
//	: GameObject(p_xPosition, p_pxSprite) 
//{
//}
EnemyFishObject::EnemyFishObject(std::string p_subtype, sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite, Collider* p_pxCollider, SpriteManager* p_SpriteManager)
	: FishObject(p_xPosition, p_pxSprite,  p_pxCollider) 
{
	m_SubType = p_subtype;
	isSafe = false;
	SetSpeed(50);
	m_iStateTimer = 0;
	SetCurrentLevel(0);
	SetType("Enemy");
	m_pAIStateMachine = new AIStateMachine<EnemyFishObject>(this);

	m_pAIStateMachine->SetCurrentState(IdleState::Instance());
	m_pAIStateMachine->SetGlobalState(AIGlobalState::Instance());

	GlowRectangle = sf::VertexArray(sf::Quads, 4);

	
	if (GetSubType() == "Stage1")
	{
		GlowTexture = p_SpriteManager->GetTexture("enemy2_finalglowsheet.png");
		GlowRectangle[0].texCoords = sf::Vector2f(0, 0);
		GlowRectangle[1].texCoords = sf::Vector2f(571+0, 0);
		GlowRectangle[2].texCoords = sf::Vector2f(571+0, 235+0);
		GlowRectangle[3].texCoords = sf::Vector2f(0, 235+0);
	}
	else if (GetSubType() == "Stage2")
	{
		GlowTexture = p_SpriteManager->GetTexture("enemy1_finalglowsheet.png");//3:::::::326.f, 362.f+169.f 4:::326.f+323.f, 362.f+169.f
		GlowRectangle[0].texCoords = sf::Vector2f(326.f, 362.f);
		GlowRectangle[1].texCoords = sf::Vector2f(326.f+323.f, 362.f);
		GlowRectangle[2].texCoords = sf::Vector2f(326.f+323.f, 362.f+169.f);
		GlowRectangle[3].texCoords = sf::Vector2f(326.f, 362.f+169.f );
	}
	else if (GetSubType() == "Stage3")
	{
		GlowTexture = p_SpriteManager->GetTexture("enemy3_finalglowsheet.png");
		GlowRectangle[0].texCoords = sf::Vector2f(2319.f, 0);
		GlowRectangle[1].texCoords = sf::Vector2f(2319.f+772.f, 0);
		GlowRectangle[2].texCoords = sf::Vector2f(2319.f+772.f, 596.f);
		GlowRectangle[3].texCoords = sf::Vector2f(2319.f, 596.f);
	}


	GlowRectangle[0].position = (sf::Vector2f(0.f,0.f));
	GlowRectangle[1].position = sf::Vector2f(571,0.f);
	GlowRectangle[2].position = sf::Vector2f(571.f, 235.f);
	GlowRectangle[3].position = sf::Vector2f(0.f,235.f);

	//GlowRectangle[0].color = sf::Color::Red;
	//GlowRectangle[1].color = sf::Color::Red;
	//GlowRectangle[2].color = sf::Color::Red;
	//GlowRectangle[3].color = sf::Color::Red;



}
EnemyFishObject::~EnemyFishObject()
{
	if (m_pAIStateMachine != nullptr)
	{
		delete m_pAIStateMachine;
		m_pAIStateMachine = nullptr;
	}

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
}

void EnemyFishObject::Update(float deltatime, PlayerFishObject *player)
{

	m_pxCurrentAnimation->SetActiveAnimation("Idle");

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

	if(m_pxCurrentAnimation != nullptr) 
	{
		m_pxCurrentAnimation->Update(deltatime);
		m_pxCurrentAnimation->setOrigin(m_pxCurrentAnimation->getTextureRect().width / 2.0f, m_pxCurrentAnimation->getTextureRect().height / 2.0f);
	}


	if(m_pxCollider != nullptr )
	{
		m_pxCollider->SetPosition(GetPosition() );
	}

	setGlowPosition();
	

}


void EnemyFishObject::SetEnemyScale(float x)
{
	SetScale(x);

	std::map<std::string, AnimatedSprite*>::iterator it = m_mpAnimations.begin();
	while(it != m_mpAnimations.end() )
	{
		it->second->setScale(GetScale(),GetScale());
		it++;
	}
}

void EnemyFishObject::AddAnimation(const std::string &p_sName, AnimatedSprite *p_pxAnimSprite)
{
	m_mpAnimations.insert(std::pair<std::string,AnimatedSprite*>(p_sName, p_pxAnimSprite));
	if(	m_pxSprite == nullptr) 
	{
		m_pxSprite = p_pxAnimSprite;
		m_pxCurrentAnimation = p_pxAnimSprite;
	}
	SetEnemyScale(GetScale());
}

AnimatedSprite* EnemyFishObject::GetCurrentAnimation()
{
	return m_pxCurrentAnimation;
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
	if (this->GetVelocity().x < 0.f && GetSubType() != "Stage2")
	{
		sf::Vector2f temp = GlowRectangle[0].position;
		sf::Vector2f temp2 = GlowRectangle[2].position;
		GlowRectangle[0].position = GlowRectangle[1].position;
		GlowRectangle[1].position = temp;
		GlowRectangle[2].position = GlowRectangle[3].position;
		GlowRectangle[3].position = temp2;
	}
	else if (this->GetVelocity().x > 0.f && GetSubType() == "Stage2")
	{
		sf::Vector2f temp = GlowRectangle[0].position;
		sf::Vector2f temp2 = GlowRectangle[2].position;
		GlowRectangle[0].position = GlowRectangle[1].position;
		GlowRectangle[1].position = temp;
		GlowRectangle[2].position = GlowRectangle[3].position;
		GlowRectangle[3].position = temp2;
	}
}

void EnemyFishObject::UpdateGlow()
{
	if(m_pxCurrentAnimation->GetActiveAnimation() == "Idle")
	{


		/*UpdateGlowTexture();*/
		/*UpdateGlowTexture(2);
		UpdateGlowTexture(3);
		UpdateGlowTexture(4);*/


	}
}
void EnemyFishObject::UpdateGlowTexture()
{



	sf::sleep(sf::milliseconds(100));
	GlowRectangle[0].texCoords = sf::Vector2f(579.0f,0.0f);
	GlowRectangle[1].texCoords = sf::Vector2f(579.0f+565.0f,0.0f);
	GlowRectangle[2].texCoords = sf::Vector2f(579.0f+565.0f,228.0f);
	GlowRectangle[3].texCoords = sf::Vector2f(579.0f,228.0f);



	sf::sleep(sf::milliseconds(200));
	GlowRectangle[0].texCoords = sf::Vector2f(579.0f,229.0f);
	GlowRectangle[1].texCoords = sf::Vector2f(579.0f+567.0f,229.f);
	GlowRectangle[2].texCoords = sf::Vector2f(579.0f+567.0f,229+228.0f);
	GlowRectangle[3].texCoords = sf::Vector2f(579.0f,229.0f+228.0f);



	sf::sleep(sf::milliseconds(300));
	GlowRectangle[0].texCoords = sf::Vector2f(579.0f,458.0f);
	GlowRectangle[1].texCoords = sf::Vector2f(579.0f+567.0f,458.0f);
	GlowRectangle[2].texCoords = sf::Vector2f(579.0f+567.0f,458.0f+228.0f);
	GlowRectangle[3].texCoords = sf::Vector2f(579.0f,458.0f+229.0f);



	sf::sleep(sf::milliseconds(400));
	GlowRectangle[0].texCoords = sf::Vector2f(1147.0f,0.0f);
	GlowRectangle[1].texCoords = sf::Vector2f(1147.0f+567.0f,0.0f);
	GlowRectangle[2].texCoords = sf::Vector2f(1147.0f+567.0f,228.0f);
	GlowRectangle[3].texCoords = sf::Vector2f(1147.0f,229.0f);


}

void GameObject::SetColor(sf::Color p_color)
{
	GlowRectangle[0].color = p_color;
	GlowRectangle[1].color = p_color;
	GlowRectangle[2].color = p_color;
	GlowRectangle[3].color = p_color;
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
					//en fuling
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
			if (GetSubType() != "Stage2")
			{
				SetVelocity(sf::Vector2f(GetSpeed() * -1, 0.0f) );
				FlipXLeft(GetScale());
			}
			else if(GetSubType() == "Stage2")
			{
				SetVelocity(sf::Vector2f(GetSpeed() * -1, 0.0f) );
				FlipXRight(GetScale());
			}
		}
		else if (iRandomX == 2)
		{
			if (GetSubType() != "Stage2")
			{
				SetVelocity(sf::Vector2f(GetSpeed() * 1, 0.0f) );
				FlipXRight(GetScale());
			}
			else if(GetSubType() == "Stage2")
			{
				SetVelocity(sf::Vector2f(GetSpeed() * 1, 0.0f) );
				FlipXLeft(GetScale());
			}
		}
	}
	if(GetTimer() == 100)
	{
		iRandomX = random(1, 2);
		//std::cout << iRandomX << std::endl;
		if(iRandomX == 1)
		{
			if (GetSubType() != "Stage2")
			{
				SetVelocity(sf::Vector2f(GetSpeed() * -1, 0.0f) );
				FlipXLeft(GetScale());
			}
			else if(GetSubType() == "Stage2")
			{
				SetVelocity(sf::Vector2f(GetSpeed() * -1, 0.0f) );
				FlipXRight(GetScale());
			}
		}
		else if (iRandomX == 2)
		{
			if (GetSubType() != "Stage2")
			{
				SetVelocity(sf::Vector2f(GetSpeed() * 1, 0.0f) );
				FlipXRight(GetScale());
			}
			else if(GetSubType() == "Stage2")
			{
				SetVelocity(sf::Vector2f(GetSpeed() * 1, 0.0f) );
				FlipXLeft(GetScale());
			}
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
		if (GetSubType() != "Stage2")
		{
			FlipXRight(GetScale());
		}
		else if (GetSubType() == "Stage2")
		{
			FlipXLeft(GetScale());
		}

	}
	if (GetPosition().x < GetPlayerPosition().x)
	{
		if (GetSubType() != "Stage2")
		{
			FlipXLeft(GetScale());
		}
		else if (GetSubType() == "Stage2")
		{
			FlipXRight(GetScale());
		}
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
		if (GetSubType() != "Stage2")
		{
			FlipXRight(GetScale());
		}
		else if (GetSubType() == "Stage2")
		{
			FlipXLeft(GetScale());
		}
	}
	if (GetPlayerPosition().x < GetPosition().x)
	{
		if (GetSubType() != "Stage2")
		{
			FlipXLeft(GetScale());
		}
		else if (GetSubType() == "Stage2")
		{
			FlipXRight(GetScale());
		}
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
			if (GetSubType() != "Stage2")
		{
			FlipXLeft(GetScale());
		}
		else if (GetSubType() == "Stage2")
		{
			FlipXRight(GetScale());
		}
		}
		if (GetVelocity().x > 0)
		{
			if (GetSubType() != "Stage2")
		{
			FlipXRight(GetScale());
		}
		else if (GetSubType() == "Stage2")
		{
			FlipXLeft(GetScale());
		}
		}
	}


}