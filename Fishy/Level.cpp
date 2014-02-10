// Level.cpp

#include "stdafx.h"
#include "Level.h"
#include "DrawManager.h"
#include "Collider.h"
#include "AnimatedSprite.h"
#include "PlayerFishObject.h"
#include "GameObjectManager.h"


Level::Level(GameObjectManager *p_pxGameObjMgr)
{
	m_iHeight = 0;
	m_iWidth = 0;
	m_PlayerStartPosition = sf::Vector2f(0.0f, 0.0f);
	m_pxGameObjMgr = p_pxGameObjMgr;
}

Level::~Level()
{
}


bool Level::Load(const string &p_sFileName, SpriteManager *p_pSpriteManager)
{
	ifstream stream(p_sFileName);

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
			sf::Sprite *sprite = p_pSpriteManager->Load(m_SpriteMapFileName, c.x, c.y, c.w, c.h);

			// Collider
			Collider *collider = new Collider;
			collider->m_position = sf::Vector2f(iX,iY) ;
			collider->m_extention = sf::Vector2f(c.w, c.h);

			GameObject *go = new GameObject(sprite->getPosition(),sprite,collider);
			go->SetPosition(sf::Vector2f(iX,iY));
			m_GameObjects.push_back(go);

			iX += m_iWidth;

		}
		iY += m_iHeight;
	}
	stream.close();
	return true;
}
/*Test function, to load player*/
bool Level::LoadFish(const string &p_sFileName, SpriteManager *p_pSpriteManager)
{
	sf::Sprite *sprite = p_pSpriteManager->Load(m_SpriteMapFileName, 0, 0, 0, 0);
	
	sprite->setPosition(100,100);

	Collider *collider = new Collider;
	collider->m_position = sf::Vector2f(sprite->getPosition() );
	collider->m_extention = sf::Vector2f(sprite->getTextureRect().width, sprite->getTextureRect().height);

	PlayerFishObject *Player = new PlayerFishObject(sprite->getPosition(),nullptr,collider);
	AnimatedSprite *pxAnimSprite = p_pSpriteManager->LoadAnim(p_sFileName);	
	Player->AddAnimation("Idle", pxAnimSprite);
	Player->SetPosition(sf::Vector2f(800,0));
	m_pxGameObjMgr->AttachPlayer(Player);
	return true;
}


void Level::Draw(DrawManager *p_draw_manager)
{
	for(auto i=0UL; i < m_GameObjects.size();i++)
	{		
		p_draw_manager->Draw(m_GameObjects[i]->GetSprite());
	}
	//& sprite eller sf::sprite? animSprite?z
	//p_draw_manager->Draw(m_pxGameObjMgr->m_pxPlayer->GetSprite() );

	//for( auto i = 0UL; i < m_pxGameObjMgr->m_apxGameObj.size(); i++)		//0UL = 0 unsigned long
	//{
	//	p_pxDrawManager->DrawSprite(m_pxGameObjMgr->m_apxGameObj[i]->GetSprite(),
	//		m_pxGameObjMgr->m_apxGameObj[i]->GetPosition().m_fX,
	//		m_pxGameObjMgr->m_apxGameObj[i]->GetPosition().m_fY);
	//}

}
