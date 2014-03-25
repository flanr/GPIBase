// GameState.h
#pragma once
#include "State.h"
#include "Core.h"
#include "SpriteManager.h"
using namespace std;
//FWD declare för testning av circle collider.
class Collider;
class CollisionManager;

class Level;
class PlayerFishObject;
class DrawManager;
class GameObjectManager;
class Camera;

class GameState : public State
{
public:
	GameState(Core* p_core);
	/* Called upon GameState Entry */
	bool EnterState();
	/* Updating GameState */
	bool Update(float p_fDeltatime);
	/*	Returns True if p_type == GameState */
	bool IsType(const string &p_sType);
	/* Exits GameState */
	void ExitState();	
	/* Draws GameState */
	void Draw();
	/* Handle Input in GameState */
	void HandleInput();
	/*Call Cleanup when you want to play a new game*/
	void Cleanup();
	/* Returns default Next State */
	string Next();
	/*Returns Current State */
	string GetCurrentState();

	void UpdateGUI();
	void HandlePause();
	void MouseDown(int x, int y);
	int MouseOver(int x, int y);

	void UpdateTutorial();
	void TutorialWASD();
	void TutorialSpace();
	void TutorialF();
	void DrawGUI();
	void DrawTutorial();

private:
	bool bStateRunning;
	InputManager *m_pInputManager;
	Core *m_pCore;
	sf::RenderWindow *m_window;
	PlayerFishObject *m_player;
	SoundManager *m_SoundManager;

	Level* m_LevelLayerForGround;
	Level* m_LevelLayerMidleGround;
	Level* m_LevelLayerBackgroundSecondLowest;
	Level* m_LevelLayerBackgroundSecondHighest;
	Level* m_LevelLayerMiddleFront;
	Level* m_LevelLayerBackgroundLowest;
	SpriteManager* m_SpriteManager;
	DrawManager* m_DrawManager;
	GameObjectManager *m_GameObjMgr;
	Camera* m_Camera;

	Slider m_HealthSlider;
	Slider m_EnergySlider;
	sf::Sprite *Gui;
	sf::Sprite m_GuiEnergy;
	sf::Sprite m_GuiSpeed;
	sf::Sprite m_GuiPower;

	CollisionManager* m_pxCollisionManager;

	bool m_TutorialWASD;
	bool m_TutorialSPACE;
	bool m_TutorialF;
	bool m_TutorialFPressed;
	bool m_Paused;
	sf::Sprite m_TutorialSpriteWASD;
	sf::Sprite m_TutorialSpriteSPACE;
	sf::Sprite m_TutorialSpriteF;

	/// PAUSE / OPTIONS ///
	sf::Sprite *m_OptionBackground;
sf::Sprite *m_BackGroundImg;
	int m_ButtonClick;

	// Buttons 
	Button m_ButtonMusicMute;
	sf::Vector2f m_ButtonMusicMutePos;
	Button m_ButtonSoundMute;
	sf::Vector2f m_ButtonSoundMutePos;
	Button m_ButtonFullScreen;
	sf::Vector2f m_ButtonFullScreenPos;
	Button m_ButtonWindowed;
	sf::Vector2f m_ButtonWindowedPos;
	Button m_ButtonReturn;
	sf::Vector2f m_ButtonReturnPos;
	/*Button m_ButtonExit;
	sf::Vector2f m_Bu;
	Button m_a;
	sf::Vector2f m_a;*/

	// Sliders
	Slider m_SliderMusicVol;
	Slider m_SliderSoundVol;


};
