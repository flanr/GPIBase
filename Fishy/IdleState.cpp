//IdleState.cpp
#include "stdafx.h"

#include "IdleState.h"
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
}
void IdleState::Exitstate(EnemyFishObject* p_pEnemy)
{
}
