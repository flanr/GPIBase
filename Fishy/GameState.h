// GameState.h
#pragma once
#include "State.h"
#include "stdafx.h"
#include "Core.h"
using namespace std;

class GameState : public State
{
public:
	GameState(Core* p_core);

	bool EnterState();
	bool Update(float p_fDeltatime);
	/**
	Returns True if p_type == GameState
	**/
	bool IsType(const string &p_sType);

	void ExitState();	
	void Draw();
	void HandleInput();


	string Next();
	string GetCurrentState();
	
private:
	
};
