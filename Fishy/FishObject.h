// FishObject.h
#pragma once

#include "GameObject.h"
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

class FishObject : public GameObject
{
public:
	FishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite, Collider* p_Collider = nullptr);

	void SetState(eState p_State);
	int GetState();

	void SetDirection(eDirection p_Direction);
	int GetDirection();

	void SetSpeed(float p_fSpeed);
	float GetSpeed();

	void SetDashPower(float p_fDashpower);
	float GetDashPower();

private:

	bool m_Direction[DirectionCount];
	bool m_CurrentState[StateCount];

	float m_fSpeed;
	float m_fDashpower;
};