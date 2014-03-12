//Collider.h

#pragma once

enum Identity
{
	ETERRAIN,
	EPLAYER,
	EENEMY,
	ELIGHT
};

class GameObject;

class Collider
{
public:
	Collider();
	Collider(sf::Vector2f p_position, sf::Vector2f p_extension);
	Collider(sf::Vector2f p_position, float p_radius);

	bool OverlapRectVsRect(Collider* other, sf::Vector2f& offset);
	bool OverlapCircleVsCircle(Collider* other, sf::Vector2f& offset);
	bool OverlapRectVsCircle(Collider* other, sf::Vector2f& offset);
	const sf::Vector2f& ClosestPointOnLine(const sf::Vector2f& p_vA,const sf::Vector2f& p_vB,const sf::Vector2f& p_vPoint);

	sf::Vector2f GetPosition();
	void SetPosition(const sf::Vector2f p_pos);
	void SetExtention(const sf::Vector2f p_ext);
	void SetPositionX(float x);
	void SetPositionY(float y);

	void SetRadius(float p_radius);
	float GetRadius();

	sf::RectangleShape PlayerRect();
	
	////Temporary for testing
	void SetStatus(bool p_Collision);
	bool GetStatus();
	sf::Vector2f GetExtension(){return m_extention;};
	void OnCollision(Collider* p_xOther, sf::Vector2f& offset);
	GameObject* GetParent(){return m_xParent;};
	void SetParent(GameObject* p_xParent){m_xParent = p_xParent;};

private:
	sf::Vector2f m_position;
	sf::Vector2f m_extention;
	float m_radius;
	GameObject* m_xParent;
	//Temporary for testing

};