// StateManager.h
#pragma once
#include "stdafx.h"
using namespace std;
class State;


class StateManager
{
public:
	
	StateManager();
	~StateManager();
	/* Returns Current State as String */
	string CurrentState();
	/* Attaches new State to StateManager */
	void Attach(State *p_pState);
	/* Calls CurrentStates Update */
	void Update(float p_fDeltatime);
	/* Calls CurrentStates Draw */
	void Draw();
	/* Changes CurrentState into string parameter*/
	void SetState(const string &p_sType);
	/* Changed State into States Default Next() */
	void ChangeState();
	/* Returns True while running */
	bool IsRunning();

	State* GetCurrentState();
	
private:
	/* Vector of States*/
	vector<State*> m_aStates;
	/* Current State Pointer*/
	State *m_pCurrentState;

};