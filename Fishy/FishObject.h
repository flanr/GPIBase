// FishObject.h
#pragma once

class Collider;

class FishObject {
public:
	FishObject(sf::Sprite *sprite, Collider *collider = nullptr);

	const sf::Vector2f &GetPosition() const;
	void SetPosition(const sf::Vector2f &position);

	sf::Sprite *HasSprite();
	sf::Sprite *GetSprite();

	bool HasCollider() const;
	Collider* GetCollider();

public:
	sf::Sprite *m_sprite;
	Collider *m_collider;
	sf::Vector2f m_position;
};