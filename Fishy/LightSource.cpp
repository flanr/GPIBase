#include "stdafx.h"
#include "LightSource.h"

LightSource::LightSource()
{
}

LightSource::LightSource(sf::Vector2f p_Position, float p_Radius )
{
	//m_Position = p_Position;
	m_LightRadius = p_Radius;
	m_Circle = new sf::CircleShape(p_Radius);
	m_Circle->setPosition(p_Position);
	m_LightTexture = new sf::RenderTexture();
	m_LightTexture->create(m_LightRadius * 2.0f, m_LightRadius * 2.0f);
	CreateCircle();
	//m_LightCircle = new sf::Sprite();
	//m_LightCircle->setTexture(m_LightTexture->getTexture(), true);
	//SetOrigin(sf::Vector2f(m_LightTexture->getTexture().getSize().x / 2.0f, m_LightTexture->getTexture().getSize().y / 2.0f) );
	//SetPosition(p_Position);

	m_LightOn = true;
}

LightSource::~LightSource(void)
{
	if(m_LightTexture != nullptr);
	{
		delete m_LightTexture;
	}
	if(m_Circle != nullptr);
	{
		delete m_Circle;
	}
	
}

//Creates multiple circles one ontop the other to create an effect
void LightSource::CreateCircle()
{
	m_LightTexture->clear();

	for(unsigned int i = 0; i < m_LightRadius / 2.0f; ++i)
	{
		sf::CircleShape tempCircle(m_LightRadius-(i*2.f));
		tempCircle.setOrigin(sf::Vector2f(m_LightRadius-(i*2.f), m_LightRadius-(i*2.f)));
		tempCircle.setFillColor(sf::Color(0, 0, 0, 255-(i*2)));
		tempCircle.setPosition(sf::Vector2f(m_LightRadius, m_LightRadius));

		m_LightTexture->draw(tempCircle, sf::BlendNone);
	}
	m_LightTexture->display();
	m_Circle->setTexture(&m_LightTexture->getTexture() );
	SetOrigin(sf::Vector2f(m_Circle->getTextureRect().width / 2.0f, m_Circle->getTextureRect().height / 2.0f) );
}
void LightSource::SetStrength()
{
}
void LightSource::SetRadius()
{
}

void LightSource::ToggleLightOn(bool p_LightOn)
{
	m_LightOn = p_LightOn;
}

bool LightSource::GetLightStatus()
{
	return m_LightOn;
}

void LightSource::SetPosition(sf::Vector2f p_Position)
{
	m_Circle->setPosition(p_Position);
}
sf::Vector2f LightSource::GetPosition()
{
	return m_Circle->getPosition();
}

void LightSource::SetOrigin(const sf::Vector2f &p_Origin)
{
	m_Circle->setOrigin(p_Origin);
}

void LightSource::Move(const sf::Vector2f &p_Offset)
{
	m_Circle->move(p_Offset);
}

void LightSource::Move(float p_OffsetX, float p_OffsetY)
{
	m_Circle->move(p_OffsetX, p_OffsetY);
}

sf::CircleShape* LightSource::GetLightCircle()
{
	return m_Circle;
}
