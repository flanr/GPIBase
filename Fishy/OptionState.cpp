// OptionState.cpp
#include "stdafx.h"
#include "OptionState.h"


using namespace std;
OptionState::OptionState(Core* p_pCore)
{
	m_pCore = p_pCore;
	m_window = p_pCore->window;
	m_pInputManager = p_pCore->m_pInputManager;
	m_DrawManager = p_pCore->m_DrawManager;
	m_SpriteManager = p_pCore->m_SpriteManager;
	////////////////
	// Background //
	////////////////
	m_BackGroundImg = m_SpriteManager->Load("background2.jpg",0,0,1280,720);
	m_BackGroundImg->setPosition(0,0);

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
	return true;
}

void OptionState::HandleInput()
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
		cout << " You are already in OptionState" << endl;
		//m_pCore->m_StateManager.SetState("OptionState");
	}


}

void OptionState::Draw()
{
	m_DrawManager->ClearWindow();
	
	m_DrawManager->Draw(m_BackGroundImg);
	
	//m_level->Draw(m_DrawManager);
	m_DrawManager->DisplayWindow();
}

bool OptionState::IsType(const string &p_sType)
{
	return p_sType.compare("OptionState") == 0;
}


