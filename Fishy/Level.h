// Level.h
#pragma once
#include "SpriteManager.h"

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

	bool Load(const string &p_FileName, SpriteManager *p_pSpriteManager);
	void Draw(DrawManager *p_pDrawManager);

private:
	string m_SpriteMapFileName;
	unsigned int m_width;
	unsigned int m_height;
	map<char,Coords> m_TimeCoords;
	
};

