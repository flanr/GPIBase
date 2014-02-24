#pragma once
class LightSource;

class Camera
{
public:
	Camera(sf::Vector2f p_Size);
	~Camera();

	void Update(sf::Vector2f p_position, LightSource *light);
	void SetCameraPosition(sf::Vector2f p_position);
	sf::View GetCameraView();

	void Move(const sf::Vector2f &p_Offset);
	void Move(float p_OffsetX, float p_OffsetY);

	void SetCameraViewport(sf::FloatRect p_NewViewPort);
	sf::FloatRect GetCameraViewport();

	void AddLayer();
	void ToggleFilterOn(bool p_FilterOn);
	bool GetFilterStatus();
	sf::Sprite* GetFilterSprite();
	void CutOutFilter(LightSource *light);

private:
	sf::View m_CameraView;
	sf::RenderTexture *m_FilterTexture;
    sf::Sprite *m_FilterSprite;
	bool m_FilterOn;

};

