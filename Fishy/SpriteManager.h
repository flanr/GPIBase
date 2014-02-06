// SpriteManger.h
#pragma once
#include <string>
#include <map>

class DrawManager;
class Sprite;

class SpriteManager{

public:
	SpriteManager(DrawManager *draw_manager);
	~SpriteManager();

		bool Initialize(const std::string &directory);
		void Cleanup();
		bool LoadImage(const std::string &filename);
		sf::Sprite* Load(const std::string &filename, int x, int y, int width, int height);


private:
	DrawManager *m_draw_manager;
	std::string m_directory;
	

};
