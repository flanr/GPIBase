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
	/**
	**/
	string CurrentState();
	/**
	**/
	void Attach(State *p_State);
	/**
	**/
	void Update(float p_deltatime);
	/**
	**/
	void Draw();
	/**
	**/
	void SetState(const string &p_type);
	/**
	**/
	void ChangeState();
	/**
	**/
	bool IsRunning();
	
private:
	/**
	**/
	vector<State*> m_aStates;
	/**
	**/
	State *m_pCurrentState;

};