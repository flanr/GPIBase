#pragma once
class Button
{
public:
	Button(void);
	~Button(void);


	void SetButtonOrigin();
	void SetCircle(float radius);
	void SetSpriteCircle(sf::Sprite*);
	void SetSpriteRect(sf::Sprite*);
	void SetPosition(float x, float y);

	void MouseMove(int x, int y);
	void MouseDown(int x, int y);
	void MouseUp();

	sf::Sprite* GetSprite();
	sf::CircleShape GetCircle();

private:
	sf::Sprite *m_sprite;
	sf::CircleShape m_circle;
};

