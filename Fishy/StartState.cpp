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

	//m_BackGroundImg->setPosition(1.0f,1.0f);

	m_BackGroundImg = m_SpriteManager->Load("background2.jpg",0,0,1280,720);
	m_BackGroundImg->setPosition(0,0);
	m_ButtonQuit.SetSprite(m_SpriteManager->Load("Button_concept_small.png",0,0,150,150));
	m_ButtonQuit.SetPosition(500,350);


	button_down = false;

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
	m_window->setView(m_window->getDefaultView());
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
	MouseOver(x,y);
	button_down = true;
}
int StartState::MouseOver(int x, int y)
{

	int xx = m_ButtonQuit.GetCircle().getGlobalBounds().left; 
	///cout << "left : " << m_ButtonQuit.GetCircle().getGlobalBounds().left << " ";
	int yy = m_ButtonQuit.GetCircle().getGlobalBounds().top;
	//cout << "top : " << m_ButtonQuit.GetCircle().getGlobalBounds().top<< " ";
	int rad = m_ButtonQuit.GetCircle().getRadius();
	//cout << "radius : " << m_ButtonQuit.GetCircle().getRadius() << " " << endl;;

	int circlex = xx;
	int circley = yy;
	int mousex = x;
	int mousey = y;

	int deltax = abs(circlex - x);
	int deltay = abs(circley - y);

	int distancestuff = sqrt( (pow(deltax, 2.0f) + pow(deltay, 2.0f)));

	//if ((x > xx - m_ButtonQuit.GetCircle().getRadius() & x < xx + m_ButtonQuit.GetCircle().getRadius() ) && (y > yy - m_ButtonQuit.GetCircle().getRadius()  && y < yy + m_ButtonQuit.GetCircle().getRadius() ) )
	if(distancestuff < m_ButtonQuit.GetCircle().getRadius())
	{ 
		cout << "Its alive  x:" << x << "  y: " << y << endl;
		m_ButtonQuit.SetSprite(m_SpriteManager->Load("Button_concept_small.png",150,0,150,150)); 
		m_ButtonQuit.SetPosition(500,350);
		/*if (m_pInputManager->IsReleased(MB_LEFT))
		{
		m_pCore->m_StateManager.SetState("GameState");
		}*/
		//
		return 1;
	} else
	{

		m_ButtonQuit.SetSprite(m_SpriteManager->Load("Button_concept_small.png",0,0,150,150)); 
		m_ButtonQuit.SetPosition(500,350);
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
	if (m_pInputManager->IsDown(MB_LEFT))
	{
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 1)
		{
			m_ButtonQuit.SetSprite(m_SpriteManager->Load("Button_concept_small.png",300,0,152,150)); 
		m_ButtonQuit.SetPosition(500,350);
		}


	}else if (m_pInputManager->IsReleased(MB_LEFT))
	{
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 1)
		{
			m_pCore->m_StateManager.SetState("GameState");
		}

	}



	//cout << "x : " << sf::Mouse::getPosition().x << " y : " << sf::Mouse::getPosition().y << endl;
}

void StartState::Draw()
{
	m_DrawManager->ClearWindow();
	m_DrawManager->Draw(m_BackGroundImg);
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


