// GameObjectManager.cpp
#include "stdafx.h"
#include "GameObjectManager.h"

//include all objects in stdafx.h eller här?

#include "InputManager.h"
#include "Camera.h"

#include "PlayerFishObject.h"
#include "EnemyFishObject.h"
#include "PowerupObject.h"
#include "LightSource.h"

GameObjectManager::GameObjectManager(InputManager *p_pxInputManager)
{
	m_iEnenmyCounter = 0;
	m_pxInputManager = p_pxInputManager;
	m_pxPlayer = nullptr;
}
GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Cleanup()
{
	if(m_pxPlayer != nullptr)
	{
		delete m_pxPlayer;
		m_pxPlayer = nullptr;
	}
	//Delete GameObjects
	{
		auto it = m_apxGameObject.begin();
		while(it != m_apxGameObject.end() )
		{
			delete (*it);
			it++;
		}
		m_apxGameObject.clear();
	}
	
}

//attach objects
void GameObjectManager::Attach(GameObject *p_pxGameObject)
{
	m_apxGameObject.push_back(p_pxGameObject);
	if (dynamic_cast<EnemyFishObject*>(p_pxGameObject))
	{
		m_iEnenmyCounter++;
	}
}
void GameObjectManager::AttachPlayer(PlayerFishObject *p_pxPlayer)
{
	m_pxPlayer = p_pxPlayer;
}

void GameObjectManager::DestroyEnemy(EnemyFishObject *p_pxEnemy)
{
	if(p_pxEnemy != nullptr)
	{
		delete p_pxEnemy;
		p_pxEnemy = nullptr;
	}
	--m_iEnenmyCounter;
}

void GameObjectManager::DestroyPowerup(PowerupObject *p_pxPowerup)
{
	if(p_pxPowerup != nullptr)
	{
		delete p_pxPowerup;
		p_pxPowerup = nullptr;
	}
}

//Update functions
void GameObjectManager::UpdateAllObjects(float p_fDeltatime)
{

	for(int i = 0UL; i < m_apxGameObject.size(); i++)
	{
		if(m_apxGameObject[i]->GetActive() )
		{
			if(m_apxGameObject[i]->HasLight())
			{
				if(m_pxPlayer->GetLightSource()->GetLightStatus() )
				{
					if(m_pxPlayer->GetLightSprite()->getGlobalBounds().intersects(m_apxGameObject[i]->GetLightSprite()->getGlobalBounds() ) )
					{
						m_apxGameObject[i]->GetLightSource()->ToggleLightOn(true);
					}
				}
			}
			//if (m_apxGameObject[i]->GetType() != "GameObject")
			if(dynamic_cast<EnemyFishObject*> (m_apxGameObject[i]) )
			{
				dynamic_cast<EnemyFishObject*> (m_apxGameObject[i])->Update(p_fDeltatime, m_pxPlayer);
			}
			else if(dynamic_cast<PowerupObject*> (m_apxGameObject[i]) )
			{
				dynamic_cast<PowerupObject*> (m_apxGameObject[i])->Update(p_fDeltatime);
			}
			else
			{
				m_apxGameObject[i]->Update(p_fDeltatime);
			}
			if (m_apxGameObject[i]->GetCollider() == nullptr && m_apxGameObject[i]->GetLevelLayer() == ELayer::MIDDLEGROUND)
			{
				if( static_cast<EnemyFishObject*> (m_apxGameObject[i])->GetDestroyed() )
				{
					DestroyEnemy(dynamic_cast<EnemyFishObject*> (m_apxGameObject[i]) );
					m_apxGameObject.erase(m_apxGameObject.begin() +i);
				}
				else if( static_cast<PowerupObject*> (m_apxGameObject[i])->GetDestroyed() )
				{
					DestroyPowerup(dynamic_cast<PowerupObject*> (m_apxGameObject[i]) );
					m_apxGameObject.erase(m_apxGameObject.begin() +i);
				}
			}
		}
		else
		{
			if(dynamic_cast<EnemyFishObject*> (m_apxGameObject[i]) )
			{
				dynamic_cast<EnemyFishObject*> (m_apxGameObject[i])->SetEnemyScale(dynamic_cast<EnemyFishObject*> (m_apxGameObject[i])->GetScale() );
			}
		}

	}
}