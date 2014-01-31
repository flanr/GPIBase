// Core.h
#include "stdafx.h"
#pragma once
#include "StateManager.h"
//using namespace sf;

class InputManager;

class Core
{
public:
	Core();
	~Core();
	/*	Inizializes the Game Window*/
	bool Initialize();
	/*	The Main Game Loop
	Runs Every Frame */
	void Run();
	/*	Cleans up all the Pointers when closing down */
	void Cleanup();

public:
	StateManager m_StateManager;

	sf::RenderWindow  *window;

	bool m_bRunning;

	float m_fDeltaTime;

	InputManager* m_pInputManager;
private:

};
