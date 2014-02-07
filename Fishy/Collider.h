//Collider.h

#pragma once

#include "stdafx.h"

class Collider
{
public:
	Collider();
	Collider(sf::Vector2f p_position, sf::Vector2f p_extension);
	Collider(sf::Vector2f p_position, float p_radius);

	bool OverlapRectVsRect(Collider* other, sf::Vector2f& offset);
	bool OverlapCircleVsCircle(Collider* other, sf::Vector2f& offset);
	bool OverlapRectVsCircle(Collider* other, sf::Vector2f& offset);

	sf::Vector2f GetPosition();
	void SetPositionX(float x);
	void SetPositionY(float y);
	sf::Vector2f m_position;
	sf::Vector2f m_extention;
private:

	float m_radius;
	//std::vector<Collider*> m_axColliders;

};