// Core.h
//#include "stdafx.h"
#include "StateManager.h"
#pragma once

//using namespace sf;
//class StateManager;
class InputManager;
class DrawManager;
class SpriteManager;
class GameObjectManager;

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

	void UpdateDeltatime();

public:
	StateManager m_StateManager;
	DrawManager *m_DrawManager;
	SpriteManager *m_SpriteManager;
	GameObjectManager *m_GameObjectManager;
	SoundManager *m_SoundManager;
	sf::RenderWindow  *window;

	PlayerFishObject *m_player;

	bool m_bRunning;

	float m_fDeltaTime;

	InputManager* m_pInputManager;
	
	sf::Sprite *playerSprite;
	
	Collider *collider;

private:
	sf::Clock m_Clock;
	sf::Time m_TimeSinceLastUpdate;
};