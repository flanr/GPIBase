// FishObject.h
#pragma once

#include "GameObject.h"
class Collider;

enum eState
{
	Idle,
	Moving,
	Attack,
	Sneak,
	Chewing,
	Death,
	StateCount
};

enum eDirection
{
	FacingUp,
	FacingDown,
	FacingLeft,
	FacingRight,
	FacingUpRight,
	FacingUpLeft,
	FacingDownRight,
	FacingDownLeft,
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
	void SetDirection(eDirection p_Direction);
	eDirection GetDirection();

	/*Set Movement of the fish*/
	void SetVelocityX(float p_VelocityX);
	void SetVelocityY(float p_VelocityY);
	void SetVelocity(sf::Vector2f p_Velocity);
	sf::Vector2f GetVelocity();

	/*Set Speed of the fish*/
	void SetSpeed(float p_fSpeed);
	float GetSpeed();

	/*Set Dash / Attack Power */
	void SetAttackPower(float p_fAttackpower);
	float GetAttackPower();

private:

	bool m_Direction[DirectionCount];
	bool m_CurrentState[StateCount];

	float m_fSpeed;
	float m_fAttackpower;
	sf::Vector2f m_Velocity;

};