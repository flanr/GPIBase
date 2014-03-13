#include "stdafx.h"
#include "EndState.h"


EndState::EndState(Core* p_pCore)
{

	m_pCore = p_pCore;
	m_window = p_pCore->window;
	m_pInputManager = p_pCore->m_pInputManager;
	m_DrawManager = p_pCore->m_DrawManager;
	m_SpriteManager = p_pCore->m_SpriteManager;
	m_SoundManager = p_pCore->m_SoundManager;

	

	m_BackGroundImg = m_SpriteManager->Load("background2.jpg",0,0,1280,720);
	m_BackGroundImg->setPosition(0,0);




}


EndState::~EndState(void)
{
}




bool EndState::EnterState()
{
	m_window->setView(m_window->getDefaultView());
	m_sCurrentState = "EndState";
	cout << "EndState::EnterState" << endl;
	return false;
}

bool EndState::Update(float p_deltatime)
{
	HandleInput();
	return true;
}

bool EndState::IsType(const string &p_sType)
{

	return p_sType.compare("EndState") == 0;
}
void EndState::ExitState()
{
	cout << "GameState::ExitState" << endl;
}	
void EndState::Draw()
{
	m_DrawManager->ClearWindow();
	m_DrawManager->DisplayWindow();
}
void EndState::HandleInput()
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
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num4))
	{
		cout << " You are already in EndState" << endl;
	}
}

string EndState::Next()
{
	return "GameState";
}
string EndState::GetCurrentState()
{	
	return m_sCurrentState;
}