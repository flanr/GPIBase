// InputManager.cpp
#include "stdafx.h"
#include "InputManager.h"


InputManager::InputManager()
{
	for (int i = 0; i < sf::Keyboard::Key::KeyCount ; i++)
	{
		m_Current[i] = false;
		m_Previous[i] = false;
	}

	for (int i = 0; i < MB_COUNT; i++)
	{
		m_current[i] = false;
		m_previous[i] = false;
	}
}

void InputManager::UpdateEvents(Core* p_pCore)
{
	sf::Event event;
	while (p_pCore->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			p_pCore->window->close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			int index = event.key.code;
			m_Current[index] = true;

		}
		else if (event.type == sf::Event::KeyReleased)
		{
			int index = event.key.code;
			m_Current[index]  = false;
			//std::cout << "released\n";
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			int index = event.key.code;
			m_current[index] = true;
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			int index = event.key.code;
			m_current[index] = false;
			//std::cout << "released\n";
		}
		if (IsDownOnceK(sf::Keyboard::Num1))
		{
			p_pCore->m_StateManager->SetState("StartState");
		}
		if (IsDownOnceK(sf::Keyboard::Num2))
		{
			p_pCore->m_StateManager->SetState("GameState");
		}
		if (IsDownOnceK(sf::Keyboard::Num3))
		{
			p_pCore->m_StateManager->SetState("OptionState");
		}
	}
	//Must have postupdates for isdownonce to function properly.
	PostUpdateKeyboard();
	PostUpdateMouse();
}

bool InputManager::IsDownK(int key) const
{
	return m_Current[key];
}
bool InputManager::IsDownOnceK(int key) const
{
	return m_Current[key] && !m_Previous[key];
}


void InputManager::PostUpdateKeyboard()
{
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		m_Previous[i] = m_Current[i];
	}
}




float InputManager::GetX() const
{
	return m_x;
}
float InputManager::GetY() const
{
	return m_y;
}
bool InputManager::IsDown(EMouseButton button) const
{
	return m_current[button];
}
bool InputManager::IsDownOnce(EMouseButton button) const
{
	return m_current[button] && ! m_previous[button];
}

void InputManager::PostUpdateMouse()
{
	for (int i = 0; i < MB_COUNT; i++)
	{
		m_previous[i] = m_current[i];
	}
}
