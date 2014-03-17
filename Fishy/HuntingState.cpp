//HuntingState.cpp
#include "stdafx.h"
#include "AIState.h"
#include "HuntingState.h"
#include "ScaredState.h"
#include "EnemyFishObject.h"

HuntingState* HuntingState::Instance()
{
	
	static HuntingState Instance;

	return &Instance;
}

void HuntingState::Enterstate(EnemyFishObject* p_pEnemy){}
void HuntingState::Execute(EnemyFishObject* p_pEnemy)
{
	p_pEnemy->Hunting();
}
void HuntingState::Exitstate(EnemyFishObject* p_pEnemy)
{
	//Only to use for getting rid of the enemy fish after it has inflicted damage
	p_pEnemy->GetFSM()->ChangeState(ScaredState::Instance());
}