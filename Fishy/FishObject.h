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
	FacingUp,
	FacingDown,
	FacingLeft,
	FacingRight,
	DirectionCount
};

class FishObject : public GameObject
{
public:
	FishObject(sf::Vector2f p_Position, sf::Sprite *p_Sprite, Collider* p_Collider = nullptr);

	/*Set State the fish is in. Idle, Moving etc*/
	void SetState(eState p_State);
	int GetState();

	/*Set Direction Fish is facing*/
	void SetDirectionTrue(eDirection p_Direction);
	void SetDirectionFalse(eDirection p_Direction);
	eDirection GetHorizontalDirection();
	eDirection GetVerticalDirection();

	/*Set Movement of the fish*/
	void SetVelocity(sf::Vector2f p_Velocity);
	sf::Vector2f GetVelocity();

	/*Set Speed of the fish*/
	void SetSpeed(float p_fSpeed);
	float GetSpeed();

	/*Set Dash / Attack Power */
	void SetDashPower(float p_fDashpower);
	float GetDashPower();

private:

	bool m_Direction[DirectionCount];
	bool m_CurrentState[StateCount];

	float m_fSpeed;
	float m_fDashpower;

	sf::Vector2f m_Velocity;
};