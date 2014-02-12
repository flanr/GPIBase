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
	m_SpriteManager = p_pCore->m_SpriteManager;

	mgr = new CollisionManager;
	

	

	m_DrawManager = p_pCore->m_DrawManager;
	m_player = p_pCore->m_player;
	m_LevelLayerBackground = nullptr;
	m_LevelLayerMidleGround = nullptr;
	m_LevelLayerForGround = nullptr;
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

	m_GameObjMgr = new GameObjectManager(m_pInputManager);
	m_GameObjMgr->LoadFish("../data/anim/PlayerAnimIdle.txt", m_SpriteManager, m_window);
	mgr->AttachCollider(m_GameObjMgr->m_pxPlayer->GetCollider() );

	if (m_LevelLayerBackground == nullptr)
	{
		m_LevelLayerBackground = new Level(m_GameObjMgr);
		m_LevelLayerBackground->Load("../data/levels/level_background.txt", m_SpriteManager, false);
		m_LevelLayerMidleGround = new Level(m_GameObjMgr, mgr);
		m_LevelLayerMidleGround->Load("../data/levels/level_middleground.txt", m_SpriteManager, true);
		m_LevelLayerForGround = new Level(m_GameObjMgr);
		m_LevelLayerForGround->Load("../data/levels/level_forground.txt", m_SpriteManager, false);
	} 
	
	return false;
}

void GameState::ExitState()
{
	cout << "GameState::ExitState" << endl;
}

bool GameState::Update(float p_DeltaTime)
{


	//Draw();
	HandleInput();
	mgr->CheckCollisionRectVsRect();
	m_GameObjMgr->UpdateAllObjects(p_DeltaTime);
	
	
	


	//mgr->CheckCollisionRectVsRect();
	
	

	//mgr->CheckCollisionCircleVsCircle();
	
	//Just until I come to think about something else sf::FloatRect
//	mgr->CheckCollisionRectVsCircle(m_floatrect);


//	HandleInput();
	


	return true;
}

void GameState::HandleInput()
{
	if(m_pInputManager->IsDownOnceK(sf::Keyboard::Num1))
	{
		m_pCore->m_StateManager.SetState("StartState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num2))
	{
		cout << " You are already in GameState" << endl;
		//m_pCore->m_StateManager.SetState("GameState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num3))
	{
		m_pCore->m_StateManager.SetState("OptionState");
	}
	
	
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
	m_window->setView(m_GameObjMgr->m_pxPlayer->GetPlayerView() );
	m_LevelLayerBackground->Draw(m_DrawManager);
	m_LevelLayerMidleGround->Draw(m_DrawManager);
	m_LevelLayerForGround->Draw(m_DrawManager);
	
	//m_level->Draw(m_DrawManager);
	m_DrawManager->DisplayWindow();







}

bool GameState::IsType(const string &p_type)
{
	return p_type.compare("GameState") == 0;
}																																										//Sten
