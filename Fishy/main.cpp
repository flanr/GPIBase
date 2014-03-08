// main.cpp
// Git

#include "stdafx.h"
#include <random>
using namespace sf;

int _tmain(int argc, _TCHAR* argv[])
{
	srand((int)time(nullptr));
	srand(time(nullptr));
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


	
	}

*/