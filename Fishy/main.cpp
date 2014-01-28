// main.cpp

#include "stdafx.h"

using namespace sf;

int _tmain(int argc, _TCHAR* argv[])
{

	RenderWindow window(VideoMode(1024,640), "Caption");

	CircleShape shape(10.0f);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::KeyReleased)
			{
	//			InputManager::OnKeyboard(event.key, true);
			}
			else if (event.type == Event::KeyPressed)
			{
	//			InputManager::OnKeyboard(event.key, true);
			}


		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			window.close();
		}

		
		window.clear(Color(0x11,0x22,0x33,0xff));
		window.draw(shape);
		window.display();
	}


	return 0;
}

/**

InputManager
StateManager
SoundManager
CollisionManager
GameObjectManager / EntityManager  /  ***
DrawManager
Engine / Core


SpriteManager
Sprite


*/