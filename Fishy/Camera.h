#pragma once
class LightSource;
class GameObjectManager;

class Camera
{
public:
	Camera(sf::Vector2f p_Size);
	~Camera();
	void Initialize(sf::RenderWindow *p_window, sf::Vector2f p_Position);
	void Update(GameObjectManager *p_GameObjMgr);
	void Camera::UpdateFilter(GameObjectManager *p_GameObjMgr);

	void SetCenterCamera(sf::Vector2f p_position);
	sf::View GetCameraView();

	void Move(const sf::Vector2f &p_Offset);
	void Move(float p_OffsetX, float p_OffsetY);

	void SetPosition(const sf::Vector2f &p_Position);
	void SetPositionY(float p_OffsetY);
	void SetPositionX(float p_OffsetX);

	void SetCameraViewport(sf::FloatRect p_NewViewPort);
	sf::FloatRect GetCameraViewport();

	void AddLayer();
	sf::RenderTexture* GetFilterTexture();
	void ToggleFilterOn(bool p_FilterOn);
	bool GetFilterStatus();
	sf::Sprite* GetFilterSprite();

	bool IsMovementXAxis();
	bool IsMovementYAxis();

private:
	sf::View m_CameraView;
	sf::RenderTexture *m_FilterTexture;
    sf::Sprite *m_FilterSprite;
	bool m_FilterOn;

	bool m_MovingXAxis;
	bool m_MovingYAxis;
};

