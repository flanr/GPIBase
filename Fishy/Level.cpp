// Level.cpp

#include "stdafx.h"
#include "Level.h"


Level::Level()
{
	m_iHeight = 0;
	m_iWidth = 0;
	m_PlayerStartPosition = sf::Vector2f(0.0f, 0.0f);
}

Level::~Level()
{
}


bool Level::Load(const string &p_sFileName, SpriteManager *p_pSpriteManager)
{
	ifstream stream(p_sFileName);
<<<<<<< HEAD
=======

>>>>>>> 1a6e168bbf056e4ea998c190a3f0928608c8c228
	if (!stream.is_open())
	{
		return false;
	}

	string row;
	unsigned int iCoordCount = 0;
	stream >> m_SpriteMapFileName;
	stream >> iCoordCount >> m_iWidth >> m_iHeight;
	getline(stream,row);

	for (unsigned int i = 0; i < iCoordCount; i++)
	{
		getline(stream,row);
		stringstream ss(row);
		string ch;
		Coords coord;

		ss >> ch;
		ss >> coord.x;
		ss >> coord.y;
		ss >> coord.w;
		ss >> coord.h;

		m_TileCoords.insert( pair<char,Coords> (ch[0],coord));

	}
	unsigned int iX = 0;
	unsigned int iY = 0;

	while (!stream.eof())
	{
		iX = 0;
		getline(stream, row, '\n');
		if (row.length()==0)
		{
			continue;
		}

		for (unsigned int i = 0; i < row.length(); i++)
		{
			if (row[i] == '0')
			{
				iX += m_iWidth;
				continue;
			} else if (row[i] == 'S')
			{
				//start pos x
				//start pos y
				iX += m_iWidth;
			}

			map<char,Coords>::iterator it = m_TileCoords.find(row[i]);
			if (it == m_TileCoords.end())
			{
				continue;
			}

			Coords &c = it->second;
			//sf::Sprite *sprite = p_pSpriteManager->Load(m_SpriteMapFileName, c.x, c.y, c.w, c.h); // Sprite

			// Collider
			//Collider 


			iX += m_iWidth;

		}
		iY += m_iHeight;
	}
	stream.close();
	return true;
}
