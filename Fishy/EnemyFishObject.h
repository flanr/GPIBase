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
	
private:
	sf::Vector2f m_xSpawnPosition;
	int m_iStateTimer;
	AIStateMachine<EnemyFishObject>* m_pAIStateMachine;

};