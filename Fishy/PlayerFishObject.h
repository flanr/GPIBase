// PlayerFishObject.h
#pragma once

#include "FishObject.h"

class AnimatedSprite;
class Collider;


class PlayerFishObject : public FishObject {
public:
	PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite, Collider* p_Collider = nullptr);
	~PlayerFishObject();

	void SetPlayerScale(float x);
	void Update(InputManager *p_pxInputManager, float p_Deltatime);
	void AddAnimation(const std::string &p_sName, AnimatedSprite *p_pxAnimSprite);

	/*	void SetActiveAnimation(const std::string &p_sName);
	AnimatedSprite* GetAnimation(const std::string &p_sName);*/

	void InitPlayerView(sf::Vector2f p_Size);
	sf::View GetPlayerView();

	void SetPlayerViewport(sf::FloatRect p_NewViewPort);
	sf::FloatRect GetPlayerViewport();

	void SetHealth(int p_Health);
	int GetHealth();

	void SetEnergy(int p_Energy);
	int GetEnergy();
	void ExperienceGain(int x);
	int GetExperience();
private:

	/*bool m_Direction[DirectionCount];
	bool m_CurrentState[StateCount];
	float m_fPlayerSpeed;
	float m_fDash;*/

	sf::Vector2f m_fVelocity;
private:

	void UpdateInput(InputManager *p_pxInputManager, float p_Deltatime);
	void UpdateIdle(float p_Deltatime);
	void UpdateMovement(float p_Deltatime);
	void UpdateAttack(float p_Deltatime);
	void UpdateSneak(float p_Deltatime);
	void UpdateChewing(float p_Deltatime);
	void UpdateHealth();
private:
	int m_Health;
	int m_Energy;
	int m_Experience;

	bool m_SlowingDown;
	int m_Healthtimer;
	int m_iAttacktimer;

	sf::View m_PlayerView;
	AnimatedSprite *m_pxCurrentAnimation;
	std::map<std::string, AnimatedSprite*> m_mpAnimations;


};
