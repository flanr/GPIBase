// GameState.cpp

#include "stdafx.h"
#include "GameState.h"
#include "Core.h"
#include "PlayerFishObject.h"
#include "FishObject.h"
#include "DrawManager.h"
#include "Level.h"
#include "GameObjectManager.h"

using namespace std;
GameState::GameState(Core* p_pCore)
{
	m_pCore = p_pCore;
	m_window = p_pCore->window;
	m_pInputManager = p_pCore->m_pInputManager;
	m_DrawManager = p_pCore->m_DrawManager;
	m_player = p_pCore->m_player;
	m_spritemanager = nullptr;
	m_level = nullptr;
	m_GameObjMgr = nullptr;

	bStateRunning = false;
}

string GameState::GetCurrentState()
{
	return m_sCurrentState;
}

string GameState::Next()
{
	return "OptionState";
}


bool GameState::EnterState() 
{
	m_sCurrentState = "GameState";
	cout << "Gamestate::EnterState" << endl;


	if (m_spritemanager == nullptr)
	{
		m_spritemanager = new SpriteManager(m_DrawManager);
		if(!m_spritemanager ->Initialize("../data/sprites/"))
		{
			return false;
		}
	}
	m_GameObjMgr = new GameObjectManager(m_spritemanager);

	if (m_level == nullptr)
	{

		m_level = new Level(m_GameObjMgr);
		m_level->Load("../data/levels/level.txt", m_spritemanager, true);
		m_level->LoadFish("../data/anim/PlayerAnimIdle.txt", m_spritemanager);

	}

	return false;
}

void GameState::ExitState()
{
	cout << "GameState::ExitState" << endl;
}

bool GameState::Update(float p_DeltaTime)
{
	
	HandleInput();
	m_GameObjMgr->UpdateAllObjects(p_DeltaTime);

	return true;
}

void GameState::HandleInput()
{
	m_pInputManager->UpdateEvents(m_pCore);
}

void GameState::Draw()
{
	/*
	sf::Texture	texture;
	if (!texture.loadFromFile("player.png"))
	{
	};
	texture.setSmooth(true);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	*/
	m_DrawManager->ClearWindow();
	m_level->Draw(m_DrawManager);
	m_DrawManager->DisplayWindow();

	/*sf::CircleShape shape(30.0f);
	m_pWindow->clear(sf::Color(0x11,0x22,0x33,0xff));
	m_pWindow->draw(shape);*/
}

bool GameState::IsType(const string &p_type)
{
	return p_type.compare("GameState") == 0;
}																																										//Sten