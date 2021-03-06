//GameObject.h

#pragma once
#include "Level.h"
#include <string>

class Collider;
class Sprite;
class LightSource;
enum ELayer;

class GameObject
{
public:

	//GameObject();
	/*F�r GameObject utan collider*/
	/*GameObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite);*/
	/*F�r GameObject med Collider*/
	GameObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite = nullptr, Collider *p_pxCollider = nullptr);
	~GameObject();


	sf::Vector2f GetPosition();
	void SetPosition(const sf::Vector2f &p_xPosition);
	void Move(const sf::Vector2f &p_Offset);
	void Move(float p_OffsetX, float p_OffsetY);

	sf::Vector2f GetLightPosition();
	void SetLightPosition(const sf::Vector2f &p_xPosition);
	void SetLightPositionX(const float &p_Xposition);
	void SetLightPositionY(const float &p_Yposition);

	bool HasSprite() const;
	sf::Sprite * GetSprite();
	//bool HasAnimSprite() const;
	//AnimSprite * GetAnimSprite();

	bool HasCollider() const;
	Collider *GetCollider();

	void SetDestroyed(bool p_bDestroyed);
	bool GetDestroyed();

	void FlipXLeft(float scale);
	void FlipXRight(float scale);
	void SetLevelLayer(ELayer); 
	ELayer GetLevelLayer();
	virtual void Update(float deltatime);
	void AddLightSource(LightSource *p_light);
	bool GameObject::HasLight() const;
	LightSource* GetLightSource();
	std::string GetType(){ return m_sType;};
	void SetType(std::string p_sType){m_sType = p_sType;};

	void SetActive(bool p_Activate);
	bool GetActive();

	void AddLightSprite(sf::Sprite *p_sprite);
	sf::Sprite * GetLightSprite();

	virtual void OnCollision(GameObject* p_xOther, sf::Vector2f& offset);

	sf::VertexArray GetGlowRectange()						{return GlowRectangle;}
	sf::Texture* GetGlowTexture()							{return GlowTexture;}
	void SetColor(sf::Color p_color);

	/*int GetCurrentLevel();
	void SetCurrentLevel(int p);*/

protected:
	sf::Sprite *m_pxSprite;
	Collider *m_pxCollider;
	bool m_isDestroyed;
	std::string m_sType;
	ELayer m_LevelLayer;
	float m_LightTimer;

	bool m_ActiveUpdate;
	LightSource *m_light;
	sf::Sprite *m_LightSprite;

	sf::Texture* GlowTexture;
	sf::VertexArray GlowRectangle;

	//int m_CurrentLevel;
};