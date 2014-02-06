// Level.h
#pragma once
#include "SpriteManager.h"
#include "GameObject.h"
using namespace std;

class Level
{
	struct Coords
	{
		int x, y, w, h;
	};

public:
	Level();
	~Level();

	bool Load(const string &p_sFileName, SpriteManager *p_pSpriteManager);
	void Draw(DrawManager *p_pDrawManager);

protected:
	string m_SpriteMapFileName;
<<<<<<< HEAD
	unsigned int m_iWidth;
	unsigned int m_iHeight;
	map<char,Coords> m_TileCoords;
	
=======

	unsigned int m_iWidth;
	unsigned int m_iHeight;

	map<char,Coords> m_TileCoords;
	// vector<GameObject*> m_GameObjects;
>>>>>>> 3ff671343fa104d8b0b5dbcc188dc7de727a080c
};

