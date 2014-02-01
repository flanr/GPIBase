// StartState.cpp
#include "stdafx.h"

#include "StartState.h"


using namespace std;
StartState::StartState(Core* p_pCore)
{
	m_pCore = p_pCore;
	m_pInputManager = p_pCore->m_pInputManager;
	m_pWindow = p_pCore->window;
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
	Draw();
	return true;
}

void StartState::HandleInput()
{
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num1))
	{
		cout << "Already in StartState" << endl;
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
	sf::CircleShape shape(40.0f);
	m_pWindow->clear(sf::Color(0x44,0x55,0x22,0xff));
	m_pWindow->draw(shape);
}

bool StartState::IsType(const string &p_sType)
{
	return p_sType.compare("StartState") == 0;
}


