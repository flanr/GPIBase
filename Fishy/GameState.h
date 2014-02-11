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

	//Orre testar

	sf::CircleShape m_shape;
	sf::CircleShape m_shape2;
	sf::CircleShape m_shape3;
	sf::RectangleShape m_rectShape;
	sf::RectangleShape m_rectShape2;
	sf::RectangleShape m_rectShape3;
	Collider* m_circle;
	Collider* m_circle2;
	Collider* m_rect;
	Collider* m_circle3;
	Collider* m_rect2;
	Collider* m_rect3;
	CollisionManager* mgr;

	sf::FloatRect m_floatrect;
};
