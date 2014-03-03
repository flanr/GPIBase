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
	m_OptionBackground->setPosition(0,0);
	
	////////////////
	//  Buttons   //
	////////////////

	// Mute Music
	m_ButtonMusicMute.SetSprite(m_SpriteManager->Load("mute.png",17,15,85,58));
	m_ButtonMusicMute.SetPosition(m_OptionBackground->getPosition().x + 743,m_OptionBackground->getPosition().y + 205);
	// Mute Sound  
	m_ButtonSoundMute.SetSprite(m_SpriteManager->Load("mute.png",17,15,85,58));
	m_ButtonSoundMute.SetPosition(m_OptionBackground->getPosition().x + 743,m_OptionBackground->getPosition().y + 312);
	// Fullscreen
	m_ButtonFullScreen.SetSprite(m_SpriteManager->Load("fullscreen.png",22,27,244,57));
	m_ButtonFullScreen.SetPosition(m_OptionBackground->getPosition().x + 215,m_OptionBackground->getPosition().y + 420);
	// Windowed
	m_ButtonWindowed.SetSprite(m_SpriteManager->Load("windowed.png",22,27,244,57));
	m_ButtonWindowed.SetPosition(m_OptionBackground->getPosition().x + 485,m_OptionBackground->getPosition().y + 420);
	// Return
	m_ButtonReturn.SetSprite(m_SpriteManager->Load("backarrow.png",17,15,85,58));
	m_ButtonReturn.SetPosition(m_OptionBackground->getPosition().x + 745 ,m_OptionBackground->getPosition().y + 420);
	
	/////////////
	// Sliders //
	/////////////
	m_SliderMusicVol.SetSlider(m_OptionBackground->getPosition().x+65,m_OptionBackground->getPosition().y+206,600,25);
	m_SliderMusicVol.SetColor(sf::Color::White);
	
	m_SliderSoundVol.SetSlider(m_OptionBackground->getPosition().x+65,m_OptionBackground->getPosition().y+314,600,25);
	m_SliderSoundVol.SetColor(sf::Color::White);


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


