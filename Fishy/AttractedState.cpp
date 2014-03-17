//AttractedState.cpp
#include "stdafx.h"
#include "AttractedState.h"

AttractedState* AttractedState::Instance()
{
	static AttractedState Instance;

	return &Instance;
}

void AttractedState::Execute(EnemyFishObject* p_pEnemy)
{
	p_pEnemy->Attracted();
}