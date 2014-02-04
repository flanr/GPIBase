// FishObject.h
#pragma once


class Sprite;
class Collider;

class FishObject {
public:
	FishObject(Sprite *sprite = nullptr, Collider *collider = nullptr);

	void SetPosition(float x, float y);

	bool HasSprite() const;
	Sprite* GetSprite();

	bool HasCollider() const;
	Collider* GetCollider();

public:
	Sprite *m_sprite;
	Collider *m_collider;
};