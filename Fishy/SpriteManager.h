// SpriteManger.h
#pragma once
#include <string>
#include <map>

class DrawManager;
class AnimatedSprite;

class SpriteManager{

public:
	SpriteManager(DrawManager *draw_manager);
	~SpriteManager();

		bool Initialize(const std::string &directory);
		void Cleanup();

		sf::Sprite* Load(const std::string &filename, int x, int y, int width, int height);
		AnimatedSprite *LoadAnim(const std::string &p_sFilename);

private:
	bool LoadImage(const std::string &filename);
	DrawManager *m_draw_manager;
	std::string m_directory;
	std::map<std::string, sf::Texture> m_axSprites;
};
