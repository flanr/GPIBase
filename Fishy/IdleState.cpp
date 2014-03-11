//IdleState.cpp
#include "stdafx.h"

#include "IdleState.h"
#include "ScaredState.h"
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
	if (p_pEnemy->GetSafe())
	{
		p_pEnemy->SetSafe(false);
	}
	int iRandomX;
	int iRandomY;
	if(p_pEnemy->GetTimer() > 400)	{p_pEnemy->ResetTimer();}

	if(p_pEnemy->GetTimer() == 50)
	{
		iRandomX = p_pEnemy->random(1, 2);
		std::cout << iRandomX << std::endl;
		if(iRandomX == 1)
		{
			p_pEnemy->SetVelocity(sf::Vector2f(p_pEnemy->GetSpeed() * -1, 0.0f) );
			p_pEnemy->FlipXLeft(p_pEnemy->GetScale());
		}
		else if (iRandomX == 2)
		{
			p_pEnemy->SetVelocity(sf::Vector2f(p_pEnemy->GetSpeed(), 0.0f));
			p_pEnemy->FlipXRight(p_pEnemy->GetScale());
		}
	}
	if(p_pEnemy->GetTimer() == 250)
	{
		iRandomY = p_pEnemy->random(1, 2);
		if (iRandomY == 1)
		{
			p_pEnemy->SetVelocity(sf::Vector2f(0.0f, p_pEnemy->GetSpeed()));
		}
		else if (iRandomY == 2)
		{
			p_pEnemy->SetVelocity(sf::Vector2f(0.0f, p_pEnemy->GetSpeed()* -1));
			
		}
	}
	sf::Vector2f DistanceVector = p_pEnemy->GetPlayerPosition() - p_pEnemy->GetPosition();
	float DistanceNumber = DistanceVector.x * DistanceVector.x + DistanceVector.y * DistanceVector.y;
	if (sqrtf(DistanceNumber) <= 300.f)
	{
		if (p_pEnemy->GetPlayerDirection() == 3 && p_pEnemy->GetPlayerPosition().x < p_pEnemy->GetPosition().x)
		{
			p_pEnemy->GetFSM()->ChangeState(ScaredState::Instance());
		}
		if (p_pEnemy->GetPlayerDirection() == 2 && p_pEnemy->GetPlayerPosition().x > p_pEnemy->GetPosition().x)
		{
			p_pEnemy->GetFSM()->ChangeState(ScaredState::Instance());
		}
	}
}
void IdleState::Exitstate(EnemyFishObject* p_pEnemy)
{
}
