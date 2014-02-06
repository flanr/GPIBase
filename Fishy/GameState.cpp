// GameState.cpp

#include "stdafx.h"
#include "GameState.h"
#include "Core.h"
#include "PlayerFishObject.h"
#include "FishObject.h"

using namespace std;
GameState::GameState(Core* p_pCore)
{
	m_pCore = p_pCore;
	m_pInputManager = p_pCore->m_pInputManager;
	m_pWindow = p_pCore->window;
	m_player = p_pCore->m_player;
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

	return false;
}

void GameState::ExitState()
{
	cout << "GameState::ExitState" << endl;
}

bool GameState::Update(float p_DeltaTime)
{
	HandleInput();
	Draw();
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
		cout << "Already in GameState" << endl;
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
	


	sf::CircleShape shape(30.0f);
	m_pWindow->clear(sf::Color(0x11,0x22,0x33,0xff));
	m_pWindow->draw(shape);
	//m_pWindow->draw();
}

bool GameState::IsType(const string &p_type)
{
	return p_type.compare("GameState") == 0;
}																																										//Sten