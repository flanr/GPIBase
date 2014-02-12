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
	
};