// GameObjectManager.h
#pragma once

class SpriteManager;
class InputManager;

class TerrainObject;
class PlayerFishObject;
class LightObject;
class EnemyFishObject;
class PowerupObject;
class InfoObject;
class TrapObject;
//class ParticleObject;

class GameObjectManager
{

public:
	GameObjectManager(SpriteManager *p_pxSpriteManager);
	~GameObjectManager();
	
	void Cleanup();
	
	//attach objects
	void AttachPlayer(PlayerFishObject *p_pxPlayer);
	void AttachLight(LightObject *p_pxLight);
	void AttachTerrain(TerrainObject *p_pxTerrain);
	void AttachEnemy(EnemyFishObject *p_pxEnemy);
	void AttachPowerup(PowerupObject *p_pxPowerup);
	void AttachInfo(InfoObject *p_pxInfoObject);
	void AttachTrap(TrapObject *p_pxTrapObject);
	//void AttachParticle(ParticleObject * p_pxParticle);

	//Create new objects during gameplay
	void CreateNewEnemy(EnemyFishObject *p_pxEnemy);
	void CreateNewPowerup(PowerupObject *p_pxPowerup);
	//void CreateParticles(int p_iAmount);


	//Add Animations to objects or maybe load/add them some other place?
	void AddPlayerAnimation(PlayerFishObject *p_pxPlayer);
	void AddEnemyAnimation(EnemyFishObject *p_pxEnemy);
	//void AddParticleAnimation(ParticleObject * p_pxParticle);


	////Destroy Functions for objects that can be destroyed in game
	void DestroyPlayer();
	void DestroyEnemy(EnemyFishObject *p_pxEnemy);
	void DestroyPowerup(PowerupObject *p_pxPowerup);
	void DestroyInfoObject(InfoObject *p_pxInfoObject);
	//void DestroyParticle(ParticleObject * p_pxParticle);

	////Update functions
	void UpdateAllObjects(float p_fDeltatime);

	void UpdatePlayer(float p_fDeltatime);
	void UpdateTerrain(float p_fDeltatime);
	void UpdateEnemies(float p_fDeltatime);
	void UpdatePowerups(float p_fDeltatime);
	void UpdateInfoObjects(float p_fDeltatime);
	void UpdateTrapObjects(float p_fDeltatime);
	//void UpdateParticles(float p_fDeltatime); // Uppdaterar position, velocity // opacity?
private:
	SpriteManager *m_pxSpriteManager;

	PlayerFishObject *m_pxPlayer;
	LightObject *m_pxLight;
	std::vector<TerrainObject*> m_apxTerrain;
	std::vector<EnemyFishObject*>  m_apxEnemy;
	std::vector<PowerupObject*>  m_apxPowerup;
	std::vector<InfoObject*>  m_apxInfoObject;
	std::vector<TrapObject*>  m_apxTrapObject;
	//std::vector<ParticleObject*> m_apxParticles;
};