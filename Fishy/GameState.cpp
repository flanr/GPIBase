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
	m_pWindow = p_pCore->window;

	m_circle = new Collider(sf::Vector2f(100.f, 100.f), 20);
	m_circle2 = new Collider(sf::Vector2f(200.f,200.f), 20);
	m_rect = new Collider(sf::Vector2f(300.f, 300.f), sf::Vector2f(50.f, 20.f));
	m_circle3 = new Collider(sf::Vector2f(400.f,400.f), 15.f);

	m_rect2 = new Collider(sf::Vector2f(500.f,500.f), sf::Vector2f(100.f, 50.f));
	m_rect3 = new Collider(sf::Vector2f(500.f, 600.f), sf::Vector2f(100.f,50.f));

	mgr = new CollisionManager;
	sf::CircleShape shape(20.0f);
	sf::CircleShape shape2(20.f);
	sf::CircleShape shape3(15.f);
	sf::RectangleShape rect(sf::Vector2f(50.f, 20.f));
	m_floatrect = rect.getGlobalBounds();

	sf::RectangleShape rect2(sf::Vector2f(100.f,50.f));
	sf::RectangleShape rect3(sf::Vector2f(100.f,50.f));

	m_rectShape2 = rect2;
	m_rectShape3 = rect3;


	m_shape = shape;
	m_shape2 = shape2;
	m_rectShape = rect;
	m_shape3 = shape3;
	m_shape.setOrigin(10.f,10.f);
	m_shape2.setOrigin(10.f, 10.f);
	m_shape.setPosition(300.f, 0.f);
	m_rectShape.setOrigin(25.f, 10.f);
	m_rectShape.setPosition(400.f, 400.f);
	m_shape3.setOrigin(7.5f, 7.5f);
	m_shape3.setPosition(500, 400);

	m_rectShape2.setOrigin(50.f, 25.f);
	m_rectShape2.setPosition(500.f, 500.f);
	m_rectShape3.setOrigin(50.f, 25.f);
	m_rectShape3.setPosition(500.f, 610.f);
	mgr->AttachCollider(m_circle);
	mgr->AttachCollider(m_circle2);
	mgr->AttachCollider(m_rect);
	mgr->AttachCollider(m_circle3);
	mgr->AttachCollider(m_rect2);
	mgr->AttachCollider(m_rect3);

	m_DrawManager = p_pCore->m_DrawManager;
	m_player = p_pCore->m_player;
	m_spritemanager = nullptr;
	m_level = nullptr;
	m_GameObjMgr = nullptr;

	bStateRunning = false;

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


	if (m_spritemanager == nullptr)
	{
		m_spritemanager = new SpriteManager(m_DrawManager);
		if(!m_spritemanager ->Initialize("../data/sprites/"))
		{
			return false;
		}
	}
	m_GameObjMgr = new GameObjectManager(m_pInputManager);

	if (m_level == nullptr)
	{
		m_level = new Level(m_GameObjMgr);
		m_level->Load("../data/levels/level.txt", m_spritemanager, true);
		m_level->LoadFish("../data/anim/PlayerAnimIdle.txt", m_spritemanager, m_window);
	}

	return false;
}

void GameState::ExitState()
{
	cout << "GameState::ExitState" << endl;
}

bool GameState::Update(float p_DeltaTime)
{

	//Draw();
	HandleInput();
	
	m_circle->SetPositionX(m_shape.getPosition().x);
	m_circle->SetPositionY(m_shape.getPosition().y);
	m_circle2->SetPositionX(m_shape2.getPosition().x);
	m_circle2->SetPositionY(m_shape2.getPosition().y);

	m_rect->SetPositionX(m_rectShape.getPosition().x);
	m_rect->SetPositionY(m_rectShape.getPosition().y);
	m_circle3->SetPositionX(m_shape3.getPosition().x);
	m_circle3->SetPositionY(m_shape3.getPosition().y);

	m_rect2->SetPositionX(m_rectShape2.getPosition().x);
	m_rect2->SetPositionY(m_rectShape2.getPosition().y);
	m_rect3->SetPositionX(m_rectShape3.getPosition().x);
	m_rect3->SetPositionY(m_rectShape3.getPosition().y);


	mgr->CheckCollisionRectVsRect();
	m_rectShape.setPosition(m_rect->GetPosition());
	m_rectShape2.setPosition(m_rect2->GetPosition());
	

	mgr->CheckCollisionCircleVsCircle();
	m_shape.setPosition(m_circle->GetPosition());
	m_shape2.setPosition(m_circle2->GetPosition());

	//Just until I come to think about something else sf::FloatRect
	mgr->CheckCollisionRectVsCircle(m_floatrect);


	HandleInput();
	m_GameObjMgr->UpdateAllObjects(p_DeltaTime);


	return true;
}

void GameState::HandleInput()
{
		if(m_pInputManager->IsDownOnceK(sf::Keyboard::Num1))
	{
		m_pCore->m_StateManager->SetState("StartState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num2))
	{
		m_pCore->m_StateManager->SetState("GameState");
	}
	if (m_pInputManager->IsDownOnceK(sf::Keyboard::Num3))
	{
		m_pCore->m_StateManager->SetState("OptionState");
	}
	if (m_pInputManager->IsDownK(sf::Keyboard::L))
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
	
	m_DrawManager->ClearWindow();
	m_window->setView(m_GameObjMgr->m_pxPlayer->GetPlayerView() );
	m_level->Draw(m_DrawManager);
	m_DrawManager->DisplayWindow();






	m_pWindow->clear(sf::Color(0x11,0x22,0x33,0xff));
	m_pWindow->draw(m_shape);
	m_pWindow->draw(m_shape2);
	m_pWindow->draw(m_rectShape);
	m_pWindow->draw(m_shape3);
	m_pWindow->draw(m_rectShape2);
	m_pWindow->draw(m_rectShape3);

	/*sf::CircleShape shape(30.0f);
	m_pWindow->clear(sf::Color(0x11,0x22,0x33,0xff));
	m_pWindow->draw(shape);*/

}

bool GameState::IsType(const string &p_type)
{
	return p_type.compare("GameState") == 0;
}																																										//Sten
