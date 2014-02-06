//Collider.cpp

#include "stdafx.h"
#include "Collider.h"

Collider::Collider() 
 : m_position(0.f, 0.f)
 , m_extention(0.f,0.f)
{
 m_radius = 0.f;
}
Collider::Collider(sf::Vector2f p_position, sf::Vector2f p_extension)
 : m_position(p_position)
 , m_extention(p_extension)
{
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
 float A = m_extention.x * 0.5f;
 float B = other->m_extention.x * 0.5f;
 float C = m_position.x - other->m_position.x;

 float P = m_extention.y *0.5f;
 float Q = other->m_extention.y * 0.5f;
 float Z = m_position.y - other->m_position.y;

 if (fabs(C) < (A + B))
 {
  if (fabs(Z) < (P + Q))
  {
   float deltaX = fabs(C) - (A + B);
   float deltaY = fabs(Z) - (P + Q);
   if (deltaX > deltaY)
   {
    if (m_position.x < other->m_position.x)
    {
     deltaX = -deltaX;
    }
    offset.x = deltaX;
    other->m_position.x += deltaX; //Wonder if this is nesicarry when both objects check. they could expell each other a little too much...
   }
   if (deltaY > deltaX)
   {
    if (m_position.y < other->m_position.y)
    {
     deltaY = -deltaY;
    }
    offset.y = deltaY;
    other->m_position.y += deltaY; // same here of course...
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


  float deltaX = fabs(C) - (A + B);
  float deltaY = fabs(Z) - (A + B);
  if (deltaX > deltaY)
  {
   if (m_position.x < other->m_position.x)
   {
    deltaX = -deltaX;
   }
   offset.x = deltaX;
  }
  if (deltaY > deltaX)
  {
   if (m_position.y < other->m_position.y)
   {
    deltaY = -deltaY;
   }
   offset.y = deltaY;
  }
  return true;

 }
 return false;
}

bool Collider::OverlapRectVsCircle(Collider* other, sf::Vector2f& offset)
{
 float W = m_extention.x * 0.5;
 float R = other->m_radius;
 float distanceX = m_position.x - other->m_position.x;

 float H = m_extention.y * 0.5;
 float distanceY = m_position.y - other->m_position.y;

 if((distanceX * distanceX) + (distanceY * distanceY) < (R * R) + (W*W + H*H))
 {
  float diffX = (distanceX * distanceX) + (distanceY * distanceY) + (R * R) - ((W*W + H*H));
  return true;
 }
 return false;
}