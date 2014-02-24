#pragma once
class LightSource
{
public:
	LightSource();
	LightSource(sf::Vector2f p_Position, sf::Vector2f p_Size, float p_Radius);
	~LightSource();

	//to toggle the effect on and off for testing.
	void ToggleOn(bool p_CircleOn);
	void CreateCircle();
	void SetStrength();
	void SetRadius();
	void CutOutCircle();

	void SetPosition(sf::Vector2f p_Position);
	sf::Vector2f GetPosition();
	void SetOrigin(const sf::Vector2f &p_Origin);
	void LightSource::Move(const sf::Vector2f &p_Position);
	void LightSource::Move(float p_OffsetX, float p_OffsetY);
	sf::Sprite* GetBlackLayerSprite();

private:
    sf::RenderTexture *m_LightTexture;
    sf::RenderTexture *m_BlacklayerTexture;
    sf::Sprite *m_LightCutCircle;
    sf::Sprite *m_BlackLayerSprite;
    sf::Vector2f m_Position;
	float m_LightRadius;
	bool m_LightSourceOn;
};

