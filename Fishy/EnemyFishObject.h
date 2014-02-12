// EnemyFishObject
#pragma once

#include "GameObject.h"

class Collider;

class EnemyFishObject : public GameObject
{
public:
	//EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_xSprite);
	EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_xSprite, Collider* p_xCollider);
	~EnemyFishObject();

	void SetSpawnPosition(sf::Vector2f p_xSpawnPosition);
	sf::Vector2f GetSpawnPosition(sf::Vector2f p_xSpawnPosition);
	void SetAttractRadius(float p_fAttractRadius);
	
	void Update(float deltatime);

private:
	sf::Vector2f m_xSpawnPosition;

};