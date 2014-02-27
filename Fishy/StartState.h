// StartState.h
#pragma once

#include "State.h"
#include "Slider.h"

using namespace std;
class SpriteManager;
class StartState : public State
{
public:
	StartState(Core *core);
	/* Called upon StartState Entry */
	bool EnterState();
	/* Updating StartState */
	bool Update(float p_fDeltaTime);
	/*	Returns True if p_type == StartState */
	bool IsType(const string &p_sType);
	/* Exits StartState */
	void ExitState();	
	/* Draws StartState */
	void Draw();
	/* Handle Input in StartState */
	void HandleInput();

	void MouseDown(int x, int y);
	int MouseOver(int x, int y);

	/* Returns default Next State */
	string Next();
	/*Returns Current State */
	string GetCurrentState();

private:
	Core* m_pCore;
	sf::RenderWindow *m_window;
	InputManager * m_pInputManager;
	DrawManager * m_DrawManager;
	SpriteManager *m_SpriteManager;
	sf::Sprite *m_BackGroundImg;
	// Start
	Button m_ButtonStart;
	sf::Vector2f m_ButtonStartPos;
	// Quit
	Button m_ButtonQuit;
	sf::Vector2f m_ButtonQuitPos;
	// Option
	Button m_ButtonOptions;
	sf::Vector2f m_ButtonOptionPos;

	int m_ButtonClick;

};