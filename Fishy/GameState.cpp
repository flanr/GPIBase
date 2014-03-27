// GameState.cpp

#include "stdafx.h"
#include "GameState.h"
#include "Core.h"
#include "PlayerFishObject.h"
#include "FishObject.h"
#include "EnemyFishObject.h"
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
	m_SoundManager = p_pCore->m_SoundManager;

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
	m_Paused = false;
	m_TutorialSPACE = false;
	m_TutorialF = false;
	m_TutorialFPressed = false;
	m_TutorialWASD = false;

	m_Camera = nullptr;

	bStateRunning = false;
	Gui = nullptr;


	m_GuiPower = m_SpriteManager->Loadnonpointer("newGUI.png",0,468,281,156);

	m_GuiEnergy = m_SpriteManager->Loadnonpointer("newGUI.png",0,312,281,156);

	m_GuiSpeed = m_SpriteManager->Loadnonpointer("newGUI.png",0,156,281,156);


	//// OPTIONS /////
	m_BackGroundImg = m_SpriteManager->Load("background2.jpg",0,0,1280,720);
	m_BackGroundImg->setPosition(0,0);
	// OptionBackground
	m_OptionBackground = m_SpriteManager->Load("ingame_options_background.png",0,0,851,609);
	m_OptionBackground->setPosition(0,0);

	////////////////
	//  Buttons   //
	////////////////

	// Mute Music
	m_ButtonMusicMute.SetSpriteRect(m_SpriteManager->Load("mute.png",0,0,85,57));
	m_ButtonMusicMutePos = sf::Vector2f(m_OptionBackground->getPosition().x + 701,m_OptionBackground->getPosition().y + 176 );
	m_ButtonMusicMute.SetPosition(m_ButtonMusicMutePos.x, m_ButtonMusicMutePos.y);
	// Mute Sound  
	m_ButtonSoundMute.SetSpriteRect(m_SpriteManager->Load("mute.png",0,0,85,57));
	m_ButtonSoundMutePos = sf::Vector2f(m_OptionBackground->getPosition().x + 701,m_OptionBackground->getPosition().y + 283);
	m_ButtonSoundMute.SetPosition(m_ButtonSoundMutePos.x,m_ButtonSoundMutePos.y);
	// Fullscreen
	m_ButtonFullScreen.SetSpriteRect(m_SpriteManager->Load("fullscreen.png",0,0,244,57));
	m_ButtonFullScreenPos = sf::Vector2f(m_OptionBackground->getPosition().x + 98,m_OptionBackground->getPosition().y + 389);
	m_ButtonFullScreen.SetPosition(m_ButtonFullScreenPos.x,m_ButtonFullScreenPos.y);
	// Windowed
	m_ButtonWindowed.SetSpriteRect(m_SpriteManager->Load("windowed.png",0,0,244,57));
	m_ButtonWindowedPos = sf::Vector2f(m_OptionBackground->getPosition().x + 364,m_OptionBackground->getPosition().y + 389);
	m_ButtonWindowed.SetPosition(m_ButtonWindowedPos.x,m_ButtonWindowedPos.y);
	// Return
	m_ButtonReturn.SetSpriteRect(m_SpriteManager->Load("backarrow.png",0,0,85,58));
	m_ButtonReturnPos = sf::Vector2f(m_OptionBackground->getPosition().x + 364 ,m_OptionBackground->getPosition().y + 481);
	m_ButtonReturn.SetPosition(m_ButtonReturnPos.x,m_ButtonReturnPos.y);
	// Play
	m_ButtonPlay.SetSpriteRect(m_SpriteManager->Load("Play_options_sprite.png",0,0,85,58));
	m_ButtonPlayPos = sf::Vector2f(m_OptionBackground->getPosition().x , m_OptionBackground->getPosition().y );
	m_ButtonPlay.SetPosition(m_ButtonPlayPos.x,m_ButtonPlayPos.y);
	// Exit
	m_ButtonExit.SetSpriteRect(m_SpriteManager->Load("exit_options_sprite.png",0,0,85,58));
	m_ButtonExitPos = sf::Vector2f(m_OptionBackground->getPosition().x , m_OptionBackground->getPosition().y );


	m_ButtonClick = -1;

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
	if(Gui == nullptr)
	{
		Gui = m_SpriteManager->Load("newGUI.png",0,0,281,156);
		m_EnergySlider.SetSlider(0,0,154,17);
		m_HealthSlider.SetSlider(0,0,190,28);
		m_HealthSlider.SetColor(sf::Color::Red);
		m_EnergySlider.SetColor(sf::Color::Yellow);
	}

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

		/*GlowTexture1 = new sf::Texture;
		GlowTexture1->loadFromFile("../data/sprites/enemy2_finalglowsheet.png", sf::IntRect(0,0,2279,1015));*/

		m_SpriteManager->LoadImage("enemy2_finalglowsheet.png");
		m_SpriteManager->LoadImage("enemy1_finalglowsheet.png");
		m_SpriteManager->LoadImage("enemy3_finalglowsheet.png");
		

		/*GlowTexture2 = new sf::Texture;
		GlowTexture2->loadFromFile("../data/sprites/enemy_spritesheet_glow.png", sf::IntRect(0,0,2279,1015));

		GlowTexture3 = new sf::Texture;
		GlowTexture3->loadFromFile("../data/sprites/enemy3_finalglowsheet.png", sf::IntRect(0,0,2279,1015));*/



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
			m_GuiEnergy.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
			m_GuiPower.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
			m_GuiSpeed.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
			Gui->setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		}
	}
	m_TutorialWASD = true;
	m_SliderMusicVol.SetValue(m_SliderMusicVol.GetValue());
	m_SliderSoundVol.SetValue(m_SliderSoundVol.GetValue());


	//m_ButtonMusicMutePos = sf::Vector2f(m_OptionBackground->getPosition().x + 701,m_OptionBackground->getPosition().y + 176 );
	//m_ButtonSoundMutePos = sf::Vector2f(m_OptionBackground->getPosition().x + 701,m_OptionBackground->getPosition().y + 283);
	//m_ButtonFullScreenPos = sf::Vector2f(m_OptionBackground->getPosition().x + 98,m_OptionBackground->getPosition().y + 389);
	//m_ButtonWindowedPos = sf::Vector2f(m_OptionBackground->getPosition().x + 364,m_OptionBackground->getPosition().y + 389);
	//m_ButtonReturnPos = sf::Vector2f(m_OptionBackground->getPosition().x + 702 ,m_OptionBackground->getPosition().y + 391);
	//
	m_OptionBackground->setPosition(100,200);

	m_ButtonFullScreen.SetPosition(m_ButtonFullScreenPos.x,m_ButtonFullScreenPos.y);
	m_ButtonWindowed.SetPosition(m_ButtonWindowedPos.x,m_ButtonWindowedPos.y);
	m_ButtonMusicMute.SetPosition(m_ButtonMusicMutePos.x,m_ButtonMusicMutePos.y);
	m_ButtonSoundMute.SetPosition(m_ButtonSoundMutePos.x,m_ButtonSoundMutePos.y);
	m_ButtonReturn.SetPosition(m_ButtonReturnPos.x,m_ButtonReturnPos.y);


	return false;
}

void GameState::ExitState()
{
	cout << "GameState::ExitState" << endl;
}


bool GameState::Update(float p_DeltaTime)
{
	HandleInput();
	if (!m_Paused)
	{

		if(m_GameObjMgr->m_pxPlayer != nullptr)
		{
			m_GameObjMgr->m_pxPlayer->Update(m_pInputManager, m_SpriteManager, m_Camera, p_DeltaTime);
		}


		//m_pxCollisionManager->CheckCollisionRectVsCircle();

		if( m_GameObjMgr->m_pxPlayer->GetState() != Growing && m_GameObjMgr->m_pxPlayer->GetState() != Death)
		{
			m_pxCollisionManager->CheckCollisionRectVsRect();
			m_GameObjMgr->UpdateAllObjects(p_DeltaTime);
		}
		m_Camera->Update(m_GameObjMgr, m_LevelLayerMidleGround, p_DeltaTime );
		UpdateGUI();
		UpdateTutorial();

		/*if(m_GameObjMgr->m_pxPlayer->GetGameStatus() )
		{

		}*/
	} else
	{
		HandlePause();
	}

	if(m_GameObjMgr->m_pxPlayer->GetGameWinStatus() )
	{

		m_pCore->m_StateManager.SetState("WinState");
		Cleanup();
	}
	else if(m_GameObjMgr->m_pxPlayer->GetGameOverStatus() )
	{
		m_pCore->m_StateManager.SetState("EndState");
		Cleanup();
		/*m_window->setView(m_window->getDefaultView());
		m_Camera->Update(m_GameObjMgr, m_LevelLayerMidleGround, p_DeltaTime );*/



	}
	for (int i = 0; i < m_GameObjMgr->m_apxGameObject.size(); i++)
	{
		if (m_GameObjMgr->m_apxGameObject[i]->GetType() == "Enemy" && m_GameObjMgr->m_apxGameObject[i]->GetCurrentLevel() < m_GameObjMgr->m_pxPlayer->GetCurrentLevel())
		{
			m_GameObjMgr->m_apxGameObject[i]->SetColor(sf::Color::Green);
		}
		else if (m_GameObjMgr->m_apxGameObject[i]->GetType() == "Enemy" && m_GameObjMgr->m_apxGameObject[i]->GetCurrentLevel() == m_GameObjMgr->m_pxPlayer->GetCurrentLevel())
		{
			m_GameObjMgr->m_apxGameObject[i]->SetColor(sf::Color::Yellow);
		}
		else if (m_GameObjMgr->m_apxGameObject[i]->GetType() == "Enemy" && m_GameObjMgr->m_apxGameObject[i]->GetCurrentLevel() < m_GameObjMgr->m_pxPlayer->GetCurrentLevel())
		{
			m_GameObjMgr->m_apxGameObject[i]->SetColor(sf::Color::Red);
		}
	}

	//else if (m_GameObjMgr->GetEnemyCounter() == 0)
	//{
	//	cout<< "YOU WIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	//	m_pCore->m_StateManager.SetState("EndState");
	//	Cleanup();
	//}

	return true;
}
void GameState::HandlePause()
{


	//m_SliderMusicVol.m_FullSlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
	m_SliderMusicVol.SetColor(sf::Color::White);
	//m_SliderMusicVol.SetValue(50);
	m_SliderSoundVol.SetColor(sf::Color::White);
	//m_SliderSoundVol.SetValue(50);

	MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);
	if (m_pInputManager->IsDown(MB_LEFT))
	{
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 1 && (m_ButtonClick == 0 || m_ButtonClick == 1)) // Fullscreen
		{
			m_ButtonClick = 1;
			m_ButtonFullScreen.SetSpriteRect(m_SpriteManager->Load("fullscreen.png",488,0,244,57)); 
			m_ButtonFullScreen.SetPosition(m_ButtonFullScreenPos.x,m_ButtonFullScreenPos.y);
		}
		else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 2 && (m_ButtonClick == 0 || m_ButtonClick == 2)) // Windowed
		{
			m_ButtonClick = 2;
			m_ButtonWindowed.SetSpriteRect(m_SpriteManager->Load("windowed.png",488,0,244,57)); 
			m_ButtonWindowed.SetPosition(m_ButtonWindowedPos.x,m_ButtonWindowedPos.y);
		}
		else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 3 && (m_ButtonClick == 0 || m_ButtonClick == 3)) // Music
		{
			m_ButtonClick = 3;
			m_ButtonMusicMute.SetSpriteRect(m_SpriteManager->Load("mute.png",170,0,85,57));
			m_ButtonMusicMute.SetPosition(m_ButtonMusicMutePos.x,m_ButtonMusicMutePos.y);

		}
		else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 4 && (m_ButtonClick == 0 || m_ButtonClick == 4)) // Sound 
		{
			m_ButtonClick = 4;
			m_ButtonSoundMute.SetSpriteRect(m_SpriteManager->Load("mute.png",170,0,85,57));
			m_ButtonSoundMute.SetPosition(m_ButtonSoundMutePos.x,m_ButtonSoundMutePos.y);

		}
		else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 5 && (m_ButtonClick == 0 || m_ButtonClick == 5)) // Back
		{
			m_ButtonClick = 5;
			m_ButtonReturn.SetSpriteRect(m_SpriteManager->Load("backarrow.png",170,0,85,57));
			m_ButtonReturn.SetPosition(m_ButtonReturnPos.x,m_ButtonReturnPos.y);
		}
		else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 6 && (m_ButtonClick == 0 || m_ButtonClick == 6)) // Play
		{
			m_ButtonClick = 6;
			m_ButtonPlay.SetSpriteRect(m_SpriteManager->Load("Play_options_sprite.png",170,0,85,57));
			m_ButtonPlay.SetPosition(m_ButtonPlayPos.x, m_ButtonPlayPos.y);
		}
		else if (MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 7 && (m_ButtonClick == 0 || m_ButtonClick == 7)) // Exit
		{
			m_ButtonClick = 7;
			m_ButtonExit.SetSpriteRect(m_SpriteManager->Load("exit_options_sprite.png",170,0,85,57));
			m_ButtonExit.SetPosition(m_ButtonExitPos.x, m_ButtonExitPos.y);
		}
		else if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y)  == 0 && m_ButtonClick == 0)
		{m_ButtonClick = -1;

		}

		m_SliderMusicVol.MouseDown(sf::Mouse::getPosition(*m_window).x,sf::Mouse::getPosition(*m_window).y);
		m_SoundManager->SetMusicVolume(m_SliderMusicVol.GetValue());
		m_SliderSoundVol.MouseDown(sf::Mouse::getPosition(*m_window).x,sf::Mouse::getPosition(*m_window).y);
		m_SoundManager->SetSoundVolume(m_SliderSoundVol.GetValue());
		//m_SliderMusicVol.MoveMouse(sf::Mouse::getPosition(*m_window).x,sf::Mouse::getPosition(*m_window).y);
		//m_SliderSoundVol.MoveMouse(sf::Mouse::getPosition(*m_window).x,sf::Mouse::getPosition(*m_window).y);

	}
	else if (m_pInputManager->IsReleased(MB_LEFT))
	{
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 1 && m_ButtonClick == 1) // Fullscreen
		{
			m_pCore->window->create(sf::VideoMode(1280,720), "Tale of the Deep", sf::Style::Fullscreen);
			m_pCore->window->setVerticalSyncEnabled(true);
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 2 && m_ButtonClick == 2) // Windowed
		{
			m_pCore->window->create(sf::VideoMode(1280,720), "Tale of the Deep");
			m_pCore->window->setVerticalSyncEnabled(true);
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 3 && m_ButtonClick == 3) // Music
		{
			m_SoundManager->SetMusicVolume(0);
			m_SliderMusicVol.SetValue(m_SliderMusicVol.GetValue());
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 4 && m_ButtonClick == 4) // Sound
		{
			m_SoundManager->SetSoundVolume(0);
			m_SliderSoundVol.SetValue(m_SliderSoundVol.GetValue());
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 5 && m_ButtonClick == 5) // Back
		{
			m_pCore->m_StateManager.SetState("StartState");
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 6 && m_ButtonClick == 6) // Play
		{
			m_Paused = false;
			m_Camera->ZoomOut(m_Camera->GetTotalZoom()  );
		}
		if(MouseOver(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y) == 7 && m_ButtonClick == 7) // Exit
		{
			std::exit(0);
		}
		m_ButtonClick = 0;
		m_SliderMusicVol.MouseUp();
		m_SliderSoundVol.MouseUp();
	}
}
int GameState::MouseOver(int x, int y)
{
	int circlex;
	int circley;
	int deltax;
	int deltay;
	int distancestuff;

	////////////////
	// FullScreen //
	////////////////

	int bw = m_ButtonFullScreen.GetSprite()->getGlobalBounds().width;
	int bh = m_ButtonFullScreen.GetSprite()->getGlobalBounds().height;
	int bx = m_ButtonFullScreen.GetSprite()->getGlobalBounds().left; 
	int by = m_ButtonFullScreen.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) ) 
	{
		m_ButtonFullScreen.SetSpriteRect(m_SpriteManager->Load("fullscreen.png",244,0,244,57));
		m_ButtonFullScreen.SetPosition(m_ButtonFullScreenPos.x,m_ButtonFullScreenPos.y);
		return 1;
	}else
	{
		m_ButtonFullScreen.SetSpriteRect(m_SpriteManager->Load("fullscreen.png",0,0,244,57));
		m_ButtonFullScreen.SetPosition(m_ButtonFullScreenPos.x, m_ButtonFullScreenPos.y);
	}

	///////////////
	// Windowed  //
	///////////////

	bw = m_ButtonWindowed.GetSprite()->getGlobalBounds().width;
	bh = m_ButtonWindowed.GetSprite()->getGlobalBounds().height;
	bx = m_ButtonWindowed.GetSprite()->getGlobalBounds().left; 
	by = m_ButtonWindowed.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) )  
	{
		m_ButtonWindowed.SetSpriteRect(m_SpriteManager->Load("windowed.png",244,0,244,57));
		m_ButtonWindowed.SetPosition(m_ButtonWindowedPos.x,m_ButtonWindowedPos.y);
		return 2;
	}else
	{
		m_ButtonWindowed.SetSpriteRect(m_SpriteManager->Load("windowed.png",0,0,244,57));
		m_ButtonWindowed.SetPosition(m_ButtonWindowedPos.x, m_ButtonWindowedPos.y);
	}

	///////////////
	// Music  //
	///////////////

	bw = m_ButtonMusicMute.GetSprite()->getGlobalBounds().width;
	bh = m_ButtonMusicMute.GetSprite()->getGlobalBounds().height;
	bx = m_ButtonMusicMute.GetSprite()->getGlobalBounds().left; 
	by = m_ButtonMusicMute.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) )  
	{
		m_ButtonMusicMute.SetSpriteRect(m_SpriteManager->Load("mute.png",85,0,85,57));
		m_ButtonMusicMute.SetPosition(m_ButtonMusicMutePos.x,m_ButtonMusicMutePos.y);
		return 3;
	}else
	{
		m_ButtonMusicMute.SetSpriteRect(m_SpriteManager->Load("mute.png",0,0,85,57));
		m_ButtonMusicMute.SetPosition(m_ButtonMusicMutePos.x, m_ButtonMusicMutePos.y);
	}

	///////////////
	// Sound  //
	///////////////

	bw = m_ButtonSoundMute.GetSprite()->getGlobalBounds().width;
	bh = m_ButtonSoundMute.GetSprite()->getGlobalBounds().height;
	bx = m_ButtonSoundMute.GetSprite()->getGlobalBounds().left; 
	by = m_ButtonSoundMute.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) )  
	{
		m_ButtonSoundMute.SetSpriteRect(m_SpriteManager->Load("mute.png",85,0,85,57));
		m_ButtonSoundMute.SetPosition(m_ButtonSoundMutePos.x,m_ButtonSoundMutePos.y);
		return 4;
	}else
	{
		m_ButtonSoundMute.SetSpriteRect(m_SpriteManager->Load("mute.png",0,0,85,57));
		m_ButtonSoundMute.SetPosition(m_ButtonSoundMutePos.x, m_ButtonSoundMutePos.y);
	}


	///////////////
	// Back  //
	///////////////

	bw = m_ButtonReturn.GetSprite()->getGlobalBounds().width;
	bh = m_ButtonReturn.GetSprite()->getGlobalBounds().height;
	bx = m_ButtonReturn.GetSprite()->getGlobalBounds().left; 
	by = m_ButtonReturn.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) )  
	{
		m_ButtonReturn.SetSpriteRect(m_SpriteManager->Load("backarrow.png",85,0,85,57));
		m_ButtonReturn.SetPosition(m_ButtonReturnPos.x,m_ButtonReturnPos.y);
		return 5;
	}else
	{
		m_ButtonReturn.SetSpriteRect(m_SpriteManager->Load("backarrow.png",0,0,85,57));
		m_ButtonReturn.SetPosition(m_ButtonReturnPos.x, m_ButtonReturnPos.y);
	}

	///////////////
	// Play  //
	///////////////

	bw = m_ButtonPlay.GetSprite()->getGlobalBounds().width;
	bh = m_ButtonPlay.GetSprite()->getGlobalBounds().height;
	bx = m_ButtonPlay.GetSprite()->getGlobalBounds().left; 
	by = m_ButtonPlay.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) )  
	{
		m_ButtonPlay.SetSpriteRect(m_SpriteManager->Load("Play_options_sprite.png",85,0,85,57));
		m_ButtonPlay.SetPosition(m_ButtonPlayPos.x,m_ButtonPlayPos.y);
		return 6;
	}else
	{
		m_ButtonPlay.SetSpriteRect(m_SpriteManager->Load("Play_options_sprite.png",0,0,85,57));
		m_ButtonPlay.SetPosition(m_ButtonPlayPos.x, m_ButtonPlayPos.y);
	}
	///////////////
	// Exit  //
	///////////////

	bw = m_ButtonExit.GetSprite()->getGlobalBounds().width;
	bh = m_ButtonExit.GetSprite()->getGlobalBounds().height;
	bx = m_ButtonExit.GetSprite()->getGlobalBounds().left; 
	by = m_ButtonExit.GetSprite()->getGlobalBounds().top;
	if ((x > bx && x < bx + bw ) && (y > by  && y < by + bh ) )  
	{
		m_ButtonExit.SetSpriteRect(m_SpriteManager->Load("exit_options_sprite.png",85,0,85,57));
		m_ButtonExit.SetPosition(m_ButtonExitPos.x, m_ButtonExitPos.y);
		return 7;
	}else
	{
		m_ButtonExit.SetSpriteRect(m_SpriteManager->Load("exit_options_sprite.png",0,0,85,57));
		m_ButtonExit.SetPosition(m_ButtonExitPos.x, m_ButtonExitPos.y);
	}


	return 0;
}
void GameState::MouseDown(int x, int y)
{
	MouseOver(x,y);
}



void GameState::UpdateGUI()
{
	/*m_GuiEnergy.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
	m_GuiPower.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
	m_GuiSpeed.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );*/

	if(m_Camera->IsZoomingOut() )
	{
		Gui->setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_EnergySlider.m_FullSlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_HealthSlider.m_FullSlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_EnergySlider.m_EmptySlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_HealthSlider.m_EmptySlider.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_EnergySlider.m_SliderBox.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_HealthSlider.m_SliderBox.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_GuiEnergy.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_GuiPower.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
		m_GuiSpeed.setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );
	}

	if (m_GameObjMgr->m_pxPlayer->GetPowerupEnergyCount() == 1)
	{
		sf::Vector2f tmp = m_GuiEnergy.getScale();
		m_GuiEnergy = m_SpriteManager->Loadnonpointer("newGUI.png",281,312,281,156);
		m_GuiEnergy.setScale(tmp);
	} else
		if (m_GameObjMgr->m_pxPlayer->GetPowerupEnergyCount() == 2)
		{
			sf::Vector2f tmp = m_GuiEnergy.getScale();
			m_GuiEnergy = m_SpriteManager->Loadnonpointer("newGUI.png",562,312,281,156);
			m_GuiEnergy.setScale(tmp);
		} else
			if (m_GameObjMgr->m_pxPlayer->GetPowerupEnergyCount() == 3)
			{
				sf::Vector2f tmp = m_GuiEnergy.getScale();
				m_GuiEnergy = m_SpriteManager->Loadnonpointer("newGUI.png",843,312,281,156);
				m_GuiEnergy.setScale(tmp);
			}


			if (m_GameObjMgr->m_pxPlayer->GetPowerupSpeedCount() == 1)
			{
				sf::Vector2f tmp = m_GuiSpeed.getScale();
				m_GuiSpeed = m_SpriteManager->Loadnonpointer("newGUI.png",281,156,281,156);
				m_GuiSpeed.setScale(tmp);
			} else
				if (m_GameObjMgr->m_pxPlayer->GetPowerupSpeedCount() == 2)
				{
					sf::Vector2f tmp = m_GuiSpeed.getScale();
					m_GuiSpeed = m_SpriteManager->Loadnonpointer("newGUI.png",562,156,281,156);
					m_GuiSpeed.setScale(tmp);
				} else
					if (m_GameObjMgr->m_pxPlayer->GetPowerupSpeedCount() == 3)
					{
						sf::Vector2f tmp = m_GuiSpeed.getScale();
						m_GuiSpeed = m_SpriteManager->Loadnonpointer("newGUI.png",843,156,281,156);
						m_GuiSpeed.setScale(tmp);
					}


					if (m_GameObjMgr->m_pxPlayer->GetPowerupLightCount() == 1)
					{
						sf::Vector2f tmp = m_GuiPower.getScale();
						m_GuiPower = m_SpriteManager->Loadnonpointer("newGUI.png",281,468,281,156);
						m_GuiPower.setScale(tmp);
					}else
						if (m_GameObjMgr->m_pxPlayer->GetPowerupLightCount() == 2)
						{
							sf::Vector2f tmp = m_GuiPower.getScale();
							m_GuiPower = m_SpriteManager->Loadnonpointer("newGUI.png",562,468,281,156);
							m_GuiPower.setScale(tmp);
						}else
							if (m_GameObjMgr->m_pxPlayer->GetPowerupLightCount() == 3)
							{
								sf::Vector2f tmp = m_GuiPower.getScale();
								m_GuiPower = m_SpriteManager->Loadnonpointer("newGUI.png",843,468,281,156);
								m_GuiPower.setScale(tmp);
							}


							Gui->setPosition(m_Camera->GetCameraView().getCenter().x - 
								(m_Camera->GetCameraView().getSize().x / 2.0f) + 
								(50.f * m_Camera->GetTotalZoom() ), m_Camera->GetCameraView().getCenter().y - 
								(m_Camera->GetCameraView().getSize().y / 2.0f) + 
								(50.f * m_Camera->GetTotalZoom() ) );


							m_GuiPower.setPosition(Gui->getPosition().x,Gui->getPosition().y);
							m_GuiEnergy.setPosition(Gui->getPosition().x,Gui->getPosition().y);
							m_GuiSpeed.setPosition(Gui->getPosition().x,Gui->getPosition().y);


							sf::Vector2f GUI_pos = Gui->getPosition();
							m_HealthSlider.SetValue(m_GameObjMgr->m_pxPlayer->GetHealth());
							m_HealthSlider.SetPosition(GUI_pos.x + (75 * m_Camera->GetTotalZoom() ) ,GUI_pos.y + (79 * m_Camera->GetTotalZoom() ) );

							if (m_GameObjMgr->m_pxPlayer->GetStageTwo())
							{
								m_EnergySlider.SetColor(sf::Color(0,230,119,255));
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
void GameState::DrawGUI()
{
	m_DrawManager->DrawSlider(m_HealthSlider);
	m_DrawManager->DrawSlider(m_EnergySlider);
	m_DrawManager->Draw(Gui);
	m_window->draw(m_GuiEnergy);
	m_window->draw(m_GuiPower);
	m_window->draw(m_GuiSpeed);
}


void GameState::HandleInput()
{
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Escape))
	{
		if (m_Paused)
		{
			m_Paused = false;
			m_Camera->ZoomOut(m_Camera->GetTotalZoom()  );
		}else
		{
			m_Paused = true;
			m_Camera->ZoomStart(m_window->getDefaultView() );
			m_OptionBackground->setPosition(200,100);
			//m_OptionBackground->setScale(Gui->getScale().x * m_Camera->GetZoomStrength(), Gui->getScale().y *  m_Camera->GetZoomStrength() );

			m_ButtonMusicMutePos = sf::Vector2f(m_OptionBackground->getPosition().x + 701,m_OptionBackground->getPosition().y + 176 );

			m_ButtonSoundMutePos = sf::Vector2f(m_OptionBackground->getPosition().x + 701,m_OptionBackground->getPosition().y + 283);

			m_ButtonFullScreenPos = sf::Vector2f(m_OptionBackground->getPosition().x + 98,m_OptionBackground->getPosition().y + 389);

			m_ButtonWindowedPos = sf::Vector2f(m_OptionBackground->getPosition().x + 364,m_OptionBackground->getPosition().y + 389);

			m_ButtonReturnPos = sf::Vector2f(m_OptionBackground->getPosition().x + 364 ,m_OptionBackground->getPosition().y + 481);

			m_ButtonPlayPos = sf::Vector2f(m_OptionBackground->getPosition().x + 67 ,m_OptionBackground->getPosition().y + 481);

			m_ButtonExitPos = sf::Vector2f(m_OptionBackground->getPosition().x + 701 ,m_OptionBackground->getPosition().y + 481);

			m_SliderMusicVol.SetSlider(m_OptionBackground->getPosition().x+65,m_OptionBackground->getPosition().y+205,600,25);
			m_SliderSoundVol.SetSlider(m_OptionBackground->getPosition().x+65,m_OptionBackground->getPosition().y+314,600,25);
		}
	}
	if(m_pInputManager->IsDownOnceK(sf::Keyboard::Num1))
	{
		//m_pCore->m_StateManager.SetState("StartState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num2))
	{
		//cout << " You are already in GameState" << endl;
		//m_pCore->m_StateManager.SetState("GameState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num3))
	{
		//m_pCore->m_StateManager.SetState("OptionState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num4))
	{
		//m_pCore->m_StateManager.SetState("EndState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num0))
	{
		/*if(m_Camera->GetFilterStatus() == true )
		{
			m_Camera->ToggleFilterOn(false);
		}
		else
		{
			m_Camera->ToggleFilterOn(true);
		}*/
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num9))
	{
		//m_Camera->ZoomStart(m_window->getDefaultView() );
	}
	if (m_pInputManager->IsDownK(sf::Keyboard::Num8))
	{

		//m_Camera->SetZoomStrength(1.005f);
		//m_Camera->ZoomOut(m_Camera->GetZoomStrength()  );
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





	if(m_GameObjMgr->m_pxPlayer->GetState() != Death)
	{
		DrawGUI();
	}

	for (int i = 0; i < m_GameObjMgr->m_apxGameObject.size(); i++)
	{
		if( (m_GameObjMgr->m_apxGameObject[i]->GetType() == "Enemy"))
		{

			m_window->draw(m_GameObjMgr->m_apxGameObject[i]->GetGlowRectange(), m_GameObjMgr->m_apxGameObject[i]->GetGlowTexture());
		}
	}


	DrawTutorial();

	if (m_Paused)
	{
		m_DrawManager->Draw(m_BackGroundImg);
		m_DrawManager->Draw(m_OptionBackground);
		m_DrawManager->Draw(m_ButtonMusicMute.GetSprite());
		m_DrawManager->Draw(m_ButtonSoundMute.GetSprite());
		m_DrawManager->Draw(m_ButtonFullScreen.GetSprite());
		m_DrawManager->Draw(m_ButtonWindowed.GetSprite());
		m_DrawManager->Draw(m_ButtonReturn.GetSprite());
		m_DrawManager->Draw(m_ButtonPlay.GetSprite());
		m_DrawManager->Draw(m_ButtonExit.GetSprite());
		m_DrawManager->DrawSlider(m_SliderMusicVol);
		m_DrawManager->DrawSlider(m_SliderSoundVol);
	}
	//m_DrawManager->DrawRect(m_GameObjMgr->m_pxPlayer->GetCollider()->PlayerRect() );
	m_DrawManager->DisplayWindow();
}

bool GameState::IsType(const string &p_type)
{
	return p_type.compare("GameState") == 0;
}
//Sten
void GameState::Cleanup()
{
	m_GameObjMgr->Cleanup();
	delete m_LevelLayerBackgroundLowest;
	m_LevelLayerBackgroundLowest = nullptr;
	delete m_LevelLayerBackgroundSecondLowest;
	m_LevelLayerBackgroundSecondLowest = nullptr;
	delete m_LevelLayerBackgroundSecondHighest;
	m_LevelLayerBackgroundSecondHighest = nullptr;
	delete m_LevelLayerMidleGround;
	m_LevelLayerMidleGround = nullptr;
	delete m_LevelLayerMiddleFront;
	m_LevelLayerMiddleFront = nullptr;
	delete m_LevelLayerForGround;
	m_LevelLayerForGround = nullptr;
	m_pxCollisionManager->Cleanup();
	delete Gui;
	Gui = nullptr;
	delete m_Camera;
	m_Camera = nullptr;
	
}

void GameState::TutorialWASD()
{
	m_TutorialSpriteWASD = m_SpriteManager->Loadnonpointer("press_wasd_small.png",0,0,365,103);
	m_TutorialSpriteWASD.setScale(sf::Vector2f(2,2));
	m_TutorialSpriteWASD.setPosition(m_Camera->GetCameraView().getCenter().x - 300 ,m_Camera->GetCameraView().getCenter().y - 300);


	if (m_GameObjMgr->m_pxPlayer->GetPosition().x > 3500)
	{
		m_TutorialWASD = false;
	}

}

void GameState::TutorialSpace()
{
	m_TutorialSpriteSPACE = m_SpriteManager->Loadnonpointer("press_spacebar_small.png",0,0,462,62);
	m_TutorialSpriteSPACE.setScale(sf::Vector2f(2,2));
	m_TutorialSpriteSPACE.setPosition(m_Camera->GetCameraView().getCenter().x - 450 ,m_Camera->GetCameraView().getCenter().y - 300);
	if (m_GameObjMgr->m_pxPlayer->GetPosition().x > 3750  && m_GameObjMgr->m_pxPlayer->GetPosition().y < 3840 && m_GameObjMgr->m_pxPlayer->GetExperience() == 0)
	{
		m_TutorialSPACE = true;
	}else
	{
		m_TutorialSPACE = false;
	}

}
void GameState::TutorialF()
{
	m_TutorialSpriteF = m_SpriteManager->Loadnonpointer("press_f_small.png",0,0,392,62);
	m_TutorialSpriteF.setScale(sf::Vector2f(3,3));
	m_TutorialSpriteF.setPosition(m_Camera->GetCameraView().getCenter().x - 500 ,m_Camera->GetCameraView().getCenter().y - 380);
	if ( m_GameObjMgr->m_pxPlayer->GetPosition().y > 3840 && m_GameObjMgr->m_pxPlayer->GetStageTwo() && !m_TutorialFPressed )
	{
		m_TutorialF = true;
		if (m_pInputManager->IsDownK(sf::Keyboard::F))
		{
			m_TutorialFPressed = true;
		}
	}else
	{
		m_TutorialF = false;
	}


}

void GameState::UpdateTutorial()
{

	TutorialWASD();
	TutorialSpace();
	TutorialF();

}
void GameState::DrawTutorial()
{
	if (m_TutorialWASD)
	{
		m_window->draw(m_TutorialSpriteWASD);
	}

	if (m_TutorialSPACE)
	{
		m_window->draw(m_TutorialSpriteSPACE);
	}

	if (m_TutorialF)
	{
		m_window->draw(m_TutorialSpriteF);
	}
}

