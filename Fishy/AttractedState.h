//AttractedState.h

#pragma once
#include "AIState.h"
#include "EnemyFishObject.h"

class AttractedState : public AIState<EnemyFishObject>
{
private:
	AttractedState(){};

public:

static AttractedState* Instance();

void Enterstate(EnemyFishObject* p_pEnemy){};
void Execute(EnemyFishObject* p_pEnemy);
void Exitstate(EnemyFishObject* p_pEnemy){};

};