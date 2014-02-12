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

	Gui = m_SpriteManager->Load("gui.png",0,0,361,136);
	m_EnergySlider.SetSlider(0,0,150,25);
	m_HealthSlider.SetSlider(0,0,259,41);

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

	if (m_GameObjMgr == nullptr)
	{
		m_GameObjMgr = new GameObjectManager(m_pInputManager);
		m_GameObjMgr->LoadFish("../data/anim/PlayerAnimIdle.txt", m_SpriteManager, m_window);

	}

	if (m_LevelLayerBackground == nullptr)
	{
		m_LevelLayerBackground = new Level(m_GameObjMgr);
		m_LevelLayerBackground->Load("../data/levels/level_background.txt", m_SpriteManager, false);
		m_LevelLayerMidleGround = new Level(m_GameObjMgr);
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
	HandleInput();
	
	m_GameObjMgr->UpdateAllObjects(p_DeltaTime);
	Gui->setPosition(m_GameObjMgr->m_pxPlayer->GetPosition().x - 500 ,m_GameObjMgr->m_pxPlayer->GetPosition().y - 310 );
	sf::Vector2f GUI_pos = Gui->getPosition();
	m_EnergySlider.SetPosition(GUI_pos.x + 96 ,GUI_pos.y +29);
	m_HealthSlider.SetPosition(GUI_pos.x + 96 ,GUI_pos.y +60);
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
	/*if (m_pInputManager->IsDownK(sf::Keyboard::L))
	{
	m_shape.move(0.01, 0.0f);
	}
	if (m_pInputManager->IsDownK(sf::Keyboard::J))
	{
	m_shape.move(-0.01, 0.0f);
	}
	if (m_pInputManager->IsDownK(sf::Keyboard::I))
	{
	m_shape.move(0.0, -0.01f);
	}
	if (m_pInputManager->IsDownK(sf::Keyboard::K))
	{
	m_shape.move(0.0, 0.01f);
	}


	if (m_pInputManager->IsDownK(sf::Keyboard::Key::A))
	{
	m_shape2.move(-0.01, 0.f);
	}
	if(m_pInputManager->IsDownK(sf::Keyboard::Key::D))
	{
	m_shape2.move(0.01, 0.f);
	}
	if (m_pInputManager->IsDownK(sf::Keyboard::Key::W))
	{
	m_shape2.move(0.0, -0.01f);
	}
	if(m_pInputManager->IsDownK(sf::Keyboard::Key::S))
	{
	m_shape2.move(0.0, 0.01f);
	}

	if(m_pInputManager->IsDownK(sf::Keyboard::Left))
	{
	m_rectShape.move(-0.05, 0.0f);
	}
	if(m_pInputManager->IsDownK(sf::Keyboard::Right))
	{
	m_rectShape.move(0.05, 0.0f);
	}
	if(m_pInputManager->IsDownK(sf::Keyboard::Up))
	{
	m_rectShape.move(0.0, -0.05f);
	}
	if(m_pInputManager->IsDownK(sf::Keyboard::Down))
	{
	m_rectShape.move(0.0, 0.05f);
	}
	if(m_pInputManager->IsDownK(sf::Keyboard::F))
	{
	m_rectShape2.move(-0.05, 0.0f);
	}
	if(m_pInputManager->IsDownK(sf::Keyboard::H))
	{
	m_rectShape2.move(0.05, 0.0f);
	}
	if(m_pInputManager->IsDownK(sf::Keyboard::T))
	{
	m_rectShape2.move(0.0, -0.05f);
	}
	if(m_pInputManager->IsDownK(sf::Keyboard::G))
	{
	m_rectShape2.move(0.0, 0.05f);
	}*/

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

	m_DrawManager->DrawSlider(m_HealthSlider);
	m_DrawManager->DrawSlider(m_EnergySlider);
	m_DrawManager->Draw(Gui);

	//m_level->Draw(m_DrawManager);
	m_DrawManager->DisplayWindow();








}

bool GameState::IsType(const string &p_type)
{
	return p_type.compare("GameState") == 0;
}																																										//Sten
