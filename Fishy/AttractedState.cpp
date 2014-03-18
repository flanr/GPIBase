//AttractedState.cpp
#include "stdafx.h"
#include "AttractedState.h"
#include "LightSource.h"
#include "ScaredState.h"
#include "HuntingState.h"

AttractedState* AttractedState::Instance()
{
	static AttractedState Instance;

	return &Instance;
}

void AttractedState::Execute(EnemyFishObject* p_pEnemy)
{
	sf::Vector2f distance = p_pEnemy->GetPlayerLightSource()->GetPosition() - p_pEnemy->GetPosition();
	float fdistance = distance.x * distance.x + distance.y * distance.y;
	if (p_pEnemy->GetPlayerLightSource()->GetLightStatus() != true)
	{
		if (p_pEnemy->GetSubType() != "Stage2")
		{
			p_pEnemy->GetFSM()->ChangeState(ScaredState::Instance() );
		}
		else if (p_pEnemy->GetSubType() == "Stage2" && sqrtf(fdistance) <= 400)
		{
			p_pEnemy->GetFSM()->ChangeState(HuntingState::Instance() );
		}
		else if (p_pEnemy->GetSubType() == "Stage2" && sqrtf(fdistance) >= 400)
		{
			p_pEnemy->GetFSM()->ChangeState(IdleState::Instance() );
		}
	}
	p_pEnemy->Attracted();
}