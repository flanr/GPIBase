// CollisionManager.cpp
#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	m_axRectColliders;
	m_axCircleColliders;
}

void CollisionManager::AttachCollider(Collider* p_collider)
{
	if(p_collider->GetRadius() <= 0) //Collider is not a circle
	{
		m_axRectColliders.push_back(p_collider);
	}
	else
	{
		m_axCircleColliders.push_back(p_collider);
	}
}

void CollisionManager::CheckCollisionRectVsRect()
{
	sf::Vector2f offset;
	for (int i = 0; i < m_axRectColliders.size()-1; i++)
	{
		for (int j = i+1; j < m_axRectColliders.size(); j++)
		{
			if (m_axRectColliders[i]->OverlapRectVsRect(m_axRectColliders[j], offset))
			{
				std::cout << "Collision!\n";
				m_axRectColliders[i]->SetPosition(m_axRectColliders[i]->GetPosition() += offset);
				m_axRectColliders[j]->SetPosition(m_axRectColliders[j]->GetPosition() += -offset);
			}
		}
	}
}

void CollisionManager::CheckCollisionCircleVsCircle()
{
	sf::Vector2f offset;
	for (int i = 0; i < m_axCircleColliders.size()-1; i++)
	{
		for (int j = i+1; j < m_axCircleColliders.size(); j++)
		{
			if (m_axCircleColliders[i]->OverlapCircleVsCircle(m_axCircleColliders[j], offset))
			{
				std::cout << "Collision!\n";
				/*m_axRectColliders[i]->SetPosition(m_axRectColliders[i]->GetPosition() += offset);
				m_axRectColliders[j]->SetPosition(m_axRectColliders[j]->GetPosition() += -offset);*/
			}
		}
	}
	//position update here
}

void CollisionManager::CheckCollisionRectVsCircle(sf::FloatRect f_rect)
{
	sf::Vector2f offset;
	for (int i = 0; i < m_axRectColliders.size() - 1; i++)
	{
		for (int j = 0; j < m_axCircleColliders.size(); j++)
		{
			if (m_axRectColliders[i]->OverlapRectVsCircle(m_axCircleColliders[j], offset, f_rect))
			{
				std::cout << "Collision!\n";
			}
		}
	}
}

void CollisionManager::Cleanup()
{
	auto it = m_axRectColliders.begin();
	while (it != m_axRectColliders.end())
	{
		delete (*it);
		it++;
	}
	m_axRectColliders.clear();

	auto it2 = m_axCircleColliders.begin();
	while (it2 != m_axCircleColliders.end())
	{
		delete (*it2);
		it2++;
	}
	m_axCircleColliders.clear();
}

