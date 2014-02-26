// OptionState.h
#pragma once

#include "State.h"
#include "Core.h"
using namespace std;

class OptionState : public State
{
public:
	OptionState(Core * core);
	/* Called upon OptionState Entry */
	bool EnterState();
	/* Updating OptionState */
	bool Update(float p_deltatime);
	/* Returns True if p_type == OptionState */
	bool IsType(const string &p_type);
	/* Exits OptionState */
	void ExitState();	
	/* Draws OptionState */
	void Draw();
	/* Handle Input in OptionState */
	void HandleInput();

	/* Returns default Next State */
	string Next();
	/*Returns Current State */
	string GetCurrentState();

private:
	Core * m_pCore;
	sf::RenderWindow  *m_window;
	InputManager * m_pInputManager;
	DrawManager * m_DrawManager;
	SpriteManager * m_SpriteManager;
	sf::Sprite *m_BackGroundImg;
	//
	Button m_ButtonMusicMute;
	sf::Vector2f m_ButtonPosMusicMute;
	//
	Button m_ButtonSoundMute;
	sf::Vector2f m_ButtonPosSoundMute;
	//
	Button m_ButtonFullScreen;
	sf::Vector2f m_ButtonPosFullScreen;
	//
	Button m_ButtonWindowed;
	sf::Vector2f m_ButtonPosWindowed;
	//
	Button m_ButtonReturn;
	sf::Vector2f m_ButtonPosReturn;

};