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

	void MouseDown(int x, int y);
	int MouseOver(int x, int y);

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

	sf::Sprite *m_OptionBackground;

	int m_ButtonClick;
	
	// Buttons 
	Button m_ButtonMusicMute;
	sf::Vector2f m_ButtonMusicMutePos;
	Button m_ButtonSoundMute;
	sf::Vector2f m_ButtonSoundMutePos;
	Button m_ButtonFullScreen;
	sf::Vector2f m_ButtonFullScreenPos;
	Button m_ButtonWindowed;
	sf::Vector2f m_ButtonWindowedPos;
	Button m_ButtonReturn;
	sf::Vector2f m_ButtonReturnPos;

	// Sliders
	Slider m_SliderMusicVol;
	Slider m_SliderSoundVol;



};