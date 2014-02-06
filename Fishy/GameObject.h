//GameObject.h

#pragma once

#include <string>

class Collider;

class GameObject
{
public:
	
	//GameObject();
	/*För GameObject utan collider*/
	/*GameObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite);*/
	/*För GameObject med Collider*/
	GameObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite = nullptr, Collider *p_pxCollider = nullptr);
	~GameObject();
	

	sf::Vector2f GetPosition();
	void SetPosition(const sf::Vector2f &p_xPosition);

	bool HasSprite() const;
	sf::Sprite * GetSprite();
	//bool HasAnimSprite() const;
	//AnimSprite * GetAnimSprite();
	//void SetNewSprite(sf::Sprite* p_pxNewSprite);

	bool HasCollider() const;
	Collider *GetCollider();

	void SetDestroyed(bool p_bDestroyed);
	bool GetDestroyed();

	virtual void Update();

protected:
	sf::Sprite *m_pxSprite;
	Collider *m_pxCollider;
	sf::Vector2f m_xPosition;
	bool m_bDestroyed;
};