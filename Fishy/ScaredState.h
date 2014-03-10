//ScaredState
#pragma once
#include "EnemyFishObject.h"

class ScaredState : public AIState<EnemyFishObject>
{
private:
	ScaredState(){}
	
public:
	static ScaredState* Instance();

	void Enterstate(EnemyFishObject* p_pEnemy);
	void Execute(EnemyFishObject* p_pEnemy);
	void Exitstate(EnemyFishObject* p_pEnemy);


};