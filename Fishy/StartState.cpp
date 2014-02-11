// StartState.cpp
#include "stdafx.h"

#include "StartState.h"


using namespace std;
StartState::StartState(Core* p_pCore)
{
	m_pCore = p_pCore;
	m_window = p_pCore->window;
	m_pInputManager = p_pCore->m_pInputManager;
	m_DrawManager = p_pCore->m_DrawManager;
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

	HandleInput();
	return true;
}

void StartState::HandleInput()
{
	if(m_pInputManager->IsDownOnceK(sf::Keyboard::Num1))
	{
		m_pCore->m_StateManager.SetState("StartState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num2))
	{
		m_pCore->m_StateManager.SetState("GameState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num3))
	{
		m_pCore->m_StateManager.SetState("OptionState");
	}


}

void StartState::Draw()
{
	sf::CircleShape shape(15.0f);
	//m_pWindow->clear(sf::Color(0x44,0x55,0x22,0xff));

	m_DrawManager->ClearWindow();
	//m_level->Draw(m_DrawManager);
	m_DrawManager->DisplayWindow();
}

bool StartState::IsType(const string &p_sType)
{
	return p_sType.compare("StartState") == 0;
}


