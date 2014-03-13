//HuntingState.h

#pragma once
#include "stdafx.h"
//#include "AIState.h"

class HuntingState : public AIState<EnemyFishObject>
{
private:
	HuntingState(){}

public:
	static HuntingState* Instance();

	void Enterstate(EnemyFishObject* p_pEnemy);
	void Execute(EnemyFishObject* p_pEnemy);
	void Exitstate(EnemyFishObject* p_pEnemy);
};