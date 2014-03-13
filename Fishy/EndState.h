#pragma once
#include "state.h"
class EndState : public State
{
public:
	EndState(Core* core);
	~EndState(void);


	bool EnterState();
	bool Update(float p_deltatime);
	bool IsType(const string &p_type);
	void ExitState();	
	void Draw();
	void HandleInput();

	string Next();
	string GetCurrentState();

private:
	Core * m_pCore;
	sf::RenderWindow  *m_window;
	InputManager * m_pInputManager;
	DrawManager * m_DrawManager;
	SpriteManager * m_SpriteManager;
	SoundManager * m_SoundManager;

	sf::Sprite *m_BackGroundImg;


};

