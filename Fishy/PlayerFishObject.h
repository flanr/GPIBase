// PlayerFishObject.h
#pragma once

#include "FishObject.h"
class AnimatedSprite;
class Collider;
class Camera;
class SpriteManager;
class SoundManager;

class PlayerFishObject : public FishObject {
public:
	PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite, Collider* p_Collider = nullptr);
	~PlayerFishObject();

	void SetPlayerScale(float x);
	void Update(InputManager *p_pxInputManager,SpriteManager *p_SpriteManager ,Camera *p_Camera ,float p_Deltatime);
	void MenuUpdate(float p_Deltatime);
	void AddAnimation(const std::string &p_sName, AnimatedSprite *p_pxAnimSprite);
	void ChangeStageAnimation(const std::string &p_sName, SpriteManager *p_pxSpriteManager);

	void SetHealth(int p_Health);
	int GetHealth();

	void SetEnergy(int p_Energy);
	int GetEnergy();
	void ExperienceGain(int x);
	void SetExperience(int p_experience);
	int GetExperience();
	bool UpdateLevel();
	bool HasGrown();
	AnimatedSprite* GetCurrentAnimation();

	void SetGameStatus(bool p_Status);
	bool GetGameStatus();

	void SetSoundManager(SoundManager* p_soundmanager);
	void OnCollision(GameObject* other, sf::Vector2f& offset);

	void DamageCooldown();
	bool GetStageTwo();

	int GetPowerupLightCount();
	int GetPowerupSpeedCount();
	int GetPowerupEnergyCount();
private:

	void UpdateInput(InputManager *p_pxInputManager, float p_Deltatime);
	void UpdateIdle(float p_Deltatime);
	void UpdateAttack(float p_Deltatime);
	void UpdateChewing(float p_Deltatime);
	void UpdateDeath(float p_Deltatime, Camera *p_Camera);
	void UpdateGrowing(SpriteManager *p_SpriteManager, Camera *p_Camera ,float p_Deltatime);
	void UpdateHealth(float p_Deltatime);
	void UpdateEnergy(float p_Deltatime);
	void UpdateCollider();
	void UpdateLightPosition();
	void UpdateSoundFeedback();
	
private:
	sf::Vector2f m_fVelocity;
	sf::Vector2f m_LightbulbPosRelativeToPlayer;

	int m_Health;
	float m_Energy;
	int m_Experience;
	bool m_GameOver;

	bool m_StageTwo;
	int m_PowerupLightCounter;
	int m_PowerupSpeedCounter;
	int m_PowerupEnergyCounter;
	bool m_SlowingDown;
	float m_Healthtimer;
	float m_iAttacktimer;
	float m_ChewTimer;
	float m_GrowTimer;
	float m_DeathTimer;

	bool m_HasGrown;
	bool m_HasFishingRod;
	SoundManager* m_SoundManager;
	AnimatedSprite *m_pxCurrentAnimation;
	std::map<std::string, AnimatedSprite*> m_mpAnimations;

	int m_iWidth, m_iHeight;

	bool m_bHasPlayedDeathMusic;
	bool m_bCanTakeDamage;
	sf::Clock m_Clock;
	sf::Time m_Time;
};
