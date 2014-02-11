// PlayerFishObject.h
#pragma once

#include "FishObject.h"
#include "GameObject.h"

class AnimatedSprite;
class Collider;

enum eState
{
	Idle,
	Moving,
	Dash,
	Chewing,
	StateCount
};

enum eDirection
{
	/*FacingUp,
	FacingDown,*/
	FacingLeft,
	FacingRight,
	DirectionCount
};

class PlayerFishObject : public GameObject {
public:
		PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite, Collider* p_Collider = nullptr);

		void Update(InputManager *p_pxInputManager, float p_Deltatime);
		void SetActiveAnimation();
		void AddAnimation(const std::string &p_sName, AnimatedSprite *p_pxAnimSprite);

		void SetPlayerState(eState p_State);
		int GetPlayerState();

		void SetPlayerDirection(eDirection p_Direction);
		int GetPlayerDirection();

		void SetPlayerSpeed(float p_fPlayerSpeed);
		float GetPlayerSpeed();

		void InitPlayerView(sf::Vector2f p_Size);
		sf::View GetPlayerView();

		void SetPlayerViewport(sf::FloatRect p_NewViewPort);
		sf::FloatRect GetPlayerViewport();

private:

	bool m_Direction[DirectionCount];
	bool m_CurrentState[StateCount];
	float m_fPlayerSpeed;
	float m_fDash;

	sf::Vector2f m_fVelocity;
	sf::View m_PlayerView;
	AnimatedSprite *m_pxCurrentAnimation;
	std::map<std::string, AnimatedSprite*> m_mpAnimations;


};
