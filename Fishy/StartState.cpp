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
	m_TitleImg = m_SpriteManager->Load("Title_final_smaller.png",0,0,924,216);
	m_TitleImg->setPosition(160,50);

	m_BackGroundImg = m_SpriteManager->Load("background2.jpg",0,0,1280,720);
	m_BackGroundImg->setPosition(0,0);
	// Start
	m_ButtonStartPos = sf::Vector2f(m_TitleImg->getPosition().x + 125 , m_TitleImg->getPosition().y + 350 );
	m_ButtonStart.SetSpriteCircle(m_SpriteManager->Load("play_final_1_smaller.png",0,0,170,177));
	m_ButtonStart.SetPosition(m_ButtonStartPos.x,m_ButtonStartPos.y);

	// Options
	m_ButtonOptionPos = sf::Vector2f(m_TitleImg->getPosition().x + 485 , m_TitleImg->getPosition().y + 350);
	m_ButtonOptions.SetSpriteCircle(m_SpriteManager->Load("Options_final_smaller.png",0,0,170,177));
	m_ButtonOptions.SetPosition(m_ButtonOptionPos.x,m_ButtonOptionPos.y);

	// Quit
	m_ButtonQuitPos = sf::Vector2f(m_TitleImg->getPosition().x + 845 , m_TitleImg->getPosition().y + 350);
	m_ButtonQuit.SetSpriteCircle(m_SpriteManager->Load("exit_final_2_smaller.png",0,0,170,177));
	m_ButtonQuit.SetPosition(m_ButtonQuitPos.x,m_ButtonQuitPos.y);


	m_AvatarAnim = nullptr;
	m_ButtonClick = 0;

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

	int posx = m_window->getDefaultView().getCenter().x;
	int posy = m_window->getDefaultView().getCenter().y + 200.f;

	////PlayerObject måste laddas in som nullptr,
	m_AvatarAnim = new PlayerFishObject(sf::Vector2f(posx, posy ), nullptr, nullptr);
	AnimatedSprite *pxAnimSprite = m_SpriteManager->LoadAnim("../data/anim/PlayerAnimStage1.txt");	
	m_AvatarAnim->AddAnimation("PlayerStage1", pxAnimSprite);
	m_AvatarAnim->SetPosition(sf::Vector2f(posx, posy) );




	return false;
} // 96 29 60

void StartState::ExitState()
{
	cout << "StartState::ExitState" << endl;
	if(m_AvatarAnim != nullptr)
	{
		delete m_AvatarAnim;
		m_AvatarAnim = nullptr;
	}
}

bool StartState::Update(float p_fDeltaTime)
{


	HandleInput();
	m_AvatarAnim->MenuUpdate(p_fDeltaTime);
	return true;
}

void StartState::MouseDown(int x, int y)
{
	MouseOver(x,y);
}
int StartState::MouseOver(int x, int y)
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

	////////////////////
	// Options Button //
	////////////////////

	int optionsX = m_ButtonOptions.GetCircle().getGlobalBounds().left; 
	///cout << "left : " << m_ButtonQuit.GetCircle().getGlobalBounds().left << " ";
	int optionsY = m_ButtonOptions.GetCircle().getGlobalBounds().top;
	//cout << "top : " << m_ButtonQuit.GetCircle().getGlobalBounds().top<< " ";

	circlex = optionsX;
	circley = optionsY;
	deltax = abs(circlex - x);
	deltay = abs(circley - y);
	distancestuff = sqrt( (pow(deltax, 2.0f) + pow(deltay, 2.0f)));

	if(distancestuff < m_ButtonOptions.GetCircle().getRadius())
	{ 
		//cout << "Its alive  x:" << x << "  y: " << y << endl;
		m_ButtonOptions.SetSpriteCircle(m_SpriteManager->Load("Options_final_smaller.png",170,0,170,177));
		m_ButtonOptions.SetPosition(m_ButtonOptionPos.x,m_ButtonOptionPos.y);
		/*if (m_pInputManager->IsReleased(MB_LEFT))
		{
		m_pCore->m_StateManager.SetState("GameState");
		}*/
		//
		return 3;
	} else
	{

		m_ButtonOptions.SetSpriteCircle(m_SpriteManager->Load("Options_final_smaller.png",0,0,170,177));
		m_ButtonOptions.SetPosition(m_ButtonOptionPos.x,m_ButtonOptionPos.y);
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
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num4))
	{
		m_pCore->m_StateManager.SetState("EndState");
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
		}else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 3 && (m_ButtonClick == 0 || m_ButtonClick == 3))
		{
			m_ButtonClick = 3;
			m_ButtonOptions.SetSpriteCircle(m_SpriteManager->Load("Options_final_smaller.png",340,0,170,177));
			m_ButtonOptions.SetPosition(m_ButtonOptionPos.x,m_ButtonOptionPos.y);
		}
		else if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y)  == 0 && m_ButtonClick == 0)
			m_ButtonClick = -1;



	}else if (m_pInputManager->IsReleased(MB_LEFT))
	{
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 1 && m_ButtonClick == 1)
		{
			m_pCore->m_StateManager.SetState("GameState");
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 2 && m_ButtonClick == 2)
		{
			std::exit(0);
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 3 && m_ButtonClick == 3)
		{
			m_pCore->m_StateManager.SetState("OptionState");
		}
		m_ButtonClick = 0;
	}



	//cout << "x : " << sf::Mouse::getPosition().x << " y : " << sf::Mouse::getPosition().y << endl;
}

void StartState::Draw()
{
	m_DrawManager->ClearWindow();
	m_DrawManager->Draw(m_BackGroundImg);
	m_DrawManager->Draw(m_TitleImg);
	//m_pWindow->clear(_sf::Color(0x44,0x55,0x22,0xff));

	m_DrawManager->Draw(m_ButtonStart.GetSprite());
	m_DrawManager->Draw(m_ButtonQuit.GetSprite());
	m_DrawManager->Draw(m_ButtonOptions.GetSprite());
	m_DrawManager->Draw(m_AvatarAnim->GetSprite() );
	//m_DrawManager->ClearWindow();
	//m_level->Draw(m_DrawManager);
	m_DrawManager->DisplayWindow();
}

bool StartState::IsType(const string &p_sType)
{
	return p_sType.compare("StartState") == 0;
}


