// EnemyFishObject
#pragma once

#include "GameObject.h"
#include "AIState.h"
#include "AIStateMachine.h"
#include "IdleState.h"

class Collider;
template class AIStateMachine<EnemyFishObject>;
class EnemyFishObject : public FishObject
{
public:
	//EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_xSprite);
	EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_xSprite, Collider* p_xCollider = nullptr);
	~EnemyFishObject();

	void Update(float deltatime, PlayerFishObject *player);

	void ChangeState();

	void SetSpawnPosition(sf::Vector2f p_xSpawnPosition);
	sf::Vector2f GetSpawnPosition(sf::Vector2f p_xSpawnPosition);
	void SetAttractRadius(float p_fAttractRadius);
	/* use for collision with EnemyFish vs Wall*/
	void OnCollision(GameObject* p_other, sf::Vector2f& p_Offset);

	
	/*----------------AI STUFF-------------------*/
	AIStateMachine<EnemyFishObject>* GetFSM()				{return m_pAIStateMachine;}
	void AddTimer(const int nr)								{m_iStateTimer+= nr;};
	int GetTimer()											{return m_iStateTimer;};
	void ResetTimer()										{m_iStateTimer = 0;};
	
	int random(int min, int max);
	
	//Scared
	void Scared();
	bool GetSafe()											{return isSafe;}
	void SetSafe(bool val)									{isSafe = val;}
	//Hunting
	void Hunting();
	sf::Vector2f GetPlayerPosition()						{return m_xPlayerPosition; }
	int GetPlayerDirection()								{return m_iPlayerDirection;}
private:
	sf::Vector2f m_xSpawnPosition, m_xPlayerPosition;
	int m_iStateTimer, m_iPlayerDirection;
	AIStateMachine<EnemyFishObject>* m_pAIStateMachine;
	bool isSafe;

};