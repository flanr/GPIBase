// FishObject
#include "stdafx.h"
#include "FishObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Vector2.h"


FishObject::FishObject(sf::Sprite *sprite, Collider *collider) 
: m_sprite(sprite)
, m_collider(collider)
{

};

const sf::Vector2f &FishObject::GetPosition() const{
	return  m_position;
};

void FishObject::SetPosition(const sf::Vector2f &position){
	m_position = position;
};

bool FishObject::HasSprite() const {
	return m_sprite != nullptr;
};

sf::Sprite* FishObject::GetSprite() {
	return m_sprite;
};

bool FishObject::HasCollider() const{
	return m_collider != nullptr;
};
Collider* FishObject::GetCollider(){
	return m_collider;
};