// StartState.cpp
#include "stdafx.h"

#include "StartState.h"


using namespace std;
StartState::StartState(Core* p_core)
{

}

string StartState::GetCurrentState()
{
	return m_sCurrentState;
}

string StartState::Next()
{
	return "OptionState";
}


bool StartState::EnterState()
{
	m_sCurrentState = "StartState";
	cout << "StartState::EnterState" << endl;

	return false;
}

void StartState::ExitState()
{
	cout << "StartState::ExitState" << endl;
}

bool StartState::Update(float p_fDeltaTime)
{
	return true;
}

void StartState::HandleInput()
{

}

void StartState::Draw()
{

}

bool StartState::IsType(const string &p_sType)
{
	return p_sType.compare("StartState") == 0;
}


