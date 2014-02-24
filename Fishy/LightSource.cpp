#include "stdafx.h"
#include "LightSource.h"

LightSource::LightSource()
{
}

LightSource::LightSource(sf::Vector2f p_Position, sf::Vector2f p_Size, float p_Radius )
{
	m_Position = p_Position;
	
	m_BlacklayerTexture = new sf::RenderTexture();
	m_BlacklayerTexture->create(1024, 640);
	m_BlackLayerSprite = new sf::Sprite();
	m_BlackLayerSprite->setTexture(m_BlacklayerTexture->getTexture() );
	m_LightRadius = p_Radius;
	m_LightTexture = new sf::RenderTexture();
	m_LightTexture->create(m_LightRadius * 2.0f, m_LightRadius * 2.0f);
	m_LightCutCircle = new sf::Sprite();
	m_LightCutCircle->setTexture(m_LightTexture->getTexture(), true);
	SetPosition(p_Position);
    m_LightCutCircle->setOrigin(30.f, 30.f);

	m_LightSourceOn = true;
}

&	//skapa lightscource i Player och testa så den skär där player simmar
	//och flytt blackTexture till camera class?
	//toggle black filter on and off i camera classen
	//check for circlecut == true i så fall Cut circle in black filter i camera class? tex i fall fler saker har ljus

LightSource::~LightSource(void)
{
}

//to toggle the effect on and off for testing.
void LightSource::ToggleOn(bool p_CircleOn)
{
	m_LightSourceOn = p_CircleOn;
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
void LightSource::CutOutCircle()
{
	if(m_LightSourceOn)
	{
		m_BlacklayerTexture->clear();
		m_BlacklayerTexture->draw(*m_LightCutCircle, sf::BlendNone);
		m_BlacklayerTexture->display();
	}
}

void LightSource::SetPosition(sf::Vector2f p_Position)
{
	m_LightCutCircle->setPosition(p_Position);
}
sf::Vector2f LightSource::GetPosition()
{
	return m_LightCutCircle->getPosition();
}

void LightSource::SetOrigin(const sf::Vector2f &p_Origin)
{
	m_LightCutCircle->setOrigin(p_Origin);
}

void LightSource::Move(const sf::Vector2f &p_Offset)
{
	m_LightCutCircle->move(p_Offset);
}

void LightSource::Move(float p_OffsetX, float p_OffsetY)
{
	m_LightCutCircle->move(p_OffsetX, p_OffsetY);
}

sf::Sprite* LightSource::GetBlackLayerSprite()
{
	return m_BlackLayerSprite;
}