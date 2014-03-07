//AIGlobalState
#include "stdafx.h"
#include "AIGlobalState.h"

AIGlobalState* AIGlobalState::Instance()
{
	AIGlobalState Instance;

	return &Instance;

}

void AIGlobalState::Execute(EnemyFishObject* p_pEnemy)
{
	//Something the enemies always can revert back to
}