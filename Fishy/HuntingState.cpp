//HuntingState.cpp
#include "stdafx.h"
#include "AIState.h"
#include "HuntingState.h"
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
void HuntingState::Exitstate(EnemyFishObject* p_pEnemy){}