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
<<<<<<< HEAD
		bool LoadImage(const std::string &filename);
=======
		
>>>>>>> 687f2cdb21b14659aa619fd3828c1c2f0f53e4db
		sf::Sprite* Load(const std::string &filename, int x, int y, int width, int height);


private:
	bool LoadImage(const std::string &filename);
	DrawManager *m_draw_manager;
	std::string m_directory;
	std::map<std::string, sf::Texture> m_axSprites;
	

};
