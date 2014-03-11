//AIGlobalState.h

#pragma once
#include "AIState.h"
#include "EnemyFishObject.h"

class AIGlobalState : public AIState<EnemyFishObject>
{
private:
	AIGlobalState() {}

	AIGlobalState(AIGlobalState&);
	AIGlobalState& operator=(const AIGlobalState&);

public:
	static AIGlobalState* Instance();

	virtual void Enterstate(EnemyFishObject* p_pEnemy){}
	virtual void Execute(EnemyFishObject* p_pEnemy);
	virtual void Exitstate(EnemyFishObject* p_pEnemy){}

};