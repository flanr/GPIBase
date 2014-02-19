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
	m_GameObjMgr = p_pCore->m_GameObjectManager;

	mgr = new CollisionManager;


	m_DrawManager = p_pCore->m_DrawManager;
	m_player = p_pCore->m_player;
	m_LevelLayerBackground = nullptr;
	m_LevelLayerMidleGround = nullptr;
	m_LevelLayerForGround = nullptr;


	bStateRunning = false;

	Gui = m_SpriteManager->Load("gui.png",0,0,361,136);
	m_EnergySlider.SetSlider(0,0,150,25);
	m_HealthSlider.SetSlider(0,0,259,41);
	m_HealthSlider.SetColor(sf::Color::Red);
	m_EnergySlider.SetColor(sf::Color::Yellow);

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

	if (m_LevelLayerBackground == nullptr)
	{
		m_LevelLayerBackground = new Level(m_GameObjMgr);
		m_LevelLayerBackground->Load("../data/levels/level_background.txt", m_SpriteManager, false);
		m_LevelLayerMidleGround = new Level(m_GameObjMgr, mgr);
		m_LevelLayerMidleGround->Load("../data/levels/level_middleground.txt", m_SpriteManager, true);
		m_LevelLayerForGround = new Level(m_GameObjMgr);
		m_LevelLayerForGround->Load("../data/levels/level_forground.txt", m_SpriteManager, false);
	} 
	
	if(m_GameObjMgr->m_pxPlayer != nullptr)
	{
		//Måste anropas efter spelare är inladdad
		m_GameObjMgr->m_pxPlayer->InitPlayerView(sf::Vector2f(m_window->getSize() ) );
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
	/*m_GameObjMgr->m_pxPlayer->SetScale(0.2f);*/


	

	mgr->CheckCollisionRectVsRect();
	m_GameObjMgr->UpdateAllObjects(p_DeltaTime);
	UpdateGUI();
	int x = m_GameObjMgr->m_pxPlayer->GetPosition().x;
	int y = m_GameObjMgr->m_pxPlayer->GetPosition().y;
	if (x > 2000)
	{
		m_GameObjMgr->m_pxPlayer->SetPosition(sf::Vector2f(2000,m_GameObjMgr->m_pxPlayer->GetPosition().y));
	}
	if (x < 0)
	{
		m_GameObjMgr->m_pxPlayer->SetPosition(sf::Vector2f(0,m_GameObjMgr->m_pxPlayer->GetPosition().y));
	}
	if (y > 2000)
	{
		m_GameObjMgr->m_pxPlayer->SetPosition(sf::Vector2f(m_GameObjMgr->m_pxPlayer->GetPosition().x,2000));
	}
	if (y < 0)
	{
		m_GameObjMgr->m_pxPlayer->SetPosition(sf::Vector2f(m_GameObjMgr->m_pxPlayer->GetPosition().y,0));
	}

	return true;
}

void GameState::UpdateGUI()
{
	
	Gui->setPosition(m_GameObjMgr->m_pxPlayer->GetPosition().x - 500 ,m_GameObjMgr->m_pxPlayer->GetPosition().y - 310 );
	sf::Vector2f GUI_pos = Gui->getPosition();
	m_EnergySlider.SetValue(m_GameObjMgr->m_pxPlayer->GetEnergy());
	m_HealthSlider.SetValue(m_GameObjMgr->m_pxPlayer->GetHealth());
	m_EnergySlider.SetPosition(GUI_pos.x + 96 ,GUI_pos.y +29);
	m_HealthSlider.SetPosition(GUI_pos.x + 96 ,GUI_pos.y +60);

	

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
	m_DrawManager->ClearWindow();
	m_window->setView(m_GameObjMgr->m_pxPlayer->GetPlayerView() );
	m_LevelLayerBackground->Draw(m_DrawManager);
	m_LevelLayerMidleGround->Draw(m_DrawManager);
	m_LevelLayerForGround->Draw(m_DrawManager);
	
	m_DrawManager->Draw(Gui);
	m_DrawManager->DrawSlider(m_HealthSlider);
	m_DrawManager->DrawSlider(m_EnergySlider);
	

	m_DrawManager->DisplayWindow();

}

bool GameState::IsType(const string &p_type)
{
	return p_type.compare("GameState") == 0;
}																																										//Sten
