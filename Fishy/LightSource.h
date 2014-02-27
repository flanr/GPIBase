#pragma once
class LightSource
{
public:
	LightSource();
	LightSource(sf::Vector2f p_Position, float p_Radius);
	~LightSource();

	void CreateCircle();
	void SetStrength();
	void SetRadius();

	void ToggleLightOn(bool p_LightOn);
	bool GetLightStatus();

	void SetPosition(sf::Vector2f p_Position);
	sf::Vector2f GetPosition();
	void SetOrigin(const sf::Vector2f &p_Origin);
	void Move(const sf::Vector2f &p_Position);
	void Move(float p_OffsetX, float p_OffsetY);
	sf::CircleShape* GetLightCircle();

private:
    sf::RenderTexture *m_LightTexture;
	sf::CircleShape *m_Circle;
	float m_LightRadius;
	bool m_LightOn;
};

