// PlayerFishObject.h
#pragma once

#include "FishObject.h"
#include "GameObject.h"

class AnimatedSprite;
class Collider;

class PlayerFishObject : public GameObject {
public:
		PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite, Collider* p_Collider = nullptr);

		void Update(InputManager *p_pxInputManager, float p_Deltatime);
		void AddAnimation(const std::string &p_sName, AnimatedSprite *p_pxAnimSprite);

		void SetPlayerSpeed(float p_fPlayerSpeed);
		float GetPlayerSpeed();

		void InitPlayerView(sf::Vector2f p_Size);
		sf::View GetPlayerView();

		void SetPlayerViewport(sf::FloatRect p_NewViewPort);
		sf::FloatRect GetPlayerViewport();

private:

	float m_fPlayerSpeed;
	sf::Vector2f m_fVelocity;
	sf::View m_PlayerView;
	AnimatedSprite *m_pxCurrentAnimation;
	std::map<std::string, AnimatedSprite*> m_mpAnimations;


};
