// OptionState.cpp
#include "stdafx.h"
#include "OptionState.h"

using namespace std;
OptionState::OptionState(Core* p_core)
{

}

string OptionState::GetCurrentState()
{
	return m_sCurrentState;
}

string OptionState::Next()
{
	return "GameState";
}


bool OptionState::EnterState()
{
	m_sCurrentState = "OptionState";
	cout << "OptionState::EnterState" << endl;

	return false;
}

void OptionState::ExitState()
{
	cout << "StartState::ExitState" << endl;
}

bool OptionState::Update(float p_fDeltaTime)
{
	return true;
}

void OptionState::HandleInput()
{

}

void OptionState::Draw()
{

}

bool OptionState::IsType(const string &p_sType)
{
	return p_sType.compare("OptionState") == 0;
}


