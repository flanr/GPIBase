// main.cpp
// Git

#include "stdafx.h"

using namespace sf;
//using namespace sf;

int _tmain(int argc, _TCHAR* argv[])
{
	Core core;
	if (core.Initialize())
	{
		core.Run();
	}

	core.Cleanup();

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

*****************************************************************detta under funkade som det ska*_****************************************
RenderWindow window(VideoMode(1024,640), "Caption");
	

	CircleShape shape(10.0f);
	
	sf::Event event;
	InputManager InputMgr;
	while (window.isOpen())
	{
		window.setKeyRepeatEnabled(true);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			
			InputMgr.UpdateEvents(event);
		}
		if (InputMgr.IsDownOnceK(sf::Keyboard::Key::A))
		{
			std::cout << "IsDownOnce\n";
		}
		if(InputMgr.IsDownK(sf::Keyboard::Key::A))
		{
			std::cout << "IsDown\n";
		}
		if (InputMgr.IsDown(MB_LEFT))
		{
			std::cout << "IsDownMouse\n";
		}
		if (InputMgr.IsDownOnce(MB_RIGHT))
		{
			std::cout << "IsDownOnceMouse\n";
		}
		window.clear(Color(0x11,0x22,0x33,0xff));
		window.draw(shape);
		window.display();
		InputMgr.PostUpdateKeyboard();
		InputMgr.PostUpdateMouse();
	
	}

*/