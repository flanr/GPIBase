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


	unsigned int m_iWidth;
	unsigned int m_iHeight;

	sf::Vector2f m_PlayerStartPosition; 

	map<char,Coords> m_TileCoords;
	vector<GameObject*> m_GameObjects;

};

