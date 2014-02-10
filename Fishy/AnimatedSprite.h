//AnimatedSprite.h

#pragma once

class AnimatedSprite : public sf::Sprite
{
	friend class SpriteManager;
public:
	AnimatedSprite(sf::Texture p_texture, int p_iX, int p_iY, int p_iWidth, int p_iHeight);
	~AnimatedSprite();
	
	void Update(float p_fDeltatime);
	//void Stop();
	void SetFrameDuration(float p_fFrameDuration);
	void AddFrame(sf::IntRect &p_Rect);

private:
	float m_fFrameDuration;
	float m_fTime;
	int m_iCurrentFrame;
	sf::IntRect m_Rect;
	std::vector<sf::IntRect> m_axAnimation;
};