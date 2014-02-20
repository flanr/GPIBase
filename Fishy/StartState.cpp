// StartState.cpp
#include "stdafx.h"
//#include "Slider.h"
#include "StartState.h"
#include "SpriteManager.h"
// Health
// w 259 h 41
// Energy
// w 150 h 25

using namespace std;
StartState::StartState(Core* p_pCore)
{
	// w 150 h 25

	m_pCore = p_pCore;
	m_window = p_pCore->window;
	m_pInputManager = p_pCore->m_pInputManager;
	m_DrawManager = p_pCore->m_DrawManager;
	m_SpriteManager = p_pCore->m_SpriteManager;


	m_ButtonQuit.SetSprite(m_SpriteManager->Load("Button_concept.jpg",0,0,653,627));
	m_ButtonQuit.SetPosition(300,300);




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
} // 96 29 60

void StartState::ExitState()
{
	cout << "StartState::ExitState" << endl;
}

bool StartState::Update(float p_fDeltaTime)
{


	HandleInput();
	return true;
}

void StartState::MouseDown(int x, int y)
{

}
int StartState::MouseOver(int x, int y)
{
	int xx = m_ButtonQuit.GetCircle().getGlobalBounds().left; 
	//cout << "left : " << m_ButtonQuit.GetCircle().getGlobalBounds().left << " ";
	int yy = m_ButtonQuit.GetCircle().getGlobalBounds().top;
	//cout << "top : " << m_ButtonQuit.GetCircle().getGlobalBounds().top<< " ";
	int wid = m_ButtonQuit.GetCircle().getGlobalBounds().width;
	//cout << "wid : " << m_ButtonQuit.GetCircle().getGlobalBounds().width<< " ";
	int hei = m_ButtonQuit.GetCircle().getGlobalBounds().height;
	//cout << "hei : " << m_ButtonQuit.GetCircle().getGlobalBounds().height << endl;
	//cout << "Left : " << m_ButtonQuit.GetCircle().getGlobalBounds().left << " Top : " << m_ButtonQuit.GetCircle().getGlobalBounds().top << endl;
	//(x > Start.GetX() && x <Start.GetX()+ Start.GetW()) && (y > Start.GetY() && y < Start.GetY()+ Start.GetH())
	/*if (( x > m_ButtonQuit.GetCircle().getGlobalBounds().left/2 && x < m_ButtonQuit.GetCircle().getGlobalBounds().left/2 + m_ButtonQuit.GetCircle().getGlobalBounds().width/2) &&( y > m_ButtonQuit.GetCircle().getGlobalBounds().top/2 && y <  m_ButtonQuit.GetCircle().getGlobalBounds().top/2 + m_ButtonQuit.GetCircle().getGlobalBounds().height/2 ))
	{
	cout << "Its alive" << endl;
	}*/
	cout << x << " " << xx << endl << xx + 100 << endl;
	if ((x > xx & x < xx + 100 ) && (y > yy && y < yy + 100) )
	{
		cout << "Its alive" << endl;
	}


	return 0;
}


void StartState::HandleInput()
{
	if(m_pInputManager->IsDownOnceK(sf::Keyboard::Num1))
	{
		cout << " You are already in StartState" << endl;
		//m_pCore->m_StateManager.SetState("StartState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num2))
	{
		m_pCore->m_StateManager.SetState("GameState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num3))
	{
		m_pCore->m_StateManager.SetState("OptionState");
	}
	
	MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);
	
	//cout << "x : " << sf::Mouse::getPosition().x << " y : " << sf::Mouse::getPosition().y << endl;
}

void StartState::Draw()
{
	m_DrawManager->ClearWindow();
	//m_pWindow->clear(_sf::Color(0x44,0x55,0x22,0xff));
	m_DrawManager->Draw(m_ButtonQuit.GetSprite());
	//m_DrawManager->ClearWindow();
	//m_level->Draw(m_DrawManager);
	m_DrawManager->DisplayWindow();
}

bool StartState::IsType(const string &p_sType)
{
	return p_sType.compare("StartState") == 0;
}


