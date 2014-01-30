// Core.cpp
#include "stdafx.h"

#include "Core.h"
//using namespace sf;

Core::Core()
{
	m_bRunning = false;
	window = nullptr;
	m_fDeltaTime = 0.0f;
}

Core::~Core()
{
	Cleanup();
}

bool Core::Initialize()
{

	//window (VideoMode(1024,640), "MEGA FUCKING AWESOME SUPER GAME");
	window = new sf::RenderWindow(sf::VideoMode(1024,640), (string)"MEGA FUCKING AWESOME SUPER GAME");

	if (m_StateManager.GetCurrentState() == nullptr)
	{
		m_StateManager.Attach(new GameState());
		m_StateManager.Attach(new OptionState());
		m_StateManager.Attach(new StartState());

		m_StateManager.SetState("GameState");
	}


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
			else if (event.type == sf::Event::KeyReleased)
			{
				//			InputManager::OnKeyboard(event.key, true);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				//			InputManager::OnKeyboard(event.key, true);
			}


		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window->close();
		}

		/*	if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
		window.close();
		}
		*/
		sf::CircleShape shape(10.0f);

		window->clear(sf::Color(0x11,0x22,0x33,0xff));
		window->draw(shape);
		window->display();
	}

}

void Core::Cleanup()
{

}

