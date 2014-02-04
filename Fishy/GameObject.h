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
	GameObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite = nullptr);
	/*För GameObject med BoxCollider*/
	GameObject(sf::Vector2f p_xPosition, BoxCollider *p_pxCollider, sf::Sprite *p_pxSprite = nullptr);
	/*För GameObject med CircleCollider*/
	GameObject(sf::Vector2f p_xPosition, CircleCollider *p_pxcircleCollider, sf::Sprite *p_pxSprite = nullptr);
	~GameObject();
	

	sf::Vector2f GetPosition();
	void SetPosition(const sf::Vector2f &p_xPosition);

	bool HasSprite() const;
	sf::Sprite * GetSprite();
	//bool HasAnimSprite() const;
	//AnimSprite * GetAnimSprite();
	void SetNewSprite(sf::Sprite* p_pxNewSprite);

	bool HasBoxCollider() const;
	BoxCollider *GetBoxCollider();

	bool HasCircleCollider() const;
	CircleCollider *GetCircleCollider();

	void SetDestroyed(bool p_bDestroyed);
	bool GetDestroyed();

	virtual void Update();

protected:
	sf::Sprite *m_pxSprite;
	BoxCollider *m_pxCollider;
	CircleCollider *m_pxCircleCollider;
	sf::Vector2f m_xPosition;
	bool m_bDestroyed;
};