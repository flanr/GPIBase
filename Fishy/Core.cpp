// Core.cpp
#include "stdafx.h"
#include "FishObject.h"
#include "PlayerFishObject.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "StateManager.h"
#include "DrawManager.h"

#include "Core.h"
//using namespace sf;

Core::Core()
{
	m_bRunning = false;
	window = nullptr;
	m_pInputManager = nullptr;

	playerSprite = nullptr;
	m_StateManager = nullptr;
	m_DrawManager = nullptr;

	m_fDeltaTime = 0.0f;
	m_Clock.restart();

}

Core::~Core()
{
	Cleanup();
}

bool Core::Initialize()
{

	//window (VideoMode(1024,640), "MEGA FUCKING AWESOME SUPER GAME");
	window = new sf::RenderWindow(sf::VideoMode(1024,640), (string)"MEGA AWESOME SUPER GAME");

	//This sets framerate to the monitors framerate (like 60FPS), if this is commented out the loop will run faster
	window->setVerticalSyncEnabled(true);
	//This sets framerate to your chosen limit, (DON'T use together with vertical sync above)
	//window->setFramerateLimit(30);

	if (m_pInputManager == nullptr)
	{
		m_pInputManager = new InputManager();
	}

	if (m_DrawManager == nullptr)
	{
		m_DrawManager = new DrawManager(window);
	}
	//Delete the states*******************************************************************
	m_StateManager = new StateManager();
	if (m_StateManager->GetCurrentState() == nullptr)
	{
		m_StateManager->Attach(new GameState(this));
		m_StateManager->Attach(new OptionState(this));
		m_StateManager->Attach(new StartState(this));

		m_StateManager->SetState("StartState");
	}


	collider = new Collider;


	return true;
}

void Core::Run()
{

	//while(m_StateManager->IsRunning() )
	//{
		
		while (window->isOpen())
		{
			UpdateDeltatime();
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();
				}


				m_pInputManager->UpdateEvents(event);
			}

			m_StateManager->Update(m_fDeltaTime);
			m_StateManager->Draw();
			//Must have postupdates for isdownonce to function properly.
			m_pInputManager->PostUpdateKeyboard();
			m_pInputManager->PostUpdateMouse();
		}
	/*}*/
}

void Core::Cleanup()
{
	if (m_pInputManager != nullptr)
	{
		delete m_pInputManager;
		m_pInputManager = nullptr;
	}
}

void Core::UpdateDeltatime()
{
	sf::Time m_TimeSinceLastUpdate = sf::Time::Zero;
	m_TimeSinceLastUpdate += m_Clock.restart();

	m_fDeltaTime = m_TimeSinceLastUpdate.asSeconds();

	if(m_fDeltaTime > 0.1f)
	{
		m_fDeltaTime = 0.1f;
	}
	cout << m_fDeltaTime << endl;
}