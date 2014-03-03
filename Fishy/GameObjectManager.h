// GameObjectManager.h
#pragma once

class InputManager;

class GameObject;
class PlayerFishObject;
//class LightSource;
class PowerupObject;

//class TerrainObject;
class EnemyFishObject;

//class InfoObject;
//class TrapObject;
//class ParticleObject;

class GameObjectManager
{
	friend class Level;
	friend class GameState;
	friend class Camera;
public:
	GameObjectManager(InputManager *p_pxInputManager);
	~GameObjectManager();
	
	void Cleanup();
	
	//attach objects
	void Attach(GameObject *p_pxGameObject);
	void AttachPlayer(PlayerFishObject *p_pxPlayer);
	//bool LoadFish(const string &p_sFileName, SpriteManager *p_pSpriteManager);
	//void AttachLight(LightSource *p_pxLight);
	//void AttachTerrain(TerrainObject *p_pxTerrain);
	//void AttachEnemy(EnemyFishObject *p_pxEnemy);
	//void AttachPowerup(PowerupObject *p_pxPowerup);
	//void AttachInfo(InfoObject *p_pxInfoObject);
	//void AttachTrap(TrapObject *p_pxTrapObject);
	//void AttachParticle(ParticleObject * p_pxParticle);

	//Create new objects during gameplay
	//void CreateNewEnemy(EnemyFishObject *p_pxEnemy);
	//void CreateNewPowerup(PowerupObject *p_pxPowerup);
	//void CreateParticles(int p_iAmount);


	//Add Animations to objects or maybe load/add them some other place?
	//void AddPlayerAnimation(PlayerFishObject *p_pxPlayer);
	//void AddEnemyAnimation(EnemyFishObject *p_pxEnemy);
	//void AddParticleAnimation(ParticleObject * p_pxParticle);


	////Destroy Functions for objects that can be destroyed in game
	//void DestroyPlayer();
	void DestroyEnemy(EnemyFishObject *p_pxEnemy, int p_Index);
	//void DestroyPowerup(PowerupObject *p_pxPowerup);
	//void DestroyInfoObject(InfoObject *p_pxInfoObject);
	//void DestroyParticle(ParticleObject * p_pxParticle);

	////Update functions
	void UpdateAllObjects(float p_fDeltatime);

	/*void UpdatePlayer(float p_fDeltatime);*/
	//void UpdateTerrain(float p_fDeltatime);
	//void UpdateEnemies(float p_fDeltatime);
	//void UpdatePowerups(float p_fDeltatime);
	//void UpdateInfoObjects(float p_fDeltatime);
	//void UpdateTrapObjects(float p_fDeltatime);
	//void UpdateParticles(float p_fDeltatime); // Uppdaterar position, velocity // opacity?
private:
	InputManager *m_pxInputManager;

	std::vector<GameObject*> m_apxGameObject;
	PlayerFishObject *m_pxPlayer;
	//LightSource *m_pxLight;
	//PlayerFishObject *m_pxPlayer;
	
	/*std::vector<TerrainObject*> m_apxTerrain;
	std::vector<EnemyFishObject*>  m_apxEnemy;
	std::vector<PowerupObject*>  m_apxPowerup;
	std::vector<InfoObject*>  m_apxInfoObject;
	std::vector<TrapObject*>  m_apxTrapObject;*/
	//std::vector<ParticleObject*> m_apxParticles;
};