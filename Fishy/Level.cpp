// Level.cpp

#include "stdafx.h"
#include "Level.h"
#include "DrawManager.h"
#include "Collider.h"
#include "AnimatedSprite.h"
#include "PlayerFishObject.h"
#include "EnemyFishObject.h"
#include "GameObjectManager.h"
#include "LightSource.h"


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


bool Level::Load(const string &p_sFileName, SpriteManager *p_pSpriteManager, bool p_collider, int setLayer)
{
	int count = 0;
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
					AnimatedSprite *pxAnimSprite = p_pSpriteManager->LoadAnim("../data/anim/PlayerAnim.txt");	
					Player->AddAnimation("Player", pxAnimSprite);
					Player->SetPosition(sf::Vector2f(iX, iY) );
					Player->SetLevelLayer(1);
					Player->AddLightSource(new LightSource(sf::Vector2f(iX, iY), 240) );
					m_pxGameObjMgr->AttachPlayer(Player);
					m_CollisionMgr->AttachCollider(Player->GetCollider() );
					iX += m_iWidth;
					continue;
				}
			}

			sf::Sprite *sprite = p_pSpriteManager->Load(m_SpriteMapFileName, c.x, c.y, c.w, c.h);
			/*if (row[i] == 'B')
			{
				sprite->setPosition(0,0);
				GameObject *go = new GameObject(sprite->getPosition(),sprite);
				go->SetPosition(sf::Vector2f(iX,iY));
				go->SetLevelLayer(setLayer);
				m_pxGameObjMgr->Attach(go);

				continue;
			}*/



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
					collider->SetExtention(sf::Vector2f(265*0.2f, 100*0.2f));
					sf::Sprite* tempEnemy = p_pSpriteManager->Load("alpha_enemy_picture_2.png", 0,0, 265*0.2f, 100*0.2f);
					tempEnemy->setOrigin((265*0.2f)/2, (100*0.2f)/2);
					tempEnemy->setPosition(iX, iY);
					EnemyFishObject *enemy = new EnemyFishObject(tempEnemy->getPosition(),tempEnemy,collider);
					enemy->SetPosition(sf::Vector2f(iX, iY) );
					enemy->SetLevelLayer(setLayer);
					m_pxGameObjMgr->Attach(enemy);
					m_CollisionMgr->AttachCollider(collider);

				}
				else
				{
					GameObject *go = new GameObject(sprite->getPosition(),sprite,collider);
					go->SetPosition(sf::Vector2f(iX,iY));
					go->SetLevelLayer(setLayer);
					go->SetType("Brown Brick");
					m_pxGameObjMgr->Attach(go);
					/*m_CollisionMgr->AttachCollider(collider);*/
				}

			}else
			{
				GameObject *go = new GameObject(sprite->getPosition(),sprite);
				go->SetPosition(sf::Vector2f(iX,iY));
				go->SetLevelLayer(setLayer);
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
	UpdateParallax();
	for (int n = 0; n < 3; n++)
	{
		for(auto i=0UL; i < m_pxGameObjMgr->m_apxGameObject.size();i++)
		{	

			if (m_pxGameObjMgr->m_apxGameObject[i]->GetLevelLayer() == n)
			{
				p_draw_manager->Draw(m_pxGameObjMgr->m_apxGameObject[i]->GetSprite());
			}

		}
		if (m_pxGameObjMgr->m_pxPlayer->GetLevelLayer() == n)
		{
			p_draw_manager->Draw(m_pxGameObjMgr->m_pxPlayer->GetSprite() );
		}
			
		/*if (m_pxGameObjMgr->m_pxPlayer != nullptr)
		{
			p_draw_manager->Draw(m_pxGameObjMgr->m_pxPlayer->GetLightSource()->GetLightCircle() );
		}*/

		

	}


	//
}


void Level::UpdateParallax()
{
	int x = 0;
	int y = 0;
	int oldX = -100000;

	for(auto i=0UL; i < m_pxGameObjMgr->m_apxGameObject.size();i++)
	{

		if (m_pxGameObjMgr->m_apxGameObject[i]->GetLevelLayer() == 0)
		{

			if (oldX < m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x)
			{
				oldX = m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x;
				m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f(((m_pxGameObjMgr->m_pxPlayer->GetPosition().x*-0.3)+(x*500)),(m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().y)));
				
				m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x),((m_pxGameObjMgr->m_pxPlayer->GetPosition().y*-0.3)+(y*500))));
				x++;

			}
			else
			{
				x = 0;
				y++;
				oldX = m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x;
				m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f(((m_pxGameObjMgr->m_pxPlayer->GetPosition().x*-0.3)+(x*500)),(m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().y)));
				
				m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x),((m_pxGameObjMgr->m_pxPlayer->GetPosition().y*-0.3)+(y*500))));
				x++;
			}
			
			
		}

	}
	
	/*x = 0;
	y = 0;
	int oldX = 0;

	for(auto i=0UL; i < m_pxGameObjMgr->m_apxGameObject.size();i++)
	{

		if (m_pxGameObjMgr->m_apxGameObject[i]->GetLevelLayer() == 0)
		{

			if (oldX == m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x)
			{
				m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x),((m_pxGameObjMgr->m_pxPlayer->GetPosition().y*-0.3)+(y*500))));
				y++;
			}
			else
			{
				y = 0;
				m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x),((m_pxGameObjMgr->m_pxPlayer->GetPosition().y*-0.3)+(y*500))));
				y++;
			}
			
			oldX = m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x;
		}

	}
*/
}
