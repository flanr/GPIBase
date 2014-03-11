//Collider.cpp

#include "stdafx.h"
#include "Collider.h"

Collider::Collider() 
	: m_position(0.f, 0.f)
	, m_extention(0.f,0.f)
{
	m_radius = 0.f;
	m_xParent = nullptr;
}
Collider::Collider(sf::Vector2f p_position, sf::Vector2f p_extension)
	: m_position(p_position)
	, m_extention(p_extension)
{

	////Temporary for testing
}

Collider::Collider(sf::Vector2f p_position, float p_radius)
	: m_radius(p_radius)
	, m_position(p_position)
{
}

sf::Vector2f Collider::GetPosition()
{
	return m_position;
}
void Collider::SetPositionX(float x)
{
	m_position.x = x;
}
void Collider::SetPositionY(float y)
{
	m_position.y = y;
}
bool Collider::OverlapRectVsRect(Collider* other, sf::Vector2f& offset)
{
	
	float A = m_extention.x *0.5f;
	float B = other->m_extention.x *0.5f;
	float C = m_position.x - other->m_position.x;

	float P = m_extention.y *0.5f;
	float Q = other->m_extention.y *0.5f;
	float Z = m_position.y - other->m_position.y;

	if (fabs(C) <= (A + B))
	{
		if (fabs(Z) <= (P + Q))
		{
			float deltaX = fabs(C) - (A + B);
			float deltaY = fabs(Z) - (P + Q);
			if (deltaX > deltaY)
			{
				if (m_position.x >= other->m_position.x)
				{
					deltaX = -deltaX;
				}
				offset.x = deltaX;
				other->m_position.x += deltaX/2.f;
				m_position.x += deltaX/2.f;
			}
			if (deltaY > deltaX)
			{
				if (m_position.y >= other->m_position.y)
				{
					deltaY = -deltaY;
				}
				offset.y = deltaY;
				other->m_position.y -= deltaY/2.f;
				m_position.y += deltaY/2.f;
			}
			return true;
		}
	}
	return false;
}

bool Collider::OverlapCircleVsCircle(Collider* other, sf::Vector2f& offset)
{
	float A = m_radius;
	float B = other->m_radius;
	float C = m_position.x - other->m_position.x;

	float Z = m_position.y - other->m_position.y;

	if ((fabs(C)*fabs(C)) + (fabs(Z) * fabs(Z)) <= (A + B) * (A + B))
	{

		//Unit vector pointing at other collider's position(B) from first collider position(A).
		//NOTE: NOT THE FLOATS A AND B, The VECTORS below. (a little confusing I know)
		sf::Vector2f vA(m_position);
		sf::Vector2f vB(other->m_position);
		sf::Vector2f vU = vB - vA;
		float lenght = (vU.x*vU.x + vU.y*vU.y);
		vU/=lenght;

		//The amount of overlap.
		float DeltaOverlap = sqrtf((fabs(C)*fabs(C)) + (fabs(Z) * fabs(Z))) - sqrtf((A + B) * (A + B));

		//offset is a vector the lenght of the overlap pointing at B from A
		offset = vU * DeltaOverlap;

		//seperate the colliders by half the offset each.
		other->m_position -= offset /2.f;
		m_position += offset /2.f;
		return true;

	}
	return false;
}

bool Collider::OverlapRectVsCircle(Collider* other, sf::Vector2f& offset)
{
	float W = m_extention.x*0.5f;
	float H = m_extention.y*0.5f;
	float R = other->m_radius;

	//The corner points
	sf::Vector2f topright = sf::Vector2f(m_position.x+W, m_position.y-H);
	sf::Vector2f botright = sf::Vector2f(m_position.x+W, m_position.y+H);
	sf::Vector2f topleft = sf::Vector2f(m_position.x-W, m_position.y-H);
	sf::Vector2f botleft = sf::Vector2f(m_position.x-W, m_position.y+H);

	//The closest points on the sides
	sf::Vector2f ClosestPointRight = ClosestPointOnLine(topright, botright, other->m_position);
	sf::Vector2f ClosestPointBottom = ClosestPointOnLine(botright, botleft, other->m_position);
	sf::Vector2f ClosestPointLeft = ClosestPointOnLine(botleft, topleft, other->m_position);
	sf::Vector2f ClosestPointTop = ClosestPointOnLine(topleft, topright, other->m_position);


	//Bulky deltas and their vectors
	float deltax = ClosestPointRight.x - other->m_position.x;
	float deltay = ClosestPointRight.y - other->m_position.y;
	float deltaxB = ClosestPointBottom.x - other->m_position.x;
	float deltayB = ClosestPointBottom.y - other->m_position.y;
	float deltaxL = ClosestPointLeft.x - other->m_position.x;
	float deltayL = ClosestPointLeft.y - other->m_position.y;
	float deltaxT = ClosestPointTop.x - other->m_position.x;
	float deltayT = ClosestPointTop.y - other->m_position.y;
	sf::Vector2f distanceright(fabs(deltax), fabs(deltay));
	sf::Vector2f distancerbottom(fabs(deltaxB), fabs(deltayB));
	sf::Vector2f distancerLeft(fabs(deltaxL), fabs(deltayL));
	sf::Vector2f distancerTop(fabs(deltaxT), fabs(deltayT));

	//Checking to see if the distance between each "closest points"
	// and the circle's center is less than the circle's radius.
	if ( distanceright.x < R && distanceright.y < R)	{	return true;	}
	if (distancerbottom.x < R && distancerbottom.y < R)	{	return true;	}
	if (distancerLeft.x < R && distancerLeft.y < R)		{	return true;	}
	if (distancerTop.x < R && distancerTop.y < R)		{	return true;	}

	//Is the circle within the rectangle?
	if (other->m_position.x < topright.x && other->m_position.y > topright.y
		&& other->m_position.x < botright.x && other->m_position.y < botright.y
		&& other->m_position.x > topleft.x && other->m_position.y > topleft.y
		&& other->m_position.x > botleft.x && other->m_position.y < botleft.y)	{	return true;	}

	return false;

}
const sf::Vector2f& Collider::ClosestPointOnLine(const sf::Vector2f& p_vA,const sf::Vector2f& p_vB,const sf::Vector2f& p_vPoint) {
	// Calculate unit vector from A->B
	sf::Vector2f vU=p_vB-p_vA;//former u
	float fLength=sqrt(vU.x*vU.x+vU.y*vU.y);
	vU/=fLength;

	// Vector from A->Point
	sf::Vector2f vAPoint=p_vPoint-p_vA;

	// Dot product between vU and vAPoint
	float fDot=vU.x*vAPoint.x+vU.y*vAPoint.y;

	// Length between two points that define the line
	fLength=sqrt(pow((p_vA.x-p_vB.x),2)+pow((p_vA.y-p_vB.y),2));

	// Clamp values
	fDot=Clamp(fDot,0.0f,fLength);

	return sf::Vector2f(vU.x*fDot+p_vA.x,vU.y*fDot+p_vA.y);
};


float Collider::GetRadius()
{
	return m_radius;
}
void Collider::SetRadius(float p_radius)
{
	m_radius = p_radius;
}

void Collider::SetPosition(const sf::Vector2f p_pos)
{
	m_position = p_pos;
}
void Collider::SetExtention(const sf::Vector2f p_ext)
{
	m_extention = p_ext;
}


void Collider::OnCollision(Collider* p_xOther, sf::Vector2f& p_Offset)
{
	//std::cout << "Collider::OnCollision: Collider A: "  << m_xParent->GetType() << " Collider B: " << p_xOther->m_xParent->GetType() << std::endl;
	/*if(m_xParent != nullptr)
	m_xParent->OnCollision(p_xOther->GetParent());*/
	if(m_xParent != nullptr && p_xOther != nullptr)
	{
		if (m_xParent->GetType() == "Player")
		{
			if (p_xOther->m_xParent->GetType() == "BrownBrick")
			{
				m_xParent->OnCollision(p_xOther->m_xParent, p_Offset);
			}
		}
		if (m_xParent->GetType() == "Player")
		{
			if (p_xOther->m_xParent->GetType() == "Enemy")
			{
				m_xParent->OnCollision(p_xOther->GetParent(), p_Offset);
			}
		}
		if(m_xParent->GetType() == "Enemy")
		{
			if(p_xOther->m_xParent->GetType() == "Player")
			{
				m_xParent->OnCollision(p_xOther->GetParent(), p_Offset);
				if(m_xParent->GetDestroyed() )
				{
					m_xParent = nullptr;
				}
			}
			else if (p_xOther->m_xParent->GetType() == "BrownBrick")
			{
				m_xParent->OnCollision(p_xOther->m_xParent, p_Offset);
			}
		}
	}
}

sf::RectangleShape Collider::PlayerRect()
{
	sf::RectangleShape playerrect;
	
	if (m_xParent->GetType() == "Player")
	{
		playerrect.setSize(m_xParent->GetCollider()->m_extention);
		playerrect.setOrigin(m_xParent->GetCollider()->m_extention.x/2, m_xParent->GetCollider()->m_extention.y/2);
		playerrect.setPosition(GetPosition().x, GetPosition().y);
		
	}
	return playerrect;
}

//           | 1 Player  |  2 Enemy  | 3 PowerUp
//    -------------------------------------------
// 1 Player  |    ---    |    xxx    |    xxx
//    -------------------------------------------
// 2 Enemy   |           |    ---    |    xxx
//    -------------------------------------------
// 3 powerup |           |           |    ---
//
// Collider.m_iLayer = ?
//
// CollisionManager har en vector med två intar det vill säga collisionpar.
// om någon av elementen i vectorerna har samma intar som collider A och B (tvärt om)
// TEX A = 1 (Player) B = 2 (Enemy), Bör pair<int,int>(1,2) finnas i vectorn (svar ja)
// 


