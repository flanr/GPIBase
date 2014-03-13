// Level.h
#pragma once
#include "SpriteManager.h"
#include "GameObject.h"
#include "PlayerFishObject.h"


class GameObjectManager;
class CollisionManager;
class Camera;

using namespace std;
enum ELayer
	{
		LOWESTBG,
		SECONDLOWESTBG,
		HIGHESTBG,
		MIDDLEGROUND,
		MIDDLEFROUNT,
		FOREGROUND
		
	};
class Level
{
	struct Coords
	{
		int x, y, w, h;
	};

public:
	

public:
	Level(GameObjectManager *p_pxGameObjMgr = nullptr, CollisionManager * p_CollisionMgr = nullptr);
	~Level();
	/* If bool value = true create level with colliders, If False no colliders */
	bool Load(const string &p_sFileName, SpriteManager *p_pSpriteManager, bool p_collider, ELayer layer);
	void Draw(DrawManager *p_pDrawManager, Camera *p_Camera);
	void UpdateParallax(Camera *p_Camera);

	unsigned int GetWidth();
	unsigned int GetHeight();

	float Random(float min, float max);
protected:
	string m_SpriteMapFileName;


	unsigned int m_iWidth;
	unsigned int m_iHeight;
	unsigned int m_LevelWidth;
	unsigned int m_LevelHeight;

	sf::Vector2f m_PlayerStartPosition; 

	map<char,Coords> m_TileCoords;
	//vector<GameObject*> m_GameObjects;
	GameObjectManager *m_pxGameObjMgr;
	CollisionManager * m_CollisionMgr;
};

