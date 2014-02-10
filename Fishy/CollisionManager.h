// CollisionManager.h

#pragma once

class Collider;

class CollisionManager
{
public:
	CollisionManager();
	
	void AttachCollider(Collider* p_collider);
	void Cleanup();

	void CheckCollisionRectVsRect();
	void CheckCollisionCircleVsCircle();
	void CheckCollisionRectVsCircle(sf::FloatRect f_rect);

	


private:
	std::vector<Collider*> m_axCircleColliders;
	std::vector<Collider*> m_axRectColliders;

};