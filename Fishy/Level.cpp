// Level.cpp

#include "stdafx.h"
#include "Level.h"
#include "DrawManager.h"
#include "Collider.h"
#include "AnimatedSprite.h"
#include "PlayerFishObject.h"
#include "EnemyFishObject.h"
#include "PowerupObject.h"
#include "GameObjectManager.h"
#include "LightSource.h"
#include "Camera.h"


Level::Level(GameObjectManager *p_pxGameObjMgr, CollisionManager * p_CollisionMgr)
{
	m_iHeight = 0;
	m_iWidth = 0;
	m_LevelWidth = 0;
	m_LevelHeight = 0;
	m_PlayerStartPosition = sf::Vector2f(0.0f, 0.0f);
	m_pxGameObjMgr = p_pxGameObjMgr;
	m_CollisionMgr = p_CollisionMgr;
}

Level::~Level()
{
}


bool Level::Load(const string &p_sFileName, SpriteManager *p_pSpriteManager, bool p_collider, ELayer layer)
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
					m_pxGameObjMgr->m_pxPlayer->SetPosition(sf::Vector2f(iX,iY));
					iX += m_iWidth;
					continue;
				}
			}



			/*if (row[i] == 'B')
			{
			sprite->setPosition(0,0);
			GameObject *go = new GameObject(sprite->getPosition(),sprite);
			go->SetPosition(sf::Vector2f(iX,iY));
			go->SetLevelLayer(setLayer);
			m_pxGameObjMgr->Attach(go);

			continue;
			}*/
			if (row[i] == 'e')
			{
				sf::Sprite * sprite = p_pSpriteManager->Load("interactive_light_boxsize_400x209.png", 0,0, 400, 209);
				sprite->setPosition(iX,iY);

				GameObject *go = new GameObject(sprite->getPosition(),sprite);
				go->SetPosition(sf::Vector2f(iX-158,iY-40));
				go->SetLevelLayer(MIDDLEGROUND);
				go->AddLightSource(new LightSource(sf::Vector2f(iX, iY), 240) );
				go->GetLightSource()->SetRadius(480);
				go->AddLightSprite(p_pSpriteManager->Load("Generic_Light_Yellow_transparent.png", 0,0, 1023, 1023) );
				go->GetLightSprite()->setOrigin(1023 / 2.0f, 1023 /2.0f);
				go->GetLightSprite()->setScale(0.3f, 0.3f);
				go->SetLightPosition(sf::Vector2f(iX + 222, iY + 142));
				go->GetLightSource()->ToggleLightOn(false);
				go->SetType("InteractiveLight");
				m_pxGameObjMgr->Attach(go);

				iX += m_iWidth;
				continue;
			}
			if (row[i] == 'f')
			{
				sf::Sprite * sprite = p_pSpriteManager->Load("interactive_light_boxsize_400x209.png", 0,209, 400, 209);
				sprite->setPosition(iX,iY);

				GameObject *go = new GameObject(sprite->getPosition(),sprite);
				go->SetPosition(sf::Vector2f(iX-242,iY-58));
				go->SetLevelLayer(MIDDLEGROUND);
				go->AddLightSource(new LightSource(sf::Vector2f(iX, iY), 240) );
				go->GetLightSource()->SetRadius(480);
				go->AddLightSprite(p_pSpriteManager->Load("Generic_Light_Yellow_transparent.png", 0,0, 1023, 1023) );
				go->GetLightSprite()->setOrigin(1023 / 2.0f, 1023 /2.0f);
				go->GetLightSprite()->setScale(0.3f, 0.3f);
				go->SetLightPosition(sf::Vector2f(iX - 222, iY +124));
				go->GetLightSource()->ToggleLightOn(false);
				go->SetType("InteractiveLight");
				m_pxGameObjMgr->Attach(go);

				iX += m_iWidth;
				continue;
			}
			if (row[i] == 'g')
			{
				sf::Sprite * sprite = p_pSpriteManager->Load("interactive_light_boxsize_400x209.png", 0, 418, 400, 209);
				sprite->setPosition(iX,iY);

				GameObject *go = new GameObject(sprite->getPosition(),sprite);
				go->SetPosition(sf::Vector2f(iX-205,iY-158));
				go->SetLevelLayer(MIDDLEGROUND);
				go->AddLightSource(new LightSource(sf::Vector2f(iX, iY), 240) );
				go->GetLightSource()->SetRadius(480);
				go->AddLightSprite(p_pSpriteManager->Load("Generic_Light_Yellow_transparent.png", 0,0, 1023, 1023) );
				go->GetLightSprite()->setOrigin(1023 / 2.0f, 1023 /2.0f);
				go->GetLightSprite()->setScale(0.3f, 0.3f);
				go->SetLightPosition(sf::Vector2f(iX - 8, iY));
				go->GetLightSource()->ToggleLightOn(false);
				go->SetType("InteractiveLight");
				m_pxGameObjMgr->Attach(go);

				iX += m_iWidth;
				continue;
			}
			if (row[i] == 'h')
			{
				sf::Sprite * sprite = p_pSpriteManager->Load("interactive_light_boxsize_400x209.png", 0, 627, 400, 209);
				sprite->setPosition(iX,iY);

				GameObject *go = new GameObject(sprite->getPosition(),sprite);
				go->SetPosition(sf::Vector2f(iX-180,iY-50));
				go->SetLevelLayer(MIDDLEGROUND);
				go->AddLightSource(new LightSource(sf::Vector2f(iX, iY), 240) );
				go->GetLightSource()->SetRadius(480);
				go->AddLightSprite(p_pSpriteManager->Load("Generic_Light_Yellow_transparent.png", 0,0, 1023, 1023) );
				go->GetLightSprite()->setOrigin(1023 / 2.0f, 1023 /2.0f);
				go->GetLightSprite()->setScale(0.3f, 0.3f);
				go->SetLightPosition(sf::Vector2f(iX + 8, iY));
				go->GetLightSource()->ToggleLightOn(false);
				go->SetType("InteractiveLight");
				m_pxGameObjMgr->Attach(go);

				iX += m_iWidth;
				continue;
			}
			if (row[i] == 'l')
			{
				Collider *collider = new Collider(sf::Vector2f(iX,iY), sf::Vector2f(494, 490) );

				sf::Sprite * sprite = p_pSpriteManager->Load("Sprite_powerup_light.png", 0,0, 494, 490);
				sprite->setOrigin(494 / 2.0f, 490 / 2.0f);
				sprite->setScale(0.3f, 0.3f);
				collider->SetExtention(sf::Vector2f(sprite->getGlobalBounds().width *0.5f , sprite->getGlobalBounds().height *0.5f ) );
				sprite->setPosition(iX,iY);

				PowerupObject *go = new PowerupObject( LIGHT,sprite->getPosition(),sprite ,collider);
				go->SetType("Powerup");
				go->SetPosition(sf::Vector2f(iX,iY));
				go->SetLevelLayer(MIDDLEGROUND);
				m_pxGameObjMgr->Attach(go);
				m_CollisionMgr->AttachCollider(collider);

				iX += m_iWidth;
				continue;
			}
			if (row[i] == 'p')
			{
				Collider *collider = new Collider(sf::Vector2f(iX,iY), sf::Vector2f(494, 490) );

				sf::Sprite * sprite = p_pSpriteManager->Load("PowerUp_Energy.png", 0,0, 494, 490);
				sprite->setOrigin(494 / 2.0f, 490 / 2.0f);
				sprite->setScale(0.3f, 0.3f);
				collider->SetExtention(sf::Vector2f(sprite->getGlobalBounds().width *0.5f , sprite->getGlobalBounds().height *0.5f ) );
				sprite->setPosition(iX,iY);

				PowerupObject *go = new PowerupObject( ENERGY,sprite->getPosition(),sprite ,collider);
				go->SetType("Powerup");
				go->SetPosition(sf::Vector2f(iX,iY));
				go->SetLevelLayer(MIDDLEGROUND);
				m_pxGameObjMgr->Attach(go);
				m_CollisionMgr->AttachCollider(collider);

				iX += m_iWidth;
				continue;
			}
			if (row[i] == 'q')
			{
				Collider *collider = new Collider(sf::Vector2f(iX,iY), sf::Vector2f(494, 490) );

				sf::Sprite * sprite = p_pSpriteManager->Load("PowerUp_Speed.png", 0,0, 494, 490);
				sprite->setOrigin(494 / 2.0f, 490 / 2.0f);
				sprite->setScale(0.3f, 0.3f);
				collider->SetExtention(sf::Vector2f(sprite->getGlobalBounds().width *0.5f , sprite->getGlobalBounds().height *0.5f ) );
				sprite->setPosition(iX,iY);

				PowerupObject *go = new PowerupObject( SPEED,sprite->getPosition(),sprite ,collider);
				go->SetType("Powerup");
				go->SetPosition(sf::Vector2f(iX,iY));
				go->SetLevelLayer(MIDDLEGROUND);
				m_pxGameObjMgr->Attach(go);
				m_CollisionMgr->AttachCollider(collider);

				iX += m_iWidth;
				continue;
			}
			if (row[i] == 'r')
			{
				Collider *collider = new Collider(sf::Vector2f(iX,iY), sf::Vector2f(256, 256) );

				sf::Sprite * sprite = p_pSpriteManager->Load("powerup_rod.png", 0,0, 256, 256);
				sprite->setOrigin(256 / 2.0f, 256 / 2.0f);
				sprite->setPosition(iX,iY);

				PowerupObject *go = new PowerupObject( ROD,sprite->getPosition(),sprite ,collider);
				go->SetType("Powerup");
				go->SetPosition(sf::Vector2f(iX,iY));
				go->SetLevelLayer(MIDDLEGROUND);
				m_pxGameObjMgr->Attach(go);
				m_CollisionMgr->AttachCollider(collider);

				iX += m_iWidth;
				continue;


			}

			if (row[i] == 'z')
			{
				sf::Sprite * sprite = p_pSpriteManager->Load("plant2.png", 0,0, 676, 632);
				sprite->setPosition(iX,iY);

				GameObject *go = new GameObject(sprite->getPosition(),sprite);
				go->SetPosition(sf::Vector2f(iX-350,iY-260));
				go->SetLevelLayer(layer);
				m_pxGameObjMgr->Attach(go);

				iX += m_iWidth;
				continue;


			}
			if (row[i] == 'x')
			{
				sf::Sprite *sprite = p_pSpriteManager->Load("plant3.png", 0,0, 540, 840);
				sprite->setPosition(iX,iY);

				GameObject *go = new GameObject(sprite->getPosition(),sprite);
				go->SetPosition(sf::Vector2f(iX-300,iY-530));
				go->SetLevelLayer(layer);
				m_pxGameObjMgr->Attach(go);


				iX += m_iWidth;
				continue;


			}
			if (row[i] == 'v')
			{
				sf::Sprite *sprite = p_pSpriteManager->Load("human_prop_3.png", 0,0, 397, 390);
				sprite->setPosition(iX,iY);

				GameObject *go = new GameObject(sprite->getPosition(),sprite);
				go->SetPosition(sf::Vector2f(iX-200,iY-200));
				go->SetLevelLayer(layer);
				m_pxGameObjMgr->Attach(go);


				iX += m_iWidth;
				continue;


			}



			if (p_collider || layer == FOREGROUND)
			{

				// Collider
				Collider *collider = new Collider;
				collider->SetPosition(sf::Vector2f(iX,iY) );
				collider->SetExtention(sf::Vector2f(c.w, c.h));

				float Random_Size = 0.0f;

				if (row[i] == 'E')
				{

					if (Random(1, 10) < 3)
					{
						if (iY > 0 && iY < 4600)
						{
							Random_Size = Random(.6 , .8);
						}
						if (iY > 4600 && iY < 11500)
						{
							Random_Size = Random(.8, 1.6f);
						}
						//collider->SetExtention(sf::Vector2f(301, 142));
						//sf::Sprite* tempEnemy = p_pSpriteManager->Load("enemy_spritesheet2.png", 76,38, 301, 142);
						//tempEnemy->setOrigin((301)/2, (142)/2);
						//tempEnemy->setPosition(iX, iY);
						//EnemyFishObject *enemy = new EnemyFishObject(sf::Vector2f(iX, iY ),tempEnemy,collider);
						//enemy->SetLevelLayer(MIDDLEGROUND);
						//enemy->SetScale(Random_Size);
						////enemy->AddLightSource(new LightSource(sf::Vector2f(iX, iY), 240) );
						//enemy->SetSubType("Stage2");
						//enemy->SetSpeed(100);
						//enemy->SetSubTypeSize(Random_Size);
						//m_pxGameObjMgr->Attach(enemy);
						//m_CollisionMgr->AttachCollider(collider);
						collider->SetExtention(sf::Vector2f(295, 140));
						EnemyFishObject *enemy = new EnemyFishObject(sf::Vector2f(iX, iY ),nullptr,collider);
						AnimatedSprite *pxAnimSprite = p_pSpriteManager->LoadAnim("../data/anim/EnemyGreenAnim.txt");	
						enemy->AddAnimation("EnemyNormal", pxAnimSprite);
						enemy->SetLevelLayer(MIDDLEGROUND);
						enemy->SetScale(Random_Size);
						enemy->SetPosition(sf::Vector2f(iX, iY) );
						enemy->SetSubType("Stage2");
						enemy->SetSpeed(100);
						enemy->SetSubTypeSize(Random_Size);
						m_pxGameObjMgr->Attach(enemy);
						m_CollisionMgr->AttachCollider(collider);
					}
					else
					{

						if (iY > 0 && iY < 4600)
						{
							Random_Size = Random(.1 , .4);
						}
						if (iY > 4600 && iY < 11500)
						{
							Random_Size = Random(.5, .8);
						}


						collider->SetExtention(sf::Vector2f(265, 100));
						sf::Sprite* tempEnemy = p_pSpriteManager->Load("enemy_tmp.png", 0,0, 265, 100);
						tempEnemy->setOrigin((265)/2, (100)/2);
						tempEnemy->setPosition(iX, iY);
						EnemyFishObject *enemy = new EnemyFishObject(sf::Vector2f(iX, iY ),tempEnemy,collider);
						enemy->SetLevelLayer(MIDDLEGROUND);
						enemy->SetScale(Random_Size);
						//enemy->AddLightSource(new LightSource(sf::Vector2f(iX, iY), 240) );
						enemy->SetSubType("Stage1");
						m_pxGameObjMgr->Attach(enemy);
						m_CollisionMgr->AttachCollider(collider);
					}
				}
				else
				{
					sf::Sprite *sprite = p_pSpriteManager->Load(m_SpriteMapFileName, c.x, c.y, c.w, c.h);
					sprite->setOrigin(sprite->getTextureRect().width / 2.0f, sprite->getTextureRect().height / 2.0f);
					sprite->setPosition(iX,iY);

					GameObject *go = new GameObject(sf::Vector2f(iX, iY),sprite,collider);
					go->SetType("BrownBrick");
					go->SetLevelLayer(layer);
					m_pxGameObjMgr->Attach(go);
					m_CollisionMgr->AttachCollider(collider);
				}

			}else
			{
				sf::Sprite *sprite = p_pSpriteManager->Load(m_SpriteMapFileName, c.x, c.y, c.w, c.h);
				sprite->setOrigin(sprite->getTextureRect().width / 2.0f, sprite->getTextureRect().height / 2.0f);
				sprite->setPosition(iX,iY);

				GameObject *go = new GameObject(sf::Vector2f(iX,iY), sprite);
				go->SetLevelLayer(layer);
				m_pxGameObjMgr->Attach(go);
			}

			iX += m_iWidth;


		}
		iY += m_iHeight;
		if(m_LevelWidth <= iX)
		{
			m_LevelWidth = iX;
		}
		if(m_LevelHeight <= iY)
		{
			m_LevelHeight = iY;
		}
	}
	stream.close();
	//m_LevelWidth += m_iWidth;
	return true;
}

void Level::Draw(DrawManager *p_draw_manager, Camera *p_Camera)
{
	UpdateParallax(p_Camera);
	for (int n = 0; n < 6; n++)
	{
		for(auto i=0UL; i < m_pxGameObjMgr->m_apxGameObject.size();i++)
		{	
			if(m_pxGameObjMgr->m_apxGameObject[i]->GetActive() )
			{
				if (m_pxGameObjMgr->m_apxGameObject[i]->GetLevelLayer() == n)
				{
					p_draw_manager->Draw(m_pxGameObjMgr->m_apxGameObject[i]->GetSprite());

					//Draw light if object has a light
					if(m_pxGameObjMgr->m_apxGameObject[i]->HasLight() )
					{
						//Draw light if its toggled on
						if(m_pxGameObjMgr->m_apxGameObject[i]->GetLightSource()->GetLightStatus())
						{
							if(m_pxGameObjMgr->m_apxGameObject[i]->GetLightSprite() != nullptr)
							{
								p_draw_manager->Draw(m_pxGameObjMgr->m_apxGameObject[i]->GetLightSprite() );
							}
						}
					}
				}
			}

		}
		if (m_pxGameObjMgr->m_pxPlayer->GetLevelLayer() == n)
		{
			p_draw_manager->Draw(m_pxGameObjMgr->m_pxPlayer->GetSprite() );
			//Draw light if Player has a light
			if(m_pxGameObjMgr->m_pxPlayer->HasLight() )
			{
				//Draw light if its toggled on
				if(m_pxGameObjMgr->m_pxPlayer->GetLightSource()->GetLightStatus() )
				{
					if(m_pxGameObjMgr->m_pxPlayer->GetLightSprite() != nullptr)
					{
						p_draw_manager->Draw(m_pxGameObjMgr->m_pxPlayer->GetLightSprite() );
					}
				}
			}
		}

		/*if (m_pxGameObjMgr->m_pxPlayer != nullptr)
		{
		p_draw_manager->Draw(m_pxGameObjMgr->m_pxPlayer->GetLightSource()->GetLightCircle() );
		}*/



	}


	//
}


void Level::UpdateParallax(Camera *p_Camera)
{
	int x = 0;
	int y = 0;
	int oldX = -10000000;

	for(auto i=0UL; i < m_pxGameObjMgr->m_apxGameObject.size();i++)
	{
		if (m_pxGameObjMgr->m_apxGameObject[i]->GetLevelLayer() == 0  ) // Background Fixed
		{

			if (oldX < m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x)
			{
				oldX = m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x;

				// X Axis
				if(p_Camera->IsMovementXAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f(m_pxGameObjMgr->m_pxPlayer->GetPosition().x,(m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().y)));
				}
				// Y Axis
				if(p_Camera->IsMovementYAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x),m_pxGameObjMgr->m_pxPlayer->GetPosition().y));
				}
				x++;

			}
			else
			{
				x = 0;
				y++;
				oldX = m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x;

				// X Axis
				if(p_Camera->IsMovementXAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f(m_pxGameObjMgr->m_pxPlayer->GetPosition().x,(m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().y)));
				}
				// Y Axis
				if(p_Camera->IsMovementYAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x),m_pxGameObjMgr->m_pxPlayer->GetPosition().y));
				}
				x++;
			}


		} else if (m_pxGameObjMgr->m_apxGameObject[i]->GetLevelLayer() == 1) // SecondLowestLayer
		{

			if (oldX < m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x)
			{
				oldX = m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x;

				// X Axis
				if(p_Camera->IsMovementXAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_pxPlayer->GetPosition().x + ((-1 * m_pxGameObjMgr->m_pxPlayer->GetPosition().x) / 5 ) + (x* m_pxGameObjMgr->m_apxGameObject[i]->GetSprite()->getGlobalBounds().width -1000)),(m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().y)));
				}
				// Y Axis
				if(p_Camera->IsMovementYAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x),m_pxGameObjMgr->m_pxPlayer->GetPosition().y + ((-1 * m_pxGameObjMgr->m_pxPlayer->GetPosition().y) / 10 ) + 300 ));
				}
				x++;

			}
			else
			{
				x = 0;
				y++;
				oldX = m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x;

				// X Axis
				if(p_Camera->IsMovementXAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_pxPlayer->GetPosition().x + ((-1 *m_pxGameObjMgr->m_pxPlayer->GetPosition().x) / 5 ) + (x * m_pxGameObjMgr->m_apxGameObject[i]->GetSprite()->getGlobalBounds().width - 1000)),(m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().y)));
				}
				// Y Axis
				if(p_Camera->IsMovementYAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x),m_pxGameObjMgr->m_pxPlayer->GetPosition().y + ((-1 * m_pxGameObjMgr->m_pxPlayer->GetPosition().y) / 10 ) +300 ));
				}
				x++;
			}


		} else if (m_pxGameObjMgr->m_apxGameObject[i]->GetLevelLayer() == 2) // HighestLayer
		{

			if (oldX < m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x)
			{
				oldX = m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x;

				// X Axis
				if(p_Camera->IsMovementXAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_pxPlayer->GetPosition().x + ((-1 *m_pxGameObjMgr->m_pxPlayer->GetPosition().x) / 3 ) + (x* m_pxGameObjMgr->m_apxGameObject[i]->GetSprite()->getGlobalBounds().width - 1000)),(m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().y)));
				}
				// Y Axis
				if(p_Camera->IsMovementYAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x),m_pxGameObjMgr->m_pxPlayer->GetPosition().y + ((-1 * m_pxGameObjMgr->m_pxPlayer->GetPosition().y) / 6 ) +500 ));
				}
				x++;

			}
			else
			{
				x = 0;
				y++;
				oldX = m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x;

				// X Axis
				if(p_Camera->IsMovementXAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_pxPlayer->GetPosition().x + ((-1 *m_pxGameObjMgr->m_pxPlayer->GetPosition().x) / 3 ) + (x* m_pxGameObjMgr->m_apxGameObject[i]->GetSprite()->getGlobalBounds().width - 1000)),(m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().y)));
				}
				// Y Axis
				if(p_Camera->IsMovementYAxis() )
				{
					m_pxGameObjMgr->m_apxGameObject[i]->SetPosition(sf::Vector2f((m_pxGameObjMgr->m_apxGameObject[i]->GetPosition().x),m_pxGameObjMgr->m_pxPlayer->GetPosition().y + ((-1 * m_pxGameObjMgr->m_pxPlayer->GetPosition().y) / 6 ) +500 ));
				}
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

unsigned int Level::GetWidth()
{
	return m_LevelWidth;
}

unsigned int Level::GetHeight()
{
	return m_LevelHeight;
}
float Level::Random(float min, float max)
{
	/*float slump;
	slump=rand()%(int)max+(min);
	return slump;*/
	return((max-min)*((float)rand()/RAND_MAX))+min;
}