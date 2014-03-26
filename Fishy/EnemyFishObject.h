// EnemyFishObject
#pragma once

#include "GameObject.h"
#include "AIState.h"
#include "AIStateMachine.h"
#include "IdleState.h"

class Collider;
class AnimatedSprite;
template class AIStateMachine<EnemyFishObject>;


class EnemyFishObject : public FishObject
{
public:
	//EnemyFishObject(sf::Vector2f p_xPosition, sf::Sprite *p_xSprite);
	EnemyFishObject(std::string p_SubType, sf::Vector2f p_xPosition, sf::Sprite *p_xSprite, Collider* p_xCollider = nullptr, SpriteManager* p_SpriteManger = nullptr);
	~EnemyFishObject();

	void Update(float deltatime, PlayerFishObject *player);
	void SetEnemyScale(float x);
	void AddAnimation(const std::string &p_sName, AnimatedSprite *p_pxAnimSprite);
	AnimatedSprite* GetCurrentAnimation();

	void ChangeState();

	void SetSpawnPosition(sf::Vector2f p_xSpawnPosition);
	sf::Vector2f GetSpawnPosition(sf::Vector2f p_xSpawnPosition);
	void SetAttractRadius(float p_fAttractRadius);
	/* use for collision with EnemyFish vs Wall*/
	void OnCollision(GameObject* p_other, sf::Vector2f& p_Offset);

	
	

	void setGlowPosition();
	void UpdateGlow();
	void UpdateGlowTexture();
	

	/*----------------AI STUFF-------------------*/
	AIStateMachine<EnemyFishObject>* GetFSM()				{return m_pAIStateMachine;}
	void AddTimer(const int nr)								{m_iStateTimer+= nr;};
	int GetTimer()											{return m_iStateTimer;};
	void ResetTimer()										{m_iStateTimer = 0;};
	sf::Vector2f GetPlayerPosition()						{return m_xPlayerPosition; }
	int GetPlayerDirection()								{return m_iPlayerDirection;}
	
	int random(int min, int max);
	
	std::string GetSubType()								{return m_SubType;}
	void SetSubType(std::string p_type)						{m_SubType = p_type;}
	float GetSubTypeSize()									{return m_SubTypeSize;}
	void SetSubTypeSize(float p_size)						{m_SubTypeSize = p_size;}
	//Idle
	void Idle();
	//Scared
	void Scared();
	bool GetSafe()											{return isSafe;}
	void SetSafe(bool val)									{isSafe = val;}
	//Hunting
	void Hunting();
	//Attracted
	void Attracted();
	LightSource* GetPlayerLightSource()						{return m_pPlayerLightSource;}



private:
	sf::Vector2f m_xSpawnPosition, m_xPlayerPosition, m_vPlayerVelocity;
	int m_iStateTimer, m_iPlayerDirection;
	AIStateMachine<EnemyFishObject>* m_pAIStateMachine;
	bool isSafe;
	std::string m_SubType;
	float m_SubTypeSize;
	AnimatedSprite *m_pxCurrentAnimation;
	std::map<std::string, AnimatedSprite*> m_mpAnimations;
	LightSource* m_pPlayerLightSource;
	/*sf::Sprite* glow;*/
	
};

