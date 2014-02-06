// PlayerFishObject.h
#pragma once

#include "FishObject.h"
#include "InputManager.h"

class Sprite;
class Collider;
class InputManager;

class PlayerFishObject : public FishObject {
public:
		PlayerFishObject(sf::Sprite *sprite, Collider* collider = nullptr);

		void Update(float deltatime);





private:

};
