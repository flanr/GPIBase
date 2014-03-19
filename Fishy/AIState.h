//AIState.h

#pragma once
template <class entity_type>
class AIState
{
public:
	string type;
	virtual void Enterstate(entity_type*) = 0;
	virtual void Execute(entity_type*) = 0;
	virtual void Exitstate(entity_type*) = 0;
	virtual ~AIState(){}
};

//virtual void OnCollision() = 0