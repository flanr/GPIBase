// PlayerFishObject.h
#pragma once

#include "FishObject.h"

class AnimatedSprite;
class Collider;


class PlayerFishObject : public FishObject {
public:
		PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite, Collider* p_Collider = nullptr);
		~PlayerFishObject();

		void Update(InputManager *p_pxInputManager, float p_Deltatime);
		void AddAnimation(const std::string &p_sName, AnimatedSprite *p_pxAnimSprite);

	/*	void SetActiveAnimation(const std::string &p_sName);
		AnimatedSprite* GetAnimation(const std::string &p_sName);*/

		void InitPlayerView(sf::Vector2f p_Size);
		sf::View GetPlayerView();

		void SetPlayerViewport(sf::FloatRect p_NewViewPort);
		sf::FloatRect GetPlayerViewport();

private:

	bool m_SlowingDown;
	int m_iDashtimer;

	sf::Vector2f m_fVelocity;
	sf::View m_PlayerView;
	AnimatedSprite *m_pxCurrentAnimation;
	std::map<std::string, AnimatedSprite*> m_mpAnimations;


};
