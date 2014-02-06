// PlayerFishObject.cpp

#pragma once

#include "FishObject.h"
#include "stdafx.h"
#include "PlayerFishObject.h"
#include "Sprite.h"
#include "InputManager.h"

PlayerFishObject::PlayerFishObject(sf::Sprite *sprite , Collider* collider )
	: FishObject(sprite, collider)
{

};

void PlayerFishObject::Update(float deltatime)
{

};