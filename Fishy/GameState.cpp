// GameState.cpp

#include "stdafx.h"
#include "GameState.h"
#include "Core.h"
using namespace std;
GameState::GameState(Core* p_core)
{

}

string GameState::GetCurrentState()
{
	return m_sCurrentState;
}

string GameState::Next()
{
	return "OptionState";
}


bool GameState::EnterState()
{
	m_sCurrentState = "GameState";
	cout << "Gamestate::EnterState" << endl;

	return false;
}

void GameState::ExitState()
{
	cout << "GameState::ExitState" << endl;
}

bool GameState::Update(float p_DeltaTime)
{
	return true;
}

void GameState::HandleInput()
{

}

void GameState::Draw()
{

}

bool GameState::IsType(const string &p_type)
{
	return p_type.compare("GameState") == 0;
}


