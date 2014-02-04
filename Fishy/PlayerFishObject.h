// PlayerFishObject.h
#pragma once

#include "FishObject.h"
#include "InputManager.h"

class Sprite;
class Collider;

class PlayerFishObject : public FishObject {
public:
		PlayerFishObject(Sprite* sprite = nullptr, Collider* collider = nullptr);

		void Update(float deltatime);

};
