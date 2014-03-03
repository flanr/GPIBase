// GameState.cpp

#include "stdafx.h"
#include "GameState.h"
#include "Core.h"
#include "PlayerFishObject.h"
#include "FishObject.h"
#include "DrawManager.h"
#include "Level.h"
#include "GameObjectManager.h"
#include "Camera.h"

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

	// Layers
	m_LevelLayerForGround = nullptr;
	m_LevelLayerMidleGround = nullptr;
	m_LevelLayerBackgroundSecondLowest = nullptr;
	m_LevelLayerBackgroundSecondHighest = nullptr;
	m_LevelLayerGradient = nullptr;
	m_LevelLayerBackgroundLowest = nullptr;

	m_Camera = nullptr;

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

	if (m_LevelLayerBackgroundSecondLowest == nullptr)
	{
		// Lowest
		m_LevelLayerBackgroundLowest = new Level(m_GameObjMgr);
		m_LevelLayerBackgroundLowest->Load("../data/levels/level_backgroundlowest.txt",m_SpriteManager,false, ELayer::LOWESTBG);
		// Second Lowest
		m_LevelLayerBackgroundSecondLowest = new Level(m_GameObjMgr);
		m_LevelLayerBackgroundSecondLowest->Load("../data/levels/level_backgroundsecondlowest.txt", m_SpriteManager, false,ELayer::SECONDLOWESTBG);
		// Background
		m_LevelLayerBackgroundSecondHighest = new Level(m_GameObjMgr);
		m_LevelLayerBackgroundSecondHighest->Load("../data/levels/level_backgroundsecondhighest.txt",m_SpriteManager,false, ELayer::HIGHESTBG);
		// MiddleGround
		m_LevelLayerMidleGround = new Level(m_GameObjMgr, mgr);
		m_LevelLayerMidleGround->Load("../data/levels/level_middleground.txt", m_SpriteManager, true,ELayer::MIDDLEGROUND);
		// ForGround
		m_LevelLayerForGround = new Level(m_GameObjMgr);
		m_LevelLayerForGround->Load("../data/levels/level_forground.txt", m_SpriteManager, false, ELayer::FOREGROUND);
	} 
	//Create Camera
	if(m_GameObjMgr->m_pxPlayer != nullptr)
	{
		//Must be called after Player is created
		m_Camera = new Camera(sf::Vector2f(m_window->getSize() ) );
		m_Camera->SetCameraPosition(m_GameObjMgr->m_pxPlayer->GetPosition() );
		m_Camera->AddLayer();
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
	
	m_Camera->Update(m_GameObjMgr->m_pxPlayer->GetPosition(), m_GameObjMgr->m_pxPlayer->GetLightSource() );

	mgr->RemoveEnemyCollider();
	/*if (mgr->GetPlayerVsEnemy())
	{
		m_GameObjMgr->m_pxPlayer->ExperienceGain(1);
		mgr->RemoveEnemyCollider();
		mgr->SetPlayerVsEnemy(false);
	}*/
	/// Player Experience Stuff
	if (m_GameObjMgr->m_pxPlayer->GetExperience() > 5)
	{
		m_GameObjMgr->m_pxPlayer->SetScale(0.5f);
	}

	UpdateGUI();
	/*int x = m_GameObjMgr->m_pxPlayer->GetPosition().x;
	int y = m_GameObjMgr->m_pxPlayer->GetPosition().y;
	if (x > 2390)
	{
	m_GameObjMgr->m_pxPlayer->SetPosition(sf::Vector2f(2390,m_GameObjMgr->m_pxPlayer->GetPosition().y));
	}
	if (x < 35)
	{
	m_GameObjMgr->m_pxPlayer->SetPosition(sf::Vector2f(35,m_GameObjMgr->m_pxPlayer->GetPosition().y));
	}
	if (y > 1270)
	{
	m_GameObjMgr->m_pxPlayer->SetPosition(sf::Vector2f(m_GameObjMgr->m_pxPlayer->GetPosition().x,1270));
	}
	if (y < 50)
	{
	m_GameObjMgr->m_pxPlayer->SetPosition(sf::Vector2f(m_GameObjMgr->m_pxPlayer->GetPosition().x,50));
	}*/

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
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num0))
	{
		if(m_Camera->GetFilterStatus() == true )
		{
			m_Camera->ToggleFilterOn(false);
		}
		else
		{
			m_Camera->ToggleFilterOn(true);
		}
	}
	//Not working correctly
	//if (m_pInputManager->IsDownOnceK(sf::Keyboard::R))
	//{
	//	m_GameObjMgr->Cleanup();
	//	delete m_LevelLayerBackground;
	//	m_LevelLayerBackground = nullptr;
	//	
	//	delete m_LevelLayerMidleGround; 
	//	m_LevelLayerMidleGround = nullptr;
	//	
	//	delete m_LevelLayerForGround;
	//	m_LevelLayerForGround = nullptr;
	//	m_pCore->m_StateManager.SetState("StartState");
	//}
}

void GameState::Draw()
{
	m_DrawManager->ClearWindow();

	m_window->setView(m_Camera->GetCameraView() );
	m_LevelLayerForGround->Draw(m_DrawManager);

	//Draw if filter is toggled On
	if(m_Camera->GetFilterStatus() == true )
	{
		m_DrawManager->Draw(m_Camera->GetFilterSprite() );
	}

	m_DrawManager->Draw(Gui);
	m_DrawManager->DrawSlider(m_HealthSlider);
	m_DrawManager->DrawSlider(m_EnergySlider);

	m_DrawManager->DisplayWindow();

}

bool GameState::IsType(const string &p_type)
{
	return p_type.compare("GameState") == 0;
}																																										//Sten
