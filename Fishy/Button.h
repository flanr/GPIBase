#pragma once
class Button
{
public:
	Button(void);
	~Button(void);


	void SetButtonOrigin();
	void SetCircle(float radius);
	void SetSprite(sf::Sprite*);
	void SetPosition(float x, float y);

	sf::Sprite* GetSprite();
	sf::CircleShape GetCircle();

private:
	sf::Sprite *m_sprite;
	sf::CircleShape m_circle;
};

