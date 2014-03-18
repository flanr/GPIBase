//IdleState.cpp
#include "stdafx.h"

#include "IdleState.h"
#include "AttractedState.h"
#include "ScaredState.h"
#include "HuntingState.h"
#include <random>
IdleState* IdleState::Instance()
{
	static IdleState Instance;

	return &Instance;
}

void IdleState::Enterstate(EnemyFishObject* p_pEnemy)
{
}
void IdleState::Execute(EnemyFishObject* p_pEnemy)
{
	p_pEnemy->Idle();

	sf::Vector2f DistanceVector = p_pEnemy->GetPlayerPosition() - p_pEnemy->GetPosition();
	float DistanceNumber = DistanceVector.x * DistanceVector.x + DistanceVector.y * DistanceVector.y;
	if (sqrtf(DistanceNumber) <= 600.f)
	{
		p_pEnemy->GetFSM()->ChangeState(AttractedState::Instance());
	}
	/*else if (p_pEnemy->GetSubType() != "Stage2" && sqrtf(DistanceNumber) <= 300.f)
	{
		p_pEnemy->GetFSM()->ChangeState(ScaredState::Instance());
	}*/
	else if (sqrtf(DistanceNumber) <= 400.f)
	{
		if (p_pEnemy->GetSubType() == "Stage2")
		{
			p_pEnemy->GetFSM()->ChangeState(HuntingState::Instance());
		}
	}
}
void IdleState::Exitstate(EnemyFishObject* p_pEnemy)
{
}
