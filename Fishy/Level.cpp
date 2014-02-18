// Level.cpp

#include "stdafx.h"
#include "Level.h"
#include "DrawManager.h"
#include "Collider.h"
#include "AnimatedSprite.h"
#include "PlayerFishObject.h"
#include "EnemyFishObject.h"
#include "GameObjectManager.h"


Level::Level(GameObjectManager *p_pxGameObjMgr, CollisionManager * p_CollisionMgr)
{
	m_iHeight = 0;
	m_iWidth = 0;
	m_PlayerStartPosition = sf::Vector2f(0.0f, 0.0f);
	m_pxGameObjMgr = p_pxGameObjMgr;
	m_CollisionMgr = p_CollisionMgr;
}

Level::~Level()
{
}


bool Level::Load(const string &p_sFileName, SpriteManager *p_pSpriteManager, bool p_collider)
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
			} 

			map<char,Coords>::iterator it = m_TileCoords.find(row[i]);
			if (it == m_TileCoords.end())
			{
				continue;
			}

			Coords &c = it->second;
			if (p_collider)
			{
				//måste ligga före ny sprite skapas. annars blir det minneslekage
				if (row[i] == 'S')
				{
					//352.f, 287.f
					Collider *collider = new Collider(sf::Vector2f(iX, iY),sf::Vector2f(c.w, c.h) );
					//PlayerObject måste laddas in som nullptr,
					PlayerFishObject *Player = new PlayerFishObject(sf::Vector2f(iX, iY ), nullptr, collider);
					AnimatedSprite *pxAnimSprite = p_pSpriteManager->LoadAnim("../data/anim/PlayerAnimIdle.txt");	
					Player->AddAnimation("Idle", pxAnimSprite);
					Player->SetPosition(sf::Vector2f(iX, iY) );
					m_pxGameObjMgr->AttachPlayer(Player);
					m_CollisionMgr->AttachCollider(Player->GetCollider() );

					iX += m_iWidth;
					continue;
				}
			}

			sf::Sprite *sprite = p_pSpriteManager->Load(m_SpriteMapFileName, c.x, c.y, c.w, c.h);
			sprite->setOrigin(sprite->getTextureRect().width / 2.0f, sprite->getTextureRect().height / 2.0f);
			sprite->setPosition(iX,iY);

			if (p_collider)
			{

				// Collider
				Collider *collider = new Collider;
				collider->SetPosition(sf::Vector2f(iX,iY) );
				collider->SetExtention(sf::Vector2f(c.w, c.h));
				if (row[i] == 'E')
				{
					EnemyFishObject *enemy = new EnemyFishObject(sprite->getPosition(),sprite,collider);
					enemy->SetPosition(sf::Vector2f(iX, iY) );
					m_pxGameObjMgr->Attach(enemy);
					m_CollisionMgr->AttachCollider(collider);

				}
				else
				{
					GameObject *go = new GameObject(sprite->getPosition(),sprite,collider);
					go->SetPosition(sf::Vector2f(iX,iY));
					m_pxGameObjMgr->Attach(go);
				}

			}else
			{
				GameObject *go = new GameObject(sprite->getPosition(),sprite);
				go->SetPosition(sf::Vector2f(iX,iY));
				m_pxGameObjMgr->Attach(go);
			}

			iX += m_iWidth;
		}
		iY += m_iHeight;
	}
	stream.close();
	return true;
}

void Level::Draw(DrawManager *p_draw_manager)
{
	for(auto i=0UL; i < m_pxGameObjMgr->m_apxGameObject.size();i++)
	{		
		p_draw_manager->Draw(m_pxGameObjMgr->m_apxGameObject[i]->GetSprite());
	}

	p_draw_manager->Draw(m_pxGameObjMgr->m_pxPlayer->GetSprite() );

}
