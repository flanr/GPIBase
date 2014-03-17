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
#include "LightSource.h"

using namespace std;
GameState::GameState(Core* p_pCore)
{
	m_pCore = p_pCore;
	m_window = p_pCore->window;
	m_pInputManager = p_pCore->m_pInputManager;
	m_SpriteManager = p_pCore->m_SpriteManager;
	m_GameObjMgr = p_pCore->m_GameObjectManager;

	m_pxCollisionManager = new CollisionManager;


	m_DrawManager = p_pCore->m_DrawManager;
	m_player = p_pCore->m_player;

	// Layers
	m_LevelLayerForGround = nullptr;
	m_LevelLayerMidleGround = nullptr;
	m_LevelLayerBackgroundSecondLowest = nullptr;
	m_LevelLayerBackgroundSecondHighest = nullptr;
	m_LevelLayerMiddleFront = nullptr;
	m_LevelLayerBackgroundLowest = nullptr;

	m_Camera = nullptr;

	bStateRunning = false;

	Gui = m_SpriteManager->Load("newGUI.png",0,0,281,156);
	m_EnergySlider.SetSlider(0,0,154,17);
	m_HealthSlider.SetSlider(0,0,190,28);
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

		int posx = 2000;
		int posy = 2000;
		Collider *collider = new Collider(sf::Vector2f(posx, posy),sf::Vector2f(70, 70) );
		//PlayerObject måste laddas in som nullptr,
		PlayerFishObject *Player = new PlayerFishObject(sf::Vector2f(posx, posy ), nullptr, collider);
		AnimatedSprite *pxAnimSprite = m_SpriteManager->LoadAnim("../data/anim/PlayerAnimStage1.txt");	
		Player->AddAnimation("PlayerStage1", pxAnimSprite);
		Player->SetPosition(sf::Vector2f(posx, posy) );
		Player->SetLevelLayer(MIDDLEGROUND);
		Player->AddLightSource(new LightSource(sf::Vector2f(posx, posy), 240) );
		Player->GetLightSource()->ToggleLightOn(false);

		Player->AddLightSprite(m_SpriteManager->Load("Generic_Light_Yellow_transparent.png", 0,0, 1023, 1023) );
		Player->GetLightSprite()->setOrigin(1023 / 2.0f, 1023 /2.0f);
		Player->GetLightSprite()->setScale(0.3f, 0.3f);

		m_GameObjMgr->AttachPlayer(Player);
		m_pxCollisionManager->AttachCollider(Player->GetCollider() );
		m_GameObjMgr->m_pxPlayer->SetSoundManager(m_pCore->m_SoundManager);

		// MiddleGround
		m_LevelLayerMidleGround = new Level(m_GameObjMgr, m_pxCollisionManager);
		m_LevelLayerMidleGround->Load("../data/levels/level_middleground.txt", m_SpriteManager, true,ELayer::MIDDLEGROUND);

		// Middlefront
		m_LevelLayerMiddleFront = new Level(m_GameObjMgr);
		m_LevelLayerMiddleFront->Load("../data/levels/level_middlefront.txt", m_SpriteManager, false,ELayer::MIDDLEFROUNT);

		// ForGround
		m_LevelLayerForGround = new Level(m_GameObjMgr, m_pxCollisionManager);
		m_LevelLayerForGround->Load("../data/levels/level_forground.txt", m_SpriteManager, false, ELayer::FOREGROUND);
		//Player loads outside of the frame, here it is set to inside of the frame. It fixed collisions somehow *_*
	} 

	//Create Camera
	if(m_GameObjMgr->m_pxPlayer != nullptr)
	{
		if(m_Camera == nullptr)
		{
			//Must be called after Player is created
			m_Camera = new Camera(sf::Vector2f(m_window->getSize() ) );
			m_Camera->Initialize(m_window, m_GameObjMgr->m_pxPlayer->GetPosition() );
			m_Camera->SetZoomStrength(2.0f);
			m_Camera->ZoomOut(m_Camera->GetZoomStrength() );
			m_Camera->SetTotalZoom(m_Camera->GetTotalZoom() * m_Camera->GetZoomStrength() );
			for(int i = 0UL; i < m_GameObjMgr->m_apxGameObject.size(); i++)
			{
				if( !(m_GameObjMgr->m_apxGameObject[i]->GetLevelLayer() == MIDDLEGROUND || m_GameObjMgr->m_apxGameObject[i]->GetLevelLayer() == FOREGROUND) )
				{
					m_GameObjMgr->m_apxGameObject[i]->GetSprite()->setScale(m_GameObjMgr->m_apxGameObject[i]->GetSprite()->getScale() * m_Camera->GetZoomStrength());
				}
			}
			m_Camera->GetFilterSprite()->setScale(m_Camera->GetFilterSprite()->getScale() * m_Camera->GetZoomStrength() );

			m_EnergySlider.m_FullSlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
			m_HealthSlider.m_FullSlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
			m_EnergySlider.m_EmptySlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
			m_HealthSlider.m_EmptySlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
			m_EnergySlider.m_SliderBox.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
			m_HealthSlider.m_SliderBox.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );	
			Gui->setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		}
	}

	return false;
}

void GameState::ExitState()
{
	cout << "GameState::ExitState" << endl;
}

bool GameState::Update(float p_DeltaTime)
{

	if (m_GameObjMgr->GetEnemyCounter() == 0)
	{
		cout<< "YOU WIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	}
	HandleInput();

	if(m_GameObjMgr->m_pxPlayer != nullptr)
	{
		m_GameObjMgr->m_pxPlayer->Update(m_pInputManager, m_SpriteManager, m_Camera, p_DeltaTime);
	}

	
	//m_pxCollisionManager->CheckCollisionRectVsCircle();

	if( m_GameObjMgr->m_pxPlayer->GetState() != Growing )
	{
		m_pxCollisionManager->CheckCollisionRectVsRect();
		m_GameObjMgr->UpdateAllObjects(p_DeltaTime);
	}
	m_Camera->Update(m_GameObjMgr, m_LevelLayerMidleGround );
	UpdateGUI();

	return true;
}

void GameState::UpdateGUI()
{
	if(m_Camera->IsZoomingOut() )
	{
		Gui->setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_EnergySlider.m_FullSlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_HealthSlider.m_FullSlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_EnergySlider.m_EmptySlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_HealthSlider.m_EmptySlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_EnergySlider.m_SliderBox.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_HealthSlider.m_SliderBox.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );		
	}

	Gui->setPosition(m_Camera->GetCameraView().getCenter().x - 
		(m_Camera->GetCameraView().getSize().x / 2.0f) + 
		(50.f * m_Camera->GetTotalZoom() ), m_Camera->GetCameraView().getCenter().y - 
		(m_Camera->GetCameraView().getSize().y / 2.0f) + 
		(50.f * m_Camera->GetTotalZoom() ) );

	sf::Vector2f GUI_pos = Gui->getPosition();
	m_HealthSlider.SetValue(m_GameObjMgr->m_pxPlayer->GetHealth());
	m_HealthSlider.SetPosition(GUI_pos.x + (75 * m_Camera->GetTotalZoom() ) ,GUI_pos.y + (79 * m_Camera->GetTotalZoom() ) );

	if (m_GameObjMgr->m_pxPlayer->GetStageTwo())
	{
		m_EnergySlider.SetColor(sf::Color::Yellow);
		m_EnergySlider.SetValue(m_GameObjMgr->m_pxPlayer->GetEnergy());
		m_EnergySlider.SetPosition(GUI_pos.x + (75 * m_Camera->GetTotalZoom() ) ,GUI_pos.y + (55 * m_Camera->GetTotalZoom() ) );
	} else
	{
		m_GameObjMgr->m_pxPlayer->SetEnergy(100);
		
		m_EnergySlider.SetValue(m_GameObjMgr->m_pxPlayer->GetEnergy());
		m_EnergySlider.SetColor(sf::Color::White);
		
		m_EnergySlider.SetPosition(GUI_pos.x + (75 * m_Camera->GetTotalZoom() ) ,GUI_pos.y + (55 * m_Camera->GetTotalZoom() ) );
	}



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
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num4))
	{
		m_pCore->m_StateManager.SetState("EndState");
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
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num9))
	{
		m_Camera->ZoomStart(m_window->getDefaultView() );
	}
	if (m_pInputManager->IsDownK(sf::Keyboard::Num8))
	{

		m_Camera->SetZoomStrength(1.005f);
		m_Camera->ZoomOut(m_Camera->GetZoomStrength() );
	}

}

void GameState::Draw()
{
	m_DrawManager->ClearWindow();

	m_window->setView(m_Camera->GetCameraView() );
	m_LevelLayerForGround->Draw(m_DrawManager, m_Camera);

	//Draw if filter is toggled On
	if(m_Camera->GetFilterStatus()  )
	{
		m_DrawManager->Draw(m_Camera->GetFilterSprite() );
	}


	m_DrawManager->DrawSlider(m_HealthSlider);
	m_DrawManager->DrawSlider(m_EnergySlider);
	m_DrawManager->Draw(Gui);
	//m_DrawManager->DrawRect(m_GameObjMgr->m_pxPlayer->GetCollider()->PlayerRect() );
	m_DrawManager->DisplayWindow();
}

bool GameState::IsType(const string &p_type)
{
	return p_type.compare("GameState") == 0;
}																																										//Sten


void GameState::TutorialWASD()
{

}

void GameState::TutorialSpace()
{

}
void GameState::TutorialF()
{

}
