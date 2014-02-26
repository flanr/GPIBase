// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "SDKDDKVer.h" // Good compile thing yes


//

#pragma warning(disable:4099)
#define SFML_STATIC
#if defined(_DEBUG)
#pragma comment(lib, "sfml-window-s-d.lib")
#pragma comment(lib, "sfml-graphics-s-d.lib")
#pragma comment(lib, "sfml-system-s-d.lib")
#pragma comment(lib, "sfml-audio-s-d.lib")
#else
#pragma comment(lib, "sfml-window-s.lib")
#pragma comment(lib, "sfml-graphics-s.lib")
#pragma comment(lib, "sfml-system-s.lib")
#pragma comment(lib, "sfml-audio-s.lib")
#endif

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Audio.hpp>


#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>


//

#include "Button.h"
#include "InputManager.h"
#include "DrawManager.h"
#include <iostream>
#include "GameState.h"
#include "StartState.h"
#include "OptionState.h"

#include "Geographics.h"
#include "Collider.h"
#include "Level.h"
#include "CollisionManager.h"
#include "FishObject.h"


#include "GameObject.h"

#include "StateManager.h"

#include "Core.h"


// TODO: reference additional headers your program requires here.
