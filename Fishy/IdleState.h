//IdleState
#include "AISTate.h"
#include "EnemyFishObject.h"

class IdleState : public AIState<EnemyFishObject>
{
public:
	void Enterstate(EnemyFishObject* p_pEnemy);
	void Execute(EnemyFishObject* p_pEnemy);
	void ExitState(EnemyFishObject* p_pEnemy);

};