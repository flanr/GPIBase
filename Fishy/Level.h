// Level.h
#pragma once
#include "SpriteManager.h"
#include "GameObject.h"
#include "PlayerFishObject.h"

class GameObjectManager;

using namespace std;

class Level
{
	struct Coords
	{
		int x, y, w, h;
	};

public:
	Level(GameObjectManager *p_pxGameObjMgr = nullptr);
	~Level();

	bool Load(const string &p_sFileName, SpriteManager *p_pSpriteManager);
	bool LoadFish(const string &p_sFileName, SpriteManager *p_pSpriteManager, sf::RenderWindow *p_window);
	void Draw(DrawManager *p_pDrawManager);

protected:
	string m_SpriteMapFileName;


	unsigned int m_iWidth;
	unsigned int m_iHeight;

	sf::Vector2f m_PlayerStartPosition; 

	map<char,Coords> m_TileCoords;
	//vector<GameObject*> m_GameObjects;
	GameObjectManager *m_pxGameObjMgr;

};

