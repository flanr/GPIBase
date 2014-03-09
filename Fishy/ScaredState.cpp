//ScaredState.cpp
#include "stdafx.h"
#include "ScaredState.h"

ScaredState* ScaredState::Instance()
{
	static ScaredState Instance;

	return &Instance;
}

void ScaredState::Enterstate(EnemyFishObject* p_pEnemy)
{

}
void ScaredState::Execute(EnemyFishObject* p_pEnemy)
{
	p_pEnemy->Scared();

	if (p_pEnemy->GetSafe())
	{
		p_pEnemy->GetFSM()->ChangeState(IdleState::Instance());
	}

}
void ScaredState::Exitstate(EnemyFishObject* p_pEnemy)
{

}