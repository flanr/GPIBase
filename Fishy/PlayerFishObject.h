// PlayerFishObject.h
#pragma once

#include "FishObject.h"
class AnimatedSprite;
class Collider;
class Camera;

class PlayerFishObject : public FishObject {
public:
	PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite, Collider* p_Collider = nullptr);
	~PlayerFishObject();

	void SetPlayerScale(float x);
	void Update(InputManager *p_pxInputManager,Camera *p_Camera ,float p_Deltatime);
	void AddAnimation(const std::string &p_sName, AnimatedSprite *p_pxAnimSprite);

	void SetHealth(int p_Health);
	int GetHealth();

	void SetEnergy(int p_Energy);
	int GetEnergy();
	void ExperienceGain(int x);
	int GetExperience();
	
	void OnCollision(GameObject* other, sf::Vector2f& offset);
private:

	void UpdateInput(InputManager *p_pxInputManager, float p_Deltatime);
	void UpdateIdle(float p_Deltatime);
	void UpdateMovement(float p_Deltatime);
	void UpdateAttack(float p_Deltatime);
	void UpdateSneak(float p_Deltatime);
	void UpdateChewing(float p_Deltatime);
	void UpdateHealth();
private:
	sf::Vector2f m_fVelocity;
	int m_Health;
	int m_Energy;
	int m_Experience;

	bool m_SlowingDown;
	int m_Healthtimer;
	int m_iAttacktimer;

	AnimatedSprite *m_pxCurrentAnimation;
	std::map<std::string, AnimatedSprite*> m_mpAnimations;

};
