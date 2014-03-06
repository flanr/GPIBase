//IdleState.cpp
#include "stdafx.h"

#include "IdleState.h"

void IdleState::Enterstate(EnemyFishObject* p_pEnemy)
{
}
void IdleState::Execute(EnemyFishObject* p_pEnemy)
{
	p_pEnemy->Move(5.f, 0.f);
}
void IdleState::Exitstate(EnemyFishObject* p_pEnemy)
{
}
IdleState* IdleState::Instance()
{
	IdleState Instance;

	return &Instance;
}