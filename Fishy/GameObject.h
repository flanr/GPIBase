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
	/*För GameObject utan collider*/
	/*GameObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite);*/
	/*För GameObject med Collider*/
	GameObject(sf::Vector2f p_xPosition, sf::Sprite *p_pxSprite = nullptr, Collider *p_pxCollider = nullptr);
	~GameObject();


	sf::Vector2f GetPosition();
	void SetPosition(const sf::Vector2f &p_xPosition);

	sf::Vector2f GetLightPosition();
	void SetLightPosition(const sf::Vector2f &p_xPosition);

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
	LightSource* GetLightSource();
	std::string GetType(){ return m_sType;};
	void SetType(std::string p_sType){m_sType = p_sType;};
	virtual void OnCollision(GameObject* p_xOther);
protected:
	sf::Sprite *m_pxSprite;
	Collider *m_pxCollider;
	sf::Vector2f m_xPosition;
	bool m_bDestroyed;
	std::string m_sType;
	ELayer m_LevelLayer;

	LightSource *m_light;
};