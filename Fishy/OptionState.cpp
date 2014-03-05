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
	// OptionBackground
	m_OptionBackground = m_SpriteManager->Load("optionsbg.png",0,0,851,518);
	m_OptionBackground->setPosition(200,100);

	////////////////
	//  Buttons   //
	////////////////

	// Mute Music
	m_ButtonMusicMute.SetSpriteRect(m_SpriteManager->Load("mute.png",0,0,85,57));
	m_ButtonMusicMutePos = sf::Vector2f(m_OptionBackground->getPosition().x + 701,m_OptionBackground->getPosition().y + 176 );
	m_ButtonMusicMute.SetPosition(m_ButtonMusicMutePos.x, m_ButtonMusicMutePos.y);
	// Mute Sound  
	m_ButtonSoundMute.SetSpriteRect(m_SpriteManager->Load("mute.png",0,0,85,57));
	m_ButtonSoundMutePos = sf::Vector2f(m_OptionBackground->getPosition().x + 701,m_OptionBackground->getPosition().y + 283);
	m_ButtonSoundMute.SetPosition(m_ButtonSoundMutePos.x,m_ButtonSoundMutePos.y);
	// Fullscreen
	m_ButtonFullScreen.SetSpriteRect(m_SpriteManager->Load("fullscreen.png",0,0,244,57));
	m_ButtonFullScreenPos = sf::Vector2f(m_OptionBackground->getPosition().x + 98,m_OptionBackground->getPosition().y + 389);
	m_ButtonFullScreen.SetPosition(m_ButtonFullScreenPos.x,m_ButtonFullScreenPos.y);
	// Windowed
	m_ButtonWindowed.SetSpriteRect(m_SpriteManager->Load("windowed.png",0,0,244,57));
	m_ButtonWindowedPos = sf::Vector2f(m_OptionBackground->getPosition().x + 364,m_OptionBackground->getPosition().y + 389);
	m_ButtonWindowed.SetPosition(m_ButtonWindowedPos.x,m_ButtonWindowedPos.y);
	// Return
	m_ButtonReturn.SetSpriteRect(m_SpriteManager->Load("backarrow.png",0,0,85,58));
	m_ButtonReturnPos = sf::Vector2f(m_OptionBackground->getPosition().x + 702 ,m_OptionBackground->getPosition().y + 391);
	m_ButtonReturn.SetPosition(m_ButtonReturnPos.x,m_ButtonReturnPos.y);

	/////////////
	// Sliders //
	/////////////
	m_SliderMusicVol.SetSlider(m_OptionBackground->getPosition().x+65,m_OptionBackground->getPosition().y+205,600,25);
	m_SliderMusicVol.SetColor(sf::Color::White);

	m_SliderSoundVol.SetSlider(m_OptionBackground->getPosition().x+65,m_OptionBackground->getPosition().y+314,600,25);
	m_SliderSoundVol.SetColor(sf::Color::White);

	m_ButtonClick = 0;
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
	m_window->setView(m_window->getDefaultView());
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
	MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);

	if (m_pInputManager->IsDown(MB_LEFT))
	{
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 1 && (m_ButtonClick == 0 || m_ButtonClick == 1)) // Fullscreen
		{
			m_ButtonClick = 1;
			m_ButtonFullScreen.SetSpriteRect(m_SpriteManager->Load("fullscreen.png",488,0,244,57)); 
			m_ButtonFullScreen.SetPosition(m_ButtonFullScreenPos.x,m_ButtonFullScreenPos.y);
		}
		else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 2 && (m_ButtonClick == 0 || m_ButtonClick == 2)) // Windowed
		{
			m_ButtonClick = 2;
			m_ButtonWindowed.SetSpriteRect(m_SpriteManager->Load("windowed.png",488,0,244,57)); 
			m_ButtonWindowed.SetPosition(m_ButtonWindowedPos.x,m_ButtonWindowedPos.y);
		}
		else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 3 && (m_ButtonClick == 0 || m_ButtonClick == 3)) // Music
		{
			m_ButtonClick = 3;
			m_ButtonMusicMute.SetSpriteRect(m_SpriteManager->Load("mute.png",170,0,85,57));
			m_ButtonMusicMute.SetPosition(m_ButtonMusicMutePos.x,m_ButtonMusicMutePos.y);

		}
		else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 4 && (m_ButtonClick == 0 || m_ButtonClick == 4)) // Sound 
		{
			m_ButtonClick = 4;
			m_ButtonSoundMute.SetSpriteRect(m_SpriteManager->Load("mute.png",170,0,85,57));
			m_ButtonSoundMute.SetPosition(m_ButtonSoundMutePos.x,m_ButtonSoundMutePos.y);

		}
		else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 5 && (m_ButtonClick == 0 || m_ButtonClick == 5)) // Back
		{
			m_ButtonClick = 5;
			m_ButtonReturn.SetSpriteRect(m_SpriteManager->Load("backarrow.png",170,0,85,57));
			m_ButtonReturn.SetPosition(m_ButtonReturnPos.x,m_ButtonReturnPos.y);
		}
		else if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y)  == 0 && m_ButtonClick == 0)
			m_ButtonClick = -1;

		//m_pCore->window->create(sf::VideoMode(1280,720), "SUPER MEGA AWESOME GAME", sf::Style::Fullscreen);
	}
	else if (m_pInputManager->IsReleased(MB_LEFT))
	{
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 1 && m_ButtonClick == 1) // Fullscreen
		{
			m_pCore->window->create(sf::VideoMode(1280,720), "SUPER MEGA AWESOME GAME", sf::Style::Fullscreen);
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 2 && m_ButtonClick == 2) // Windowed
		{
			m_pCore->window->create(sf::VideoMode(1280,720), "SUPER MEGA AWESOME GAME");
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 3 && m_ButtonClick == 3) // Music
		{

		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 4 && m_ButtonClick == 4) // Sound
		{

		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 5 && m_ButtonClick == 5) // Back
		{
			m_pCore->m_StateManager.SetState("StartState");
		}
		m_ButtonClick = 0;
	}
}

void OptionState::MouseDown(int x, int y)
{
	MouseOver(x,y);
}

int OptionState::MouseOver(int x, int y)
{
	int circlex;
	int circley;
	int deltax;
	int deltay;
	int distancestuff;

	////////////////
	// FullScreen //
	////////////////

	int bw = m_ButtonFullScreen.GetSprite()->getGlobalBounds().width;
	int bh = m_ButtonFullScreen.GetSprite()->getGlobalBounds().height;
	int bx = m_ButtonFullScreen.GetSprite()->getGlobalBounds().left; 
	int by = m_ButtonFullScreen.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) ) 
	{
		m_ButtonFullScreen.SetSpriteRect(m_SpriteManager->Load("fullscreen.png",244,0,244,57));
		m_ButtonFullScreen.SetPosition(m_ButtonFullScreenPos.x,m_ButtonFullScreenPos.y);
		return 1;
	}else
	{
		m_ButtonFullScreen.SetSpriteRect(m_SpriteManager->Load("fullscreen.png",0,0,244,57));
		m_ButtonFullScreen.SetPosition(m_ButtonFullScreenPos.x, m_ButtonFullScreenPos.y);
	}

	///////////////
	// Windowed  //
	///////////////

	bw = m_ButtonWindowed.GetSprite()->getGlobalBounds().width;
	bh = m_ButtonWindowed.GetSprite()->getGlobalBounds().height;
	bx = m_ButtonWindowed.GetSprite()->getGlobalBounds().left; 
	by = m_ButtonWindowed.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) )  
	{
		m_ButtonWindowed.SetSpriteRect(m_SpriteManager->Load("windowed.png",244,0,244,57));
		m_ButtonWindowed.SetPosition(m_ButtonWindowedPos.x,m_ButtonWindowedPos.y);
		return 2;
	}else
	{
		m_ButtonWindowed.SetSpriteRect(m_SpriteManager->Load("windowed.png",0,0,244,57));
		m_ButtonWindowed.SetPosition(m_ButtonWindowedPos.x, m_ButtonWindowedPos.y);
	}

	///////////////
	// Music  //
	///////////////

	bw = m_ButtonMusicMute.GetSprite()->getGlobalBounds().width;
	bh = m_ButtonMusicMute.GetSprite()->getGlobalBounds().height;
	bx = m_ButtonMusicMute.GetSprite()->getGlobalBounds().left; 
	by = m_ButtonMusicMute.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) )  
	{
		m_ButtonMusicMute.SetSpriteRect(m_SpriteManager->Load("mute.png",85,0,85,57));
		m_ButtonMusicMute.SetPosition(m_ButtonMusicMutePos.x,m_ButtonMusicMutePos.y);
		return 3;
	}else
	{
		m_ButtonMusicMute.SetSpriteRect(m_SpriteManager->Load("mute.png",0,0,85,57));
		m_ButtonMusicMute.SetPosition(m_ButtonMusicMutePos.x, m_ButtonMusicMutePos.y);
	}

	///////////////
	// Sound  //
	///////////////

	bw = m_ButtonSoundMute.GetSprite()->getGlobalBounds().width;
	bh = m_ButtonSoundMute.GetSprite()->getGlobalBounds().height;
	bx = m_ButtonSoundMute.GetSprite()->getGlobalBounds().left; 
	by = m_ButtonSoundMute.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) )  
	{
		m_ButtonSoundMute.SetSpriteRect(m_SpriteManager->Load("mute.png",85,0,85,57));
		m_ButtonSoundMute.SetPosition(m_ButtonSoundMutePos.x,m_ButtonSoundMutePos.y);
		return 4;
	}else
	{
		m_ButtonSoundMute.SetSpriteRect(m_SpriteManager->Load("mute.png",0,0,85,57));
		m_ButtonSoundMute.SetPosition(m_ButtonSoundMutePos.x, m_ButtonSoundMutePos.y);
	}


	///////////////
	// Back  //
	///////////////

	bw = m_ButtonReturn.GetSprite()->getGlobalBounds().width;
	bh = m_ButtonReturn.GetSprite()->getGlobalBounds().height;
	bx = m_ButtonReturn.GetSprite()->getGlobalBounds().left; 
	by = m_ButtonReturn.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) )  
	{
		m_ButtonReturn.SetSpriteRect(m_SpriteManager->Load("backarrow.png",85,0,85,57));
		m_ButtonReturn.SetPosition(m_ButtonReturnPos.x,m_ButtonReturnPos.y);
		return 5;
	}else
	{
		m_ButtonReturn.SetSpriteRect(m_SpriteManager->Load("backarrow.png",0,0,85,57));
		m_ButtonReturn.SetPosition(m_ButtonReturnPos.x, m_ButtonReturnPos.y);
	}



	return 0;
}


void OptionState::Draw()
{
	m_DrawManager->ClearWindow();
	m_DrawManager->Draw(m_BackGroundImg);
	m_DrawManager->Draw(m_OptionBackground);
	m_DrawManager->Draw(m_ButtonMusicMute.GetSprite());
	m_DrawManager->Draw(m_ButtonSoundMute.GetSprite());
	m_DrawManager->Draw(m_ButtonFullScreen.GetSprite());
	m_DrawManager->Draw(m_ButtonWindowed.GetSprite());
	m_DrawManager->Draw(m_ButtonReturn.GetSprite());
	m_DrawManager->DrawSlider(m_SliderMusicVol);
	m_DrawManager->DrawSlider(m_SliderSoundVol);

	//m_level->Draw(m_DrawManager);
	m_DrawManager->DisplayWindow();
}

bool OptionState::IsType(const string &p_sType)
{
	return p_sType.compare("OptionState") == 0;
}


