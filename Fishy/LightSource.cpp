#include "stdafx.h"
#include "LightSource.h"

LightSource::LightSource()
{
}

LightSource::LightSource(sf::Vector2f p_Position, float p_Radius )
{
	//m_Position = p_Position;
	m_LightRadius = p_Radius;
	m_LightTexture = new sf::RenderTexture();
	m_LightTexture->create(m_LightRadius * 2.0f, m_LightRadius * 2.0f);
	CreateCircle();
	m_LightCircle = new sf::Sprite();
	m_LightCircle->setTexture(m_LightTexture->getTexture(), true);
	SetOrigin(sf::Vector2f(m_LightTexture->getTexture().getSize().x / 2.0f, m_LightTexture->getTexture().getSize().y / 2.0f) );
	SetPosition(p_Position);

	m_LightOn = false;

	//m_light->SetOrigin(sf::Vector2f(iX, iY) );
	//m_light->SetPosition( sf::Vector2f(iX, iY) );



}

//skapa lightscource i Player och testa så den skär där player simmar
//och flytt blackTexture till camera class?
//toggle black filter on and off i camera classen
//check for circlecut == true i så fall Cut circle in black filter i camera class? tex i fall fler saker har ljus

LightSource::~LightSource(void)
{
	if(m_LightCircle != nullptr);
	{
		delete m_LightCircle;
	}
	if(m_LightTexture != nullptr);
	{
		delete m_LightTexture;
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
	m_LightCircle->setPosition(p_Position);
}
sf::Vector2f LightSource::GetPosition()
{
	return m_LightCircle->getPosition();
}

void LightSource::SetOrigin(const sf::Vector2f &p_Origin)
{
	m_LightCircle->setOrigin(p_Origin);
}

void LightSource::Move(const sf::Vector2f &p_Offset)
{
	m_LightCircle->move(p_Offset);
}

void LightSource::Move(float p_OffsetX, float p_OffsetY)
{
	m_LightCircle->move(p_OffsetX, p_OffsetY);
}

sf::Sprite* LightSource::GetLightCircle()
{
	return m_LightCircle;
}
