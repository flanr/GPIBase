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
	void SetSoundManager(SoundManager* p_soundmanager);
	void OnCollision(GameObject* other, sf::Vector2f& offset);
	
private:
	
	void UpdateInput(InputManager *p_pxInputManager, float p_Deltatime);
	void UpdateIdle(float p_Deltatime);
	void UpdateAttack(float p_Deltatime);
	void UpdateChewing(float p_Deltatime);
	void UpdateGrowing(SpriteManager *p_SpriteManager, Camera *p_Camera ,float p_Deltatime);
	void UpdateHealth();
	void UpdateCollider();
	void UpdateLightPosition();
private:
	sf::Vector2f m_fVelocity;
	sf::Vector2f m_LightbulbPosRelativeToPlayer;

	int m_Health;
	int m_Energy;
	int m_Experience;

	int m_PowerupLightCounter;
	int m_PowerupSpeedCounter;
	int m_PowerupEnergyCounter;
	bool m_SlowingDown;
	int m_Healthtimer;
	int m_iAttacktimer;
	int m_ChewTimer;
	int m_GrowTimer;
	bool m_HasGrown;
	bool m_HasFishingRod;
	SoundManager* m_SoundManager;
	AnimatedSprite *m_pxCurrentAnimation;
	std::map<std::string, AnimatedSprite*> m_mpAnimations;

	int m_iWidth, m_iHeight;
};
