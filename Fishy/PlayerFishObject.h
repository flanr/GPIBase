// PlayerFishObject.h
#pragma once

#include "FishObject.h"
#include "GameObject.h"

class AnimatedSprite;
class Collider;

class PlayerFishObject : public GameObject {
public:
		PlayerFishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite, Collider* p_Collider = nullptr);

		virtual void Update(float deltatime);

		void AddAnimation(const std::string &p_sName, AnimatedSprite *p_pxAnimSprite);

private:

	AnimatedSprite *m_pxCurrentAnimation;
	std::map<std::string, AnimatedSprite*> m_mpAnimations;


};
