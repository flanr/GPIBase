// GameObjectManager.cpp
#include "stdafx.h"
#include "GameObjectManager.h"

//include all objects in stdafx.h eller här?


#include "InputManager.h"
#include "Camera.h"

//#include "TerrainObject.h"
#include "PlayerFishObject.h"
//#include "LightObject.h"
#include "EnemyFishObject.h"
//#include "PowerupObject.h"
//#include "InfoObject.h"
//#include "TrapObject.h"
//#include "ParticleObject.h"

GameObjectManager::GameObjectManager(InputManager *p_pxInputManager)
{
	m_pxInputManager = p_pxInputManager;
	m_pxPlayer = nullptr;
}
GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Cleanup()
{
	//Delete GameObjects
	{
		auto it = m_apxGameObject.begin();
		while(it != m_apxGameObject.end() )
		{
			/*if((*it)->HasAnimSprite()
			{
			delete (*it->GetAnimatedSprite();
			}
			else
			{
			delete (*it)->GetSprite();
			}*/
			delete (*it)->GetSprite();
			//delete (*it)->GetCollider();
			delete (*it);
			it++;
		}
		m_apxGameObject.clear();
	}
	//Delete Player Fish
	//if(m_pxPlayer != nullptr) 
	//{
	//	/*delete m_pxPlayer->GetSprite();
	//	or delete (*it->GetAnimatedSprite();
	//	delete m_pxPlayer->GetCollider();*/
	//	delete m_pxPlayer;
	//	m_pxPlayer = nullptr;
	//}

	//Delete Player Light
	//if(m_pxLight != nullptr) 
	//{
	//	/*delete m_pxLight->GetSprite();
	//	delete m_pxLight->GetCollider();
	//	delete m_pxLight->GetCircleCollider();*/
	//	delete m_pxLight;
	//	m_pxLight = nullptr;
	//}
}

//attach objects
void GameObjectManager::Attach(GameObject *p_pxGameObject)
{
	m_apxGameObject.push_back(p_pxGameObject);
}
void GameObjectManager::AttachPlayer(PlayerFishObject *p_pxPlayer)
{
	m_pxPlayer = p_pxPlayer;
}

//void GameObjectManager::AttachLight(LightSource *p_pxLight)
//{
//	m_pxLight = p_pxLight;
//}

//void GameObjectManager::AttachTerrain(TerrainObject *p_pxTerrain)
//{
//	m_apxTerrain.push_back(p_pxTerrain);
//}
//void GameObjectManager::AttachEnemy(EnemyFishObject *p_pxEnemy)
//{
//	m_apxEnemy.push_back(p_pxEnemy);
//}
//void GameObjectManager::AttachPowerup(PowerupObject *p_pxPowerup)
//{
//	m_apxPowerup.push_back(p_pxPowerup);
//}
//void GameObjectManager::AttachInfo(InfoObject *p_pxInfoObject)
//{
//	m_apxInfoObject.push_back(p_pxInfoObject);
//}
//void GameObjectManager::AttachTrap(TrapObject *p_pxTrapObject)
//{
//	m_apxTrapObject.push_back(p_pxTrapObject);
//}
///*void GameObjectManager::AttachParticle(ParticleObject * p_pxParticle)
//{
//m_apxParticles.push_back(p_pxParticle);
//}*/

//Create new objects during gameplay
//void GameObjectManager::CreateNewEnemy(EnemyFishObject *p_pxEnemy)
//{
//}
//void GameObjectManager::CreateNewPowerup(PowerupObject *p_pxPowerup)
//{
//}
//void GameObjectManager::CreateParticles(int p_iAmount)
//{
//}


//Add Animations to objects or maybe load/add them some other place?
//void GameObjectManager::AddPlayerAnimation(PlayerFishObject *p_pxPlayer)
//{
//		/*AnimatedSprite *p_pxPlayer = m_pxSpriteManager->LoadAnim("..filename");		
//		p_pxPlayer->AddAnimation("Move",p_pxPlayer);*/
//}
//void GameObjectManager::AddEnemyAnimation(EnemyFishObject *p_pxEnemy)
//{
//	/*AnimatedSprite *p_pxEnemy = m_pxSpriteManager->LoadAnim("..filename");		
//	p_pxEnemy->AddAnimation("Move",p_pxEnemy);*/
//}
//void GameObjectManager::AddParticleAnimation(ParticleObject * p_pxParticle)
//{
//}


////Destroy Functions for objects that can be destroyed in game
//void GameObjectManager::DestroyPlayer()
//{
//	//Destroy Player
//	if(m_pxPlayer != nullptr) 
//	{
//		/*delete m_pxPlayer->GetSprite();
//		or delete m_pxPlayer->GetAnimSprite();
//		delete m_pxPlayer->GetCollider();*/
//		delete m_pxPlayer;
//		m_pxPlayer = nullptr;
//	}
//	//Destroy player light
//	if(m_pxLight != nullptr) 
//	{
//		/*delete m_pxLight->GetSprite();
//		delete m_pxLight->GetCollider();*/
//		delete m_pxLight;
//		m_pxLight = nullptr;
//	}
//}
void GameObjectManager::DestroyEnemy(EnemyFishObject *p_pxEnemy, int p_Index)
{

	if(p_pxEnemy != nullptr)
	{
		delete p_pxEnemy;
		p_pxEnemy = nullptr;
	}

	//m_apxGameObject.erase(m_apxGameObject.begin() + p_Index);
}

//void GameObjectManager::DestroyPowerup(PowerupObject *p_pxPowerup)
//{
//	if(p_pxPowerup != nullptr)
//	{
//		int iVectorPosition;
//		for(int i = 0; i < m_apxPowerup.size(); i ++)
//		{
//			if(m_apxPowerup[i] == p_pxPowerup)
//			{
//				iVectorPosition = i;
//				/*delete p_pxPowerup->GetSprite();
//				delete p_pxPowerup->GetCollider();*/
//				delete p_pxPowerup;
//				p_pxPowerup = nullptr;
//			}
//		}
//		m_apxPowerup.erase(m_apxPowerup.begin() + iVectorPosition);
//	}
//}
//void GameObjectManager::DestroyInfoObject(InfoObject *p_pxInfoObject)
//{
//	if(p_pxInfoObject != nullptr)
//	{
//		int iVectorPosition;
//		for(int i = 0; i < m_apxInfoObject.size(); i ++)
//		{
//			if(m_apxInfoObject[i] == p_pxInfoObject)
//			{
//				iVectorPosition = i;
//				/*delete p_pxInfoObject->GetSprite();
//				delete p_pxInfoObject->GetCollider();*/
//				delete p_pxInfoObject;
//				p_pxInfoObject = nullptr;
//			}
//		}
//		m_apxInfoObject.erase(m_apxInfoObject.begin() + iVectorPosition);
//	}
//}

/*
void GameObjectManager::DestroyParticle(ParticleObject * p_pxParticle)
{
if(p_pxParticle != nullptr)
{
int iVectorPosition;
for(int i = 0; i < m_apxParticles.size(); i ++)
{
if(m_apxParticles[i] == p_pxParticle)
{
iVectorPosition = i;
//delete p_pxParticle->GetSprite();
//delete p_pxParticle->GetCollider();
delete p_pxParticle;
p_pxParticle = nullptr;
}
}
m_apxParticles.erase(m_apxParticles.begin() + iVectorPosition);
}

}
*/


//Update functions
void GameObjectManager::UpdateAllObjects(float p_fDeltatime, Camera * p_Camera)
{

	for(int i = 0UL; i < m_apxGameObject.size(); i++)
	{

		if(dynamic_cast<EnemyFishObject*> (m_apxGameObject[i]) )
		{
			dynamic_cast<EnemyFishObject*> (m_apxGameObject[i])->Update(p_fDeltatime, m_pxPlayer);
		}
		else
		{
			m_apxGameObject[i]->Update(p_fDeltatime);
		}
		if (m_apxGameObject[i]->GetCollider() == nullptr && m_apxGameObject[i]->GetLevelLayer() == ELayer::MIDDLEGROUND)
		{
			m_apxGameObject.erase(m_apxGameObject.begin() +i);
		}

	}
}
		//if(m_apxGameObject[i]->HasCollider() )
		//{
		//	if( m_apxGameObject[i]->GetCollider() )
		//	{
		//		std::cout << "Destroying: " << m_apxGameObject[i]->GetType() << std::endl;
		//		m_apxGameObject[i]->SetDestroyed(true);
		//	}

		//	if( static_cast<EnemyFishObject*> (m_apxGameObject[i])->GetDestroyed() )
		//	{

		//		DestroyEnemy(dynamic_cast<EnemyFishObject*> (m_apxGameObject[i]), i);
		//		//DestroyEnemy( (EnemyFishObject*) m_apxGameObject[i], i);
		//		m_apxGameObject.erase(m_apxGameObject.begin() + i);
		//		m_pxPlayer->SetHealth(m_pxPlayer->GetHealth() + 10);
		//	}
		//}
	//if(m_pxPlayer != nullptr)
	//{

	//	m_pxPlayer->Update(m_pxInputManager, Camera, p_fDeltatime);
	//	if(m_pxPlayer->GetCollider()->GetStatus() == true)
	//	{
	//		m_pxPlayer->SetDestroyed(false);
	//	}
	//}


	/*for ( auto element : m_apxGameObject )
	{
	element->Update(p_fDeltatime);
	}*/
