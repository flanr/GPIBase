// SpriteManger.h
#pragma once
#include <string>
#include <map>

class DrawManager;

class SpriteManager{

public:
	SpriteManager(DrawManager *draw_manager);
	~SpriteManager();

		bool Initialize(const std::string &directory);
		void Cleanup();
		
		sf::Sprite* Load(const std::string &filename, int x, int y, int width, int height);


private:
	bool LoadImage(const std::string &filename, sf::IntRect size);
	DrawManager *m_draw_manager;
	std::string m_directory;
	std::map<std::string, sf::Texture> m_axSprites;
	

};
