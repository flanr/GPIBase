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

	

	m_BackGroundImg = m_SpriteManager->Load("game_over_background.jpg",0,0,1280,720);
	m_BackGroundImg->setPosition(0,0);
	m_GameOverImg = m_SpriteManager->Load("game_over_text.png",0,0,585,216);
	m_GameOverImg->setPosition(m_window->getDefaultView().getCenter().x - (585 /2.0f), 50);
	m_Deadfish = m_SpriteManager->Load("player_sheet_v4.png",1185, 1560, 237, 195);
	m_Deadfish->setPosition( m_window->getDefaultView().getCenter().x - (237 / 2.0f), m_window->getDefaultView().getCenter().y - (195 / 2.0f)  );

	// Start
	m_ButtonStartPos = sf::Vector2f(m_GameOverImg->getPosition().x , m_GameOverImg->getPosition().y + 450 );
	m_ButtonStart.SetSpriteCircle(m_SpriteManager->Load("play_final_1_smaller.png",0,0,170,177));
	m_ButtonStart.SetPosition(m_ButtonStartPos.x,m_ButtonStartPos.y);

	// Quit
	m_ButtonQuitPos = sf::Vector2f(m_GameOverImg->getPosition().x + 585 , m_GameOverImg->getPosition().y + 450);
	m_ButtonQuit.SetSpriteCircle(m_SpriteManager->Load("exit_final_2_smaller.png",0,0,170,177));
	m_ButtonQuit.SetPosition(m_ButtonQuitPos.x,m_ButtonQuitPos.y);

	

	m_ButtonClick = 0;

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


void EndState::MouseDown(int x, int y)
{
	MouseOver(x,y);
}
int EndState::MouseOver(int x, int y)
{
	int circlex;
	int circley;
	int deltax;
	int deltay;
	int distancestuff;

	//////////////////
	// Start Button //
	//////////////////

	int startX = m_ButtonStart.GetCircle().getGlobalBounds().left; 
	///cout << "left : " << m_ButtonQuit.GetCircle().getGlobalBounds().left << " ";
	int startY = m_ButtonStart.GetCircle().getGlobalBounds().top;
	//cout << "top : " << m_ButtonQuit.GetCircle().getGlobalBounds().top<< " ";

	circlex = startX;
	circley = startY;
	deltax = abs(circlex - x);
	deltay = abs(circley - y);
	distancestuff = sqrt( (pow(deltax, 2.0f) + pow(deltay, 2.0f)));
	if(distancestuff < m_ButtonStart.GetCircle().getRadius())
	{ 
		//cout << "Its alive  x:" << x << "  y: " << y << endl;
		m_ButtonStart.SetSpriteCircle(m_SpriteManager->Load("play_final_1_smaller.png",170,0,170,177));
		m_ButtonStart.SetPosition(m_ButtonStartPos.x,m_ButtonStartPos.y);
		/*if (m_pInputManager->IsReleased(MB_LEFT))
		{
		m_pCore->m_StateManager.SetState("GameState");
		}*/
		//
		//m_pCore->m_SoundManager->PlayMusic("vandalism.flac");

		return 1;
	} else
	{

		m_ButtonStart.SetSpriteCircle(m_SpriteManager->Load("play_final_1_smaller.png",0,0,170,177));
		m_ButtonStart.SetPosition(m_ButtonStartPos.x,m_ButtonStartPos.y);
	}

	/////////////////
	// Quit Button //
	/////////////////

	int quitX = m_ButtonQuit.GetCircle().getGlobalBounds().left; 
	int quitY = m_ButtonQuit.GetCircle().getGlobalBounds().top;
	if ((x > quitX - m_ButtonQuit.GetCircle().getRadius() & x < quitX + m_ButtonQuit.GetCircle().getRadius() ) && (y > quitY - m_ButtonQuit.GetCircle().getRadius()  && y < quitY + m_ButtonQuit.GetCircle().getRadius() ) ) 
	{
		m_ButtonQuit.SetSpriteCircle(m_SpriteManager->Load("exit_final_2_smaller.png",170,0,170,177));
		m_ButtonQuit.SetPosition(m_ButtonQuitPos.x,m_ButtonQuitPos.y);
		return 2;
	}else
	{
		m_ButtonQuit.SetSpriteCircle(m_SpriteManager->Load("exit_final_2_smaller.png",0,0,170,177));
		m_ButtonQuit.SetPosition(m_ButtonQuitPos.x,m_ButtonQuitPos.y);
	}

	return 0;
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
	m_DrawManager->Draw(m_BackGroundImg);
	m_DrawManager->Draw(m_GameOverImg);
	m_DrawManager->Draw(m_Deadfish);
	m_DrawManager->Draw(m_ButtonStart.GetSprite());
	m_DrawManager->Draw(m_ButtonQuit.GetSprite());
	m_DrawManager->DisplayWindow();
}
void EndState::HandleInput()
{
		if(m_pInputManager->IsDownOnceK(sf::Keyboard::Num1))
	{
		//m_pCore->m_StateManager.SetState("StartState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num2))
	{
		//m_pCore->m_StateManager.SetState("GameState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num3))
	{
		//m_pCore->m_StateManager.SetState("OptionState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num4))
	{
		//cout << " You are already in EndState" << endl;
	}

	MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);
	if (m_pInputManager->IsDown(MB_LEFT))
	{
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 1 && (m_ButtonClick == 0 || m_ButtonClick == 1))
		{
			m_ButtonClick = 1;
			m_ButtonStart.SetSpriteCircle(m_SpriteManager->Load("play_final_1_smaller.png",340,0,170,177));
			m_ButtonStart.SetPosition(m_ButtonStartPos.x,m_ButtonStartPos.y);
		}
		else if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 2 && (m_ButtonClick == 0 || m_ButtonClick == 2))
		{
			m_ButtonClick = 2;
			m_ButtonQuit.SetSpriteCircle(m_SpriteManager->Load("exit_final_2_smaller.png",340,0,170,177));
			m_ButtonQuit.SetPosition(m_ButtonQuitPos.x,m_ButtonQuitPos.y);
		}
		else if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y)  == 0 && m_ButtonClick == 0)
			m_ButtonClick = -1;



	}else if (m_pInputManager->IsReleased(MB_LEFT))
	{
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 1 && m_ButtonClick == 1)
		{
			m_pCore->m_StateManager.SetState("GameState");
			m_SoundManager->PlayMusic("WIPFishyAmbient_1.ogg");
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 2 && m_ButtonClick == 2)
		{
			std::exit(0);
		}
		m_ButtonClick = 0;
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