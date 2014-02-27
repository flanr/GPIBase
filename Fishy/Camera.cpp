#include "stdafx.h"
#include "Camera.h"
#include "LightSource.h"
#include "GameObjectManager.h"
#include "PlayerFishObject.h"


Camera::Camera(sf::Vector2f p_Size)
{
	m_CameraView.setSize(p_Size);
	m_FilterOn = false;
	m_FilterSprite = nullptr;
	m_FilterTexture = nullptr;

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

void Camera::Initialize(sf::RenderWindow *p_window, sf::Vector2f p_Position)
{
	SetCenterCamera(p_window->getView().getCenter() );
	AddLayer();
	Move(p_Position - GetCameraView().getCenter() );
	//m_FilterSprite->move( p_Position - GetCameraView().getCenter() /*+ sf::Vector2f(210, 210)*/ );
}

void Camera::Update(GameObjectManager *p_GameObjMgr)
{

	if( ( (p_GameObjMgr->m_pxPlayer->GetPosition().x - (GetCameraView().getSize().x / 2.0f) )<= -35) 
		&&  ( (p_GameObjMgr->m_pxPlayer->GetPosition().y - (GetCameraView().getSize().y / 2.0f) ) <= -20) )
	{
		Move(0.0f, 0.0f);
		m_FilterSprite->move(0.0f, 0.0f );
	}
	else if( ( (p_GameObjMgr->m_pxPlayer->GetPosition().x + (GetCameraView().getSize().x / 2.0f) ) >= 2460)
		&& ( (p_GameObjMgr->m_pxPlayer->GetPosition().y + (GetCameraView().getSize().y / 2.0f) ) >= 1340) )
	{
		Move(0.0f, 0.0f);
		m_FilterSprite->move(0.0f, 0.0f );
	}
	else if( ( (p_GameObjMgr->m_pxPlayer->GetPosition().x + (GetCameraView().getSize().x / 2.0f) ) >= 2460)
		&& ( (p_GameObjMgr->m_pxPlayer->GetPosition().y - (GetCameraView().getSize().y / 2.0f) ) <= -20) )
	{
		Move(0.0f, 0.0f);
		m_FilterSprite->move(0.0f, 0.0f );
	}
	else if( ( (p_GameObjMgr->m_pxPlayer->GetPosition().x - (GetCameraView().getSize().x / 2.0f) ) <= -35)
		&& ( (p_GameObjMgr->m_pxPlayer->GetPosition().y + (GetCameraView().getSize().y / 2.0f) ) >= 1340) )
	{
		Move(0.0f, 0.0f);
		m_FilterSprite->move(0.0f, 0.0f );
	}
	else if( (p_GameObjMgr->m_pxPlayer->GetPosition().x - (GetCameraView().getSize().x / 2.0f) )<= -35) 
	{
		Move(0.0f, p_GameObjMgr->m_pxPlayer->GetVelocity().y );
		m_FilterSprite->move(0.0f, p_GameObjMgr->m_pxPlayer->GetVelocity().y );
	}
	else if( (p_GameObjMgr->m_pxPlayer->GetPosition().y - (GetCameraView().getSize().y / 2.0f) ) <= -20) 
	{
		Move(p_GameObjMgr->m_pxPlayer->GetVelocity().x, 0.0f );
		m_FilterSprite->move(p_GameObjMgr->m_pxPlayer->GetVelocity().x, 0.0f );
	}
	else if( (p_GameObjMgr->m_pxPlayer->GetPosition().x + (GetCameraView().getSize().x / 2.0f) ) >= 2460)
	{
		Move(0.0f, p_GameObjMgr->m_pxPlayer->GetVelocity().y );
		m_FilterSprite->move(0.0f, p_GameObjMgr->m_pxPlayer->GetVelocity().y );
	}
	else if( (p_GameObjMgr->m_pxPlayer->GetPosition().y + (GetCameraView().getSize().y / 2.0f) ) >= 1340)
	{
		Move(p_GameObjMgr->m_pxPlayer->GetVelocity().x, 0.0f );
		m_FilterSprite->move(p_GameObjMgr->m_pxPlayer->GetVelocity().x, 0.0f );
	}
	else
	{
		Move(p_GameObjMgr->m_pxPlayer->GetVelocity() );
		m_FilterSprite->move(p_GameObjMgr->m_pxPlayer->GetVelocity() );
	}

	UpdateFilter(p_GameObjMgr);
}

void Camera::UpdateFilter(GameObjectManager *p_GameObjMgr)
{
	m_FilterTexture->setView(m_CameraView);

	GetFilterTexture()->clear();
	for( int i = 0; i < p_GameObjMgr->m_apxGameObject.size(); i++)
	{
		if(p_GameObjMgr->m_apxGameObject[i]->HasLight() )
		{
			/*if(fabs(p_GameObjMgr->m_apxGameObject[i]->GetPosition().x - GetCameraView().getCenter().x) 
				< (GetCameraView().getSize().x / 2.0f + p_GameObjMgr->m_apxGameObject[i]->GetLightSource()->GetLightCircle()->getRadius() ) 
				&&
				fabs(p_GameObjMgr->m_apxGameObject[i]->GetPosition().y - GetCameraView().getCenter().y) 
				< (GetCameraView().getSize().y / 2.0f + p_GameObjMgr->m_apxGameObject[i]->GetLightSource()->GetLightCircle()->getRadius()))*/
			{

				if(p_GameObjMgr->m_apxGameObject[i]->GetLightSource()->GetLightStatus() == true)
				{
					//checka om cirklar överlappar om dom gör det ta BlendAlpha??
					GetFilterTexture()->draw(*p_GameObjMgr->m_apxGameObject[i]->GetLightSource()->GetLightCircle(), sf::BlendNone );
				}

			}
		}
	}
	if(p_GameObjMgr->m_pxPlayer->GetLightSource()->GetLightStatus() == true )
	{
		GetFilterTexture()->draw(*p_GameObjMgr->m_pxPlayer->GetLightSource()->GetLightCircle(), sf::BlendNone );
	}
	GetFilterTexture()->display();
	

}
/* Do when you want to change the center/origin of the camera*/
void Camera::SetCenterCamera(sf::Vector2f p_position)
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
	//m_FilterSprite->setOrigin(m_CameraView.getCenter() );
	m_FilterSprite->setOrigin(m_FilterTexture->getTexture().getSize().x / 2.0f, m_FilterTexture->getTexture().getSize().y / 2.0f  );
	m_FilterSprite->setPosition(m_CameraView.getCenter() + sf::Vector2f(200, 60) );
}

sf::RenderTexture* Camera::GetFilterTexture()
{
	return m_FilterTexture;
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
