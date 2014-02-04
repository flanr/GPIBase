// OptionState.cpp
#include "stdafx.h"
#include "OptionState.h"

using namespace std;
OptionState::OptionState(Core* p_pCore)
{
	m_pCore = p_pCore;
	m_pInputManager = p_pCore->m_pInputManager;
	m_pWindow = p_pCore->window;
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
	HandleInput();
	Draw();
	return true;
}

void OptionState::HandleInput()
{
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num1))
	{
		
		m_pCore->m_StateManager.SetState("StartState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num2))
	{
		m_pCore->m_StateManager.SetState("GameState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num3))
	{
		cout << "Already in OptionState" << endl;
	}
	
}

void OptionState::Draw()
{
	sf::CircleShape shape(45.0f);
	m_pWindow->clear(sf::Color(0x55,0x66,0x77,0xff));
	m_pWindow->draw(shape);
}

bool OptionState::IsType(const string &p_sType)
{
	return p_sType.compare("OptionState") == 0;
}


