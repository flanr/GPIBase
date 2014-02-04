//GameObject.h

#pragma once

#include <string>


class Sprite;
class BoxCollider;
class CircleCollider;

class GameObject
{
public:
	
	GameObject();
	/*För GameObject utan collider*/
	GameObject(sf::Vector2f p_xPosition, Sprite *p_pxSprite = nullptr);
	/*För GameObject med BoxCollider*/
	GameObject(sf::Vector2f p_xPosition, BoxCollider *p_pxCollider, Sprite *p_pxSprite = nullptr);
	/*För GameObject med CircleCollider*/
	GameObject(sf::Vector2f p_xPosition, CircleCollider *p_pxcircleCollider, Sprite *p_pxSprite = nullptr);
	~GameObject();
	

	const sf::Vector2f &GetPosition() const;
	void SetPosition(const sf::Vector2f &p_xPosition);

	bool HasSprite() const;
	Sprite * GetSprite();
	//bool HasAnimSprite() const;
	//AnimSprite * GetAnimSprite();
	void SetNewSprite(Sprite* p_pxNewSprite);

	bool HasCollider() const;
	BoxCollider *GetCollider();

	bool HasCircleCollider() const;
	CircleCollider *GetCircleCollider();

	void SetDestroyable(bool p_bDestroyable);
	bool GetDestroyable();

	virtual void Update();

protected:
	Sprite *m_pxSprite;
	BoxCollider *m_pxCollider;
	CircleCollider *m_pxCircleCollider;
	sf::Vector2f m_xPosition;
	bool m_bDestroyable;
};