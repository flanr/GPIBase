// PlayerFishObject.cpp

#pragma once

#include "FishObject.h"
#include "stdafx.h"
#include "PlayerFishObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "GameObject.h"

PlayerFishObject::PlayerFishObject(sf::Sprite *sprite , Collider* collider )
	: GameObject(m_xPosition, m_pxSprite, m_pxCollider)
{

};

void PlayerFishObject::Update(float deltatime)
{

};