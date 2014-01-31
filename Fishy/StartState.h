// StartState.h
#pragma once


#include "State.h"
#include "stdafx.h"
using namespace std;

class StartState : public State
{
public:
	StartState(Core *core);
	/* Called upon StartState Entry */
	bool EnterState();
	/* Updating StartState */
	bool Update(float p_fDeltaTime);
	/*	Returns True if p_type == StartState */
	bool IsType(const string &p_sType);
	/* Exits StartState */
	void ExitState();	
	/* Draws StartState */
	void Draw();
	/* Handle Input in StartState */
	void HandleInput();

	/* Returns default Next State */
	string Next();
	/*Returns Current State */
	string GetCurrentState();
	
private:

};