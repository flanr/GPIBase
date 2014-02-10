//PowerupObject.h

#pragma once

#include "GameObject.h"

//namespace sf{class Sprite;}
//class sf::Sprite;
class Collider;

enum eType
{
	ROD,
	LIGHT,
	SPEED,
	ENERGY,
	TYPECOUNT
};

class PowerupObject : public GameObject
{
public:
	PowerupObject(eType p_eUpgrade, sf::Vector2f p_xPosition, sf::Sprite* p_pxSprite = nullptr, Collider* p_pxCollider = nullptr);
	~PowerupObject();

	eType GetType();
	void SetIdleMovement(float p_fMovement);
	/*void SetGlowEffect();*/

	void Update(float p_fDeltatime);

protected:
	float m_fMovement;
	eType m_eUpgrade;
	sf::Vector2f m_xStartPos;
	bool bMovingUp;

};