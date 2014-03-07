// GameObjectManager.h
#pragma once

class InputManager;

class GameObject;
class PlayerFishObject;
class PowerupObject;
class EnemyFishObject;

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
	//void AttachParticle(ParticleObject * p_pxParticle);

	//Create new objects during gameplay
	//void CreateNewEnemy(EnemyFishObject *p_pxEnemy);
	//void CreateNewPowerup(PowerupObject *p_pxPowerup);
	//void CreateParticles(int p_iAmount);


	//Add Animations to objects or maybe load/add them some other place?
	//void AddEnemyAnimation(EnemyFishObject *p_pxEnemy);
	//void AddParticleAnimation(ParticleObject * p_pxParticle);


	////Destroy Functions for objects that can be destroyed in game
	//void DestroyPlayer();
	void DestroyEnemy(EnemyFishObject *p_pxEnemy, int p_Index);
	//void DestroyPowerup(PowerupObject *p_pxPowerup);
	//void DestroyParticle(ParticleObject * p_pxParticle);

	////Update functions
	void UpdateAllObjects(float p_fDeltatime);

	/*void UpdatePlayer(float p_fDeltatime);*/
	//void UpdateParticles(float p_fDeltatime); // Uppdaterar position, velocity // opacity?
private:
	InputManager *m_pxInputManager;

	std::vector<GameObject*> m_apxGameObject;
	PlayerFishObject *m_pxPlayer;

	std::vector<PowerupObject*>  m_apxPowerup;

	//std::vector<ParticleObject*> m_apxParticles;
};