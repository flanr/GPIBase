// GameState.h
#pragma once
#include "State.h"
#include "stdafx.h"
#include "Core.h"
using namespace std;

class PlayerFishObject;
class GameState : public State
{
public:
	GameState(Core* p_core);
	/* Called upon GameState Entry */
	bool EnterState();
	/* Updating GameState */
	bool Update(float p_fDeltatime);
	/*	Returns True if p_type == GameState */
	bool IsType(const string &p_sType);
	/* Exits GameState */
	void ExitState();	
	/* Draws GameState */
	void Draw();
	/* Handle Input in GameState */
	void HandleInput();

	/* Returns default Next State */
	string Next();
	/*Returns Current State */
	string GetCurrentState();

private:
	InputManager *m_pInputManager;
	Core *m_pCore;
	sf::RenderWindow  *m_pWindow;
	PlayerFishObject *m_player;
	sf::Sprite *m_playerSprite;
	Collider *m_collider;

};
