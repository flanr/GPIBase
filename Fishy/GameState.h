// GameState.h
#pragma once
#include "State.h"
#include "Core.h"
#include "SpriteManager.h"
using namespace std;
//FWD declare för testning av circle collider.
class Collider;
class CollisionManager;

class Level;
class PlayerFishObject;
class DrawManager;
class GameObjectManager;
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
	
	void UpdateGUI();


private:
	bool bStateRunning;
	InputManager *m_pInputManager;
	Core *m_pCore;
	sf::RenderWindow *m_window;
	PlayerFishObject *m_player;

	Level * m_LevelLayerForGround;
	Level * m_LevelLayerMidleGround;
	Level * m_LevelLayerBackground;
	SpriteManager * m_SpriteManager;
	DrawManager * m_DrawManager;
	GameObjectManager *m_GameObjMgr;

	Slider m_HealthSlider;
	Slider m_EnergySlider;
	sf::Sprite *Gui;

	
	CollisionManager* mgr;

	sf::FloatRect m_floatrect;
};
