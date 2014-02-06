// Core.h
#include "stdafx.h"
#pragma once
#include "StateManager.h"
//using namespace sf;

class InputManager;
class PlayerFishObject;
class Collider;

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

	PlayerFishObject *m_player;

	bool m_bRunning;

	float m_fDeltaTime;

	InputManager* m_pInputManager;
	
	sf::Sprite *playerSprite;
	
	Collider *collider;

private:

};