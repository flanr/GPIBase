// Level.cpp

#include "stdafx.h"
#include "Level.h"

Level::Level()
{
	m_iHeight = 0;
	m_iWidth = 0;
}

Level::~Level()
{
}

bool Level::Load(const string &p_FileName, SpriteManager* p_pSpriteManager)
{
	ifstream stream(p_FileName);

	if (!stream.is_open())
	{
		return false;
	}

	string row;
	unsigned int iCoordCount = 0;
	stream >> m_SpriteMapFileName;


}
