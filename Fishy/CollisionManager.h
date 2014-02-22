// CollisionManager.h

#pragma once

class Collider;

class CollisionManager
{
	friend class EnemyFishObject;
public:
	CollisionManager();
	
	void AttachCollider(Collider* p_collider);
	void Cleanup();

	void CheckCollisionRectVsRect();
	void CheckCollisionCircleVsCircle();
	void CheckCollisionRectVsCircle();

	void RemoveEnemyCollider();
	bool GetPlayerVsEnemy() {return b_playerVsenemy; }
	void SetPlayerVsEnemy(bool value) {b_playerVsenemy = value; }


private:
	std::vector<Collider*> m_axCircleColliders;
	std::vector<Collider*> m_axRectColliders;
	bool b_playerVsenemy;
	bool b_enemyVsLight;
	int m_enemynr;
};