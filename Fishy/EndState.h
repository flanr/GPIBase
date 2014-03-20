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

	void MouseDown(int x, int y);
	int MouseOver(int x, int y);

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
	sf::Sprite *m_GameOverImg;
	sf::Sprite *m_Deadfish;
	
	// Start
	Button m_ButtonStart;
	sf::Vector2f m_ButtonStartPos;
	// Quit
	Button m_ButtonQuit;
	sf::Vector2f m_ButtonQuitPos;

	int m_ButtonClick;


};

