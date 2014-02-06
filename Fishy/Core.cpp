// Core.cpp
#include "stdafx.h"
#include "FishObject.h"
#include "PlayerFishObject.h"
#include "GameObject.h"
#include "GameObjectManager.h"

#include "Core.h"
//using namespace sf;

Core::Core()
{
	m_bRunning = false;
	window = nullptr;
	m_pInputManager = nullptr;
	m_fDeltaTime = 0.0f;
	playerSprite = nullptr;
	
}

Core::~Core()
{
	Cleanup();
}

bool Core::Initialize()
{

	//window (VideoMode(1024,640), "MEGA FUCKING AWESOME SUPER GAME");
	window = new sf::RenderWindow(sf::VideoMode(1024,640), (string)"MEGA AWESOME SUPER GAME");

	if (m_pInputManager == nullptr)
	{
		m_pInputManager = new InputManager;
	}
	//Delete the states*******************************************************************
	if (m_StateManager.GetCurrentState() == nullptr)
	{
		m_StateManager.Attach(new GameState(this));
		m_StateManager.Attach(new OptionState(this));
		m_StateManager.Attach(new StartState(this));

		m_StateManager.SetState("StartState");
	}
	
	sf::Texture	texture;
	if (!texture.loadFromFile("player.png"))
	{
	};
	texture.setSmooth(true);

//	playerSprite->setTexture(texture);
	
	collider = new Collider;
	//m_player = new PlayerFishObject(playerSprite, collider);
	
	return true;
}

void Core::Run()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

			////////Following is a demo: to have window.pollEvent(param) or window->close() in imput manager, add a sf::RenderWindow parameter
			////////to UpdateEvents and copypaste. 
			////////Demonstrating isdown and isdownonce functions in the console.
			m_pInputManager->UpdateEvents(event);
		}
		if (m_pInputManager->IsDownOnceK(sf::Keyboard::Key::A))
		{
			std::cout << "IsDownOnce\n";
		}
		if(m_pInputManager->IsDownK(sf::Keyboard::Key::D))
		{
			std::cout << "IsDown\n";
		}
		if (m_pInputManager->IsDown(MB_LEFT))
		{
			std::cout << "IsDownMouse\n";
		}
		if (m_pInputManager->IsDownOnce(MB_RIGHT))
		{
			std::cout << "IsDownOnceMouse\n";
		}

		


		m_StateManager.Update(m_fDeltaTime);
		
		window->display();

		//Must have postupdates for isdownonce to function properly.
		m_pInputManager->PostUpdateKeyboard();
		m_pInputManager->PostUpdateMouse();
	}

}

void Core::Cleanup()
{
	if (m_pInputManager != nullptr)
	{
		delete m_pInputManager;
		m_pInputManager = nullptr;
	}
}