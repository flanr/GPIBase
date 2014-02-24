#include "stdafx.h"
#include "Camera.h"
#include "LightSource.h"


Camera::Camera(sf::Vector2f p_Size)
{
	m_CameraView.setSize(p_Size);
	m_FilterOn = false;

}


Camera::~Camera()
{
	if(m_FilterSprite != nullptr);
	{
		delete m_FilterSprite;
	}
	if(m_FilterTexture != nullptr);
	{
		delete m_FilterTexture;
	}
}

void Camera::Update(sf::Vector2f p_position, LightSource *light)
{
	//Move is better to use if there is a limit to where the camera can move.
	//Move(m_GameObjMgr->m_pxPlayer->GetVelocity() );

	SetCameraPosition(p_position);
	if(m_FilterOn)
	{
		m_FilterSprite->setPosition(p_position);
		CutOutFilter(light);
	}
}

void Camera::SetCameraPosition(sf::Vector2f p_position)
{
	m_CameraView.setCenter(p_position);
}
sf::View Camera::GetCameraView()
{
	return m_CameraView;
}

void Camera::Move(const sf::Vector2f &p_Offset)
{
	m_CameraView.move(p_Offset);
}

void Camera::Move(float p_OffsetX, float p_OffsetY)
{
	m_CameraView.move(p_OffsetX, p_OffsetY);
}

void Camera::SetCameraViewport(sf::FloatRect p_NewViewPort)
{
	m_CameraView.setViewport(p_NewViewPort);
}

sf::FloatRect Camera::GetCameraViewport()
{
	return m_CameraView.getViewport();
}
//At the moment only one layer can be added. need to add map<> to add multiple layers
void Camera::AddLayer()
{
	m_FilterTexture = new sf::RenderTexture();
	m_FilterTexture->create(m_CameraView.getSize().x, m_CameraView.getSize().y);
	m_FilterSprite = new sf::Sprite();
	m_FilterSprite->setTexture(m_FilterTexture->getTexture() );
	m_FilterSprite->setOrigin(m_FilterTexture->getTexture().getSize().x / 2.0f, m_FilterTexture->getTexture().getSize().y / 2.0f  );
}

//to toggle the effect on and off for testing.
void Camera::ToggleFilterOn(bool p_FilterOn)
{
	m_FilterOn = p_FilterOn;
}

bool Camera::GetFilterStatus()
{
	return m_FilterOn;
}

sf::Sprite* Camera::GetFilterSprite()
{
	return m_FilterSprite;
}

void Camera::CutOutFilter(LightSource *light)
{
	m_FilterTexture->clear();
	if(light->GetLightStatus() )
	{
		m_FilterTexture->draw(*light->GetLightCircle(), sf::BlendNone);
	}
	m_FilterTexture->display();
}