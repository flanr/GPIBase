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

<<<<<<< HEAD
bool Level::Load(const string &p_FileName, SpriteManager* p_pSpriteManager)
{
	ifstream stream(p_FileName);

=======
bool Level::Load(const string &p_sFileName, SpriteManager *p_pSpriteManager)
{
	ifstream stream(p_sFileName);
>>>>>>> 3ff671343fa104d8b0b5dbcc188dc7de727a080c
	if (!stream.is_open())
	{
		return false;
	}
<<<<<<< HEAD

	string row;
	unsigned int iCoordCount = 0;
	stream >> m_SpriteMapFileName;


=======
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
			Sprite *sprite = p_pSpriteManager->Load(m_SpriteMapFileName, c.x, c.y, c.w, c.h);
			iX += m_iWidth;

		}
		iY += m_iHeight;
	}
	stream.close();
	return true;
>>>>>>> 3ff671343fa104d8b0b5dbcc188dc7de727a080c
}
