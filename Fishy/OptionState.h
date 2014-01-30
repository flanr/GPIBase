// OptionState.h
#pragma once

#include "State.h"
#include "stdafx.h"
#include "Core.h"
using namespace std;

class OptionState : public State
{
public:
	OptionState(Core * core);

	bool EnterState();
	bool Update(float p_deltatime);
	/**
	Returns True if p_type == OptionState
	**/
	bool IsType(const string &p_type);

	void ExitState();	
	void Draw();
	void HandleInput();

	string Next();
	string GetCurrentState();
	
private:

};