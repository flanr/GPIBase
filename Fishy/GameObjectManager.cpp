// GameObjectManager.cpp
#include "stdafx.h"
#include "GameObjectManager.h"

//include all objects in stdafx.h eller här?


#include "InputManager.h"

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
	//m_pxLight = nullptr;
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
			delete (*it)->GetCollider();
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
	//Delete Terrain Objects
	//{

	//	auto it = m_apxTerrain.begin();
	//	while(it != m_apxTerrain.end() )
	//	{
	//		/*delete (*it)->GetSprite();
	//		delete (*it)->GetCollider();*/
	//		delete (*it);
	//		it++;
	//	}
	//	m_apxTerrain.clear();
	//}

	//Delete Enemy Objects
	//{
	//	auto it = m_apxEnemy.begin();
	//	while(it != m_apxEnemy.end() )
	//	{
	//		/*delete (*it)->GetSprite();
	//		or delete (*it->GetAnimatedSprite();
	//		delete (*it)->GetCollider();*/
	//		delete (*it);
	//		it++;
	//	}
	//	m_apxEnemy.clear();
	//}

	//Delete Powerup Objects
	//{
	//	auto it = m_apxPowerup.begin();
	//	while(it != m_apxPowerup.end() )
	//	{
	//		/*delete (*it)->GetSprite();
	//		delete (*it)->GetCollider();*/
	//		delete (*it);
	//		it++;
	//	}
	//	m_apxPowerup.clear();
	//}

	//Delete Info Objects
	//{
	//	auto it = m_apxInfoObject.begin();
	//	while(it != m_apxInfoObject.end() )
	//	{
	//		/*delete (*it)->GetSprite();
	//		delete (*it)->GetCollider();*/
	//		delete (*it);
	//		it++;
	//	}
	//	m_apxInfoObject.clear();
	//}

	//Delete Trap Objects
	//{
	//	auto it = m_apxTrapObject.begin();
	//	while(it != m_apxTrapObject.end() )
	//	{
	//		/*delete (*it)->GetSprite();
	//		delete (*it)->GetCollider();*/
	//		delete (*it);
	//		it++;
	//	}
	//	m_apxTrapObject.clear();
	//}

	//Delete Particle Objects
	//{
	//	auto it = m_apxParticles.begin();
	//	while(it != m_apxParticles.end() )
	//	{
	//		/*delete (*it)->GetSprite();
	//		delete (*it)->GetCollider();*/
	//		delete (*it);
	//		it++;
	//	}
	//	m_apxParticles.clear();
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

/*Test function, to load player*/
bool GameObjectManager::LoadFish(const string &p_sFileName, SpriteManager *p_pSpriteManager)
{
	/*Collider *collider = new Collider(sf::Vector2f(0.f, 0.f),sf::Vector2f(352.f, 287.f) );

	PlayerFishObject *Player = new PlayerFishObject(sf::Vector2f(0.f, 0.f ), nullptr, collider);
	AnimatedSprite *pxAnimSprite = p_pSpriteManager->LoadAnim(p_sFileName);	
	Player->AddAnimation("Idle", pxAnimSprite);
	AttachPlayer(Player);*/
	return true;
}

//void GameObjectManager::AttachLight(LightObject *p_pxLight)
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
//void GameObjectManager::DestroyEnemy(EnemyFishObject *p_pxEnemy)
//{
//	
//	if(p_pxEnemy != nullptr)
//	{
//		int iVectorPosition;
//		for(int i = 0; i < m_apxEnemy.size(); i ++)
//		{
//			if(m_apxEnemy[i] == p_pxEnemy)
//			{
//				iVectorPosition = i;
//				/*delete p_apxEnemy->GetAnimSprite();
//				delete p_apxEnemy->GetCollider();*/
//				delete p_pxEnemy;
//				p_pxEnemy = nullptr;
//			}
//		}
//		m_apxEnemy.erase(m_apxEnemy.begin() + iVectorPosition);
//	}
//}
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


////Update functions
void GameObjectManager::UpdateAllObjects(float p_fDeltatime)
{

	for(int i = 0UL; i < m_apxGameObject.size(); i++)
	{
		m_apxGameObject[i]->Update(p_fDeltatime);
	}

	if(m_pxPlayer != nullptr)
	{
		m_pxPlayer->Update(m_pxInputManager, p_fDeltatime);
	}

	/*for ( auto element : m_apxGameObject )
	{
	element->Update(p_fDeltatime);
	}*/
	/*UpdatePlayer(p_fDeltatime);
	UpdateTerrain(p_fDeltatime);
	UpdateEnemies(p_fDeltatime);
	UpdatePowerups(p_fDeltatime);
	UpdateInfoObjects(p_fDeltatime);
	UpdateTrapObjects(p_fDeltatime);*/
	//UpdateParticles(p_fDeltatime);
}

//void GameObjectManager::UpdatePlayer(float p_fDeltatime)
//{
//	//Ex
//	//if(m_pxPlayer != nullptr)
//	//{
//	//	m_pxPlayer->Update(p_fDeltatime, p_pxInputManager);
//	//}
//}
//void GameObjectManager::UpdateTerrain(float p_fDeltatime)
//{
//	//uppdatera Terrain
//}
//void GameObjectManager::UpdateEnemies(float p_fDeltatime)
//{
//	//uppdatera Enemies
//}
//void GameObjectManager::UpdatePowerups(float p_fDeltatime)
//{
//	//uppdatera Powerups
//}
//void GameObjectManager::UpdateInfoObjects(float p_fDeltatime)
//{
//	//uppdatera info Objects
//}
//void GameObjectManager::UpdateTrapObjects(float p_fDeltatime)
//{
//	//uppdatera Trap Objects
//}
////void GameObjectManager::UpdateParticles(float p_fDeltatime) // Uppdaterar position, velocity // opacity?
////{
////}