//AnimatedSprite.h

#pragma once

class AnimatedSprite : public sf::Sprite
{
	friend class SpriteManager;
public:
	
	struct Anim
	{
		float m_fFrameDuration;
		struct std::vector<sf::IntRect> m_axAnimation;
	};

	AnimatedSprite(sf::Texture *p_texture, int p_iX, int p_iY, int p_iWidth, int p_iHeight);
	~AnimatedSprite();
	
	void Update(float p_fDeltatime);
	void SetActiveAnimation(const std::string AnimName);
	const std::string GetActiveAnimation();
	void Stop();
	void StoreAnim(const std::string AnimName, Anim p_Anim);
	int GetCurrentFrame();

private:
	float m_fTime;
	int m_iCurrentFrame;

	std::string m_AnimType;
	std::map<std::string, Anim> m_mAllAnimations;
};