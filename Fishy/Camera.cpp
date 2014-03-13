#include "stdafx.h"
#include "Camera.h"
#include "LightSource.h"
#include "GameObjectManager.h"
#include "PlayerFishObject.h"


Camera::Camera(sf::Vector2f p_Size)
{
	m_CameraView.setSize(p_Size);
	m_FilterOn = true;
	m_FilterSprite = nullptr;
	m_FilterTexture = nullptr;
	m_MovingXAxis = false;
	m_MovingYAxis = false;
	m_IsZoomingOut = false;
	m_ZoomStrength = 0.0;
	m_TotalZoom = 1.0f;
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
	m_FilterSprite->setPosition(p_Position );
}

void Camera::Update(GameObjectManager *p_GameObjMgr, Level *p_Level)
{
	//m_MovingXAxis = false;
	//m_MovingYAxis = false;
	//if( ( (p_GameObjMgr->m_pxPlayer->GetPosition().x - (GetCameraView().getSize().x / 2.0f) )<= -35) 
	//	&&  ( (p_GameObjMgr->m_pxPlayer->GetPosition().y - (GetCameraView().getSize().y / 2.0f) ) <= -20) )
	//{
	//	Move(0.0f, 0.0f);
	//	m_FilterSprite->move(0.0f, 0.0f );
	//	m_MovingXAxis = false;
	//	m_MovingYAxis = false;
	//}
	//else if( ( (p_GameObjMgr->m_pxPlayer->GetPosition().x + (GetCameraView().getSize().x / 2.0f) ) >= 2460)
	//	&& ( (p_GameObjMgr->m_pxPlayer->GetPosition().y + (GetCameraView().getSize().y / 2.0f) ) >= 1340) )
	//{
	//	Move(0.0f, 0.0f);
	//	m_FilterSprite->move(0.0f, 0.0f );
	//	m_MovingXAxis = false;
	//	m_MovingYAxis = false;
	//}
	//else if( ( (p_GameObjMgr->m_pxPlayer->GetPosition().x + (GetCameraView().getSize().x / 2.0f) ) >= 2460)
	//	&& ( (p_GameObjMgr->m_pxPlayer->GetPosition().y - (GetCameraView().getSize().y / 2.0f) ) <= -20) )
	//{
	//	Move(0.0f, 0.0f);
	//	m_FilterSprite->move(0.0f, 0.0f );
	//	m_MovingXAxis = false;
	//	m_MovingYAxis = false;
	//}
	//else if( ( (p_GameObjMgr->m_pxPlayer->GetPosition().x - (GetCameraView().getSize().x / 2.0f) ) <= -35)
	//	&& ( (p_GameObjMgr->m_pxPlayer->GetPosition().y + (GetCameraView().getSize().y / 2.0f) ) >= 1340) )
	//{
	//	Move(0.0f, 0.0f);
	//	m_FilterSprite->move(0.0f, 0.0f );
	//	m_MovingXAxis = false;
	//	m_MovingYAxis = false;
	//}
	//else
	//{
	//	if( (p_GameObjMgr->m_pxPlayer->GetPosition().x - (GetCameraView().getSize().x / 2.0f) )<= -35) 
	//	{
	//		SetPositionY(p_GameObjMgr->m_pxPlayer->GetPosition().y );
	//		//Move(0.0f, p_GameObjMgr->m_pxPlayer->GetVelocity().y );
	//		m_FilterSprite->setPosition(m_FilterSprite->getPosition().x, p_GameObjMgr->m_pxPlayer->GetPosition().y );
	//		//m_FilterSprite->move(0.0f, p_GameObjMgr->m_pxPlayer->GetVelocity().y );
	//		m_MovingXAxis = false;
	//		m_MovingYAxis = true;
	//	}
	//	else if( (p_GameObjMgr->m_pxPlayer->GetPosition().y - (GetCameraView().getSize().y / 2.0f) ) <= -20) 
	//	{
	//		SetPositionX(p_GameObjMgr->m_pxPlayer->GetPosition().x );
	//		//Move(p_GameObjMgr->m_pxPlayer->GetVelocity().x, 0.0f );
	//		m_FilterSprite->setPosition(p_GameObjMgr->m_pxPlayer->GetPosition().x, m_FilterSprite->getPosition().y );
	//		//m_FilterSprite->move(p_GameObjMgr->m_pxPlayer->GetVelocity().x, 0.0f );
	//		m_MovingXAxis = true;
	//		m_MovingYAxis = false;
	//	}
	//	else if( (p_GameObjMgr->m_pxPlayer->GetPosition().x + (GetCameraView().getSize().x / 2.0f) ) >= 2460)
	//	{
	//		SetPositionY(p_GameObjMgr->m_pxPlayer->GetPosition().y );
	//		//Move(0.0f, p_GameObjMgr->m_pxPlayer->GetVelocity().y );
	//		m_FilterSprite->setPosition(m_FilterSprite->getPosition().x, p_GameObjMgr->m_pxPlayer->GetPosition().y );
	//		//m_FilterSprite->move(0.0f, p_GameObjMgr->m_pxPlayer->GetVelocity().y );
	//		m_MovingXAxis = false;
	//		m_MovingYAxis = true;
	//	}
	//	else if( (p_GameObjMgr->m_pxPlayer->GetPosition().y + (GetCameraView().getSize().y / 2.0f) ) >= 1340)
	//	{
	//		SetPositionX(p_GameObjMgr->m_pxPlayer->GetPosition().x );
	//		//Move(p_GameObjMgr->m_pxPlayer->GetVelocity().x, 0.0f );
	//		m_FilterSprite->setPosition(p_GameObjMgr->m_pxPlayer->GetPosition().x, m_FilterSprite->getPosition().y );
	//		//m_FilterSprite->move(p_GameObjMgr->m_pxPlayer->GetVelocity().x, 0.0f );
	//		m_MovingXAxis = true;
	//		m_MovingYAxis = false;
	//	}
	//	else
	//	{
	//		SetPosition(p_GameObjMgr->m_pxPlayer->GetPosition() );
	//		//Move(p_GameObjMgr->m_pxPlayer->GetVelocity() );
	//		m_FilterSprite->setPosition(p_GameObjMgr->m_pxPlayer->GetPosition() );
	//		//m_FilterSprite->move(p_GameObjMgr->m_pxPlayer->GetVelocity() );
	//		m_MovingXAxis = true;
	//		m_MovingYAxis = true;
	//	}
	//}
	if(IsZoomingOut() )
	{
		for(int i = 0UL; i < p_GameObjMgr->m_apxGameObject.size(); i++)
		{
			if( !(p_GameObjMgr->m_apxGameObject[i]->GetLevelLayer() == MIDDLEGROUND || p_GameObjMgr->m_apxGameObject[i]->GetLevelLayer() == FOREGROUND) )
			{
				p_GameObjMgr->m_apxGameObject[i]->GetSprite()->setScale(p_GameObjMgr->m_apxGameObject[i]->GetSprite()->getScale() * GetZoomStrength());
			}
		}
		m_FilterSprite->setScale(m_FilterSprite->getScale() * GetZoomStrength() );
		m_TotalZoom *= GetZoomStrength();
		//cout << "TotalZoom: " << m_TotalZoom << endl;
		if(p_GameObjMgr->m_pxPlayer->HasGrown() == false)
		{
			SetZoomingOut(false);
		}
	}
	SetPosition(p_GameObjMgr->m_pxPlayer->GetPosition() );
	m_FilterSprite->setPosition(p_GameObjMgr->m_pxPlayer->GetPosition() );
	m_MovingXAxis = true;
	m_MovingYAxis = true;

	UpdateFilter(p_GameObjMgr, p_Level);
}

void Camera::UpdateFilter(GameObjectManager *p_GameObjMgr, Level *p_Level)
{
	m_FilterTexture->setView(m_CameraView);
	//Opacity = 0.
	GetFilterTexture()->clear(sf::Color(0,0,0,0) );
	//Opacity starts at this position
	const int OPACITYSTART = 3000; //p_Level->GetHeight() / 3.0f;
	//OpacityDepth == how fast the opacity change 
	const int OPACITYDEPTH = 2000;
	//OPACITYMAX is the opacity of the darkest part
	const int OPACITYMAX = 245;

	if(p_GameObjMgr->m_pxPlayer->GetPosition().y > OPACITYSTART )
	{
		int OpacityLevel = 0;
		int OpacityCounter = 0;
		while( (OpacityLevel < (p_GameObjMgr->m_pxPlayer->GetPosition().y - OPACITYSTART) ) && OpacityCounter < OPACITYMAX )
		{
			//Divide OpacityDepth by 256 because opacity is 0 - 255, so we dived it in 256 parts.
			OpacityLevel += (OPACITYDEPTH / 256);
			OpacityCounter++;
		}

		//cout << "OpacityCounter: " << OpacityCounter << endl;

		//Clear the screen with OpacityCounter.
		GetFilterTexture()->clear(sf::Color(0,0,0, OpacityCounter) );
	}

	for( int i = 0; i < p_GameObjMgr->m_apxGameObject.size(); i++)
	{
		if(p_GameObjMgr->m_apxGameObject[i]->HasLight() )
		{
			{
				if(p_GameObjMgr->m_apxGameObject[i]->GetLightSource()->GetLightStatus() == true)
				{
					//checka om cirklar överlappar om dom gör det ta BlendAlpha??
					GetFilterTexture()->draw(*p_GameObjMgr->m_apxGameObject[i]->GetLightSource()->GetLightCircle(), sf::BlendMultiply );
				}
			}
		}
	}
	if(p_GameObjMgr->m_pxPlayer->GetLightSource()->GetLightStatus() == true )
	{
		GetFilterTexture()->draw(*p_GameObjMgr->m_pxPlayer->GetLightSource()->GetLightCircle(), sf::BlendMultiply);
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

void Camera::SetPosition(const sf::Vector2f &p_Position)
{
	m_CameraView.setCenter(p_Position);
}

void Camera::SetPositionY(float p_OffsetY)
{
	m_CameraView.setCenter(m_CameraView.getCenter().x, p_OffsetY);
}

void Camera::SetPositionX(float p_OffsetX)
{
	m_CameraView.setCenter(p_OffsetX, m_CameraView.getCenter().y);
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

bool Camera::IsMovementXAxis()
{
	return m_MovingXAxis;
}
bool Camera::IsMovementYAxis()
{
	return m_MovingYAxis;
}

void Camera::ZoomIn(float p_ZoomValue)
{
	m_CameraView.zoom(p_ZoomValue);
}
void Camera::ZoomOut(float p_ZoomValue)
{
	m_CameraView.zoom(p_ZoomValue);
}
void Camera::ZoomStart(sf::View p_StartView)
{
	m_CameraView = p_StartView;
}

bool Camera::IsZoomingOut()
{
	return m_IsZoomingOut;
}

void Camera::SetZoomingOut(bool p_zoom)
{
	m_IsZoomingOut = p_zoom;
}

void Camera::SetZoomStrength(float p_zoom)
{
	m_ZoomStrength = p_zoom;
}
float Camera::GetZoomStrength()
{
	return m_ZoomStrength;
}

void Camera::SetTotalZoom(float p_TotalZoom)
{
	m_TotalZoom = p_TotalZoom;
}

float Camera::GetTotalZoom()
{
	return m_TotalZoom;
}