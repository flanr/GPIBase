// FishObject
#include "stdafx.h"
#include "FishObject.h"
#include "Sprite.h"
#include "InputManager.h"


FishObject::FishObject(Sprite *sprite, Collider *collider) 
: m_sprite(sprite)
, m_collider(collider)
{

};

void FishObject::SetPosition(float x, float y){
	
};

bool FishObject::HasSprite() const {
	return m_sprite != nullptr;
};

Sprite* FishObject::GetSprite() {
	return m_sprite;
};

bool FishObject::HasCollider() const{
	return m_collider != nullptr;
};
Collider* FishObject::GetCollider(){
	return m_collider;
};