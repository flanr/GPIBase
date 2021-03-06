//IdleState
//#include "AISTate.h"
#pragma once
#include "stdafx.h"
#include "EnemyFishObject.h"

class IdleState : public AIState<EnemyFishObject>
{
private:
	IdleState(){}
	
public:
	static IdleState* Instance();

	void Enterstate(EnemyFishObject* p_pEnemy);
	void Execute(EnemyFishObject* p_pEnemy);
	void Exitstate(EnemyFishObject* p_pEnemy);


};