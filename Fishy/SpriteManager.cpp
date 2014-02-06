// SpriteManager.cpp
#include "stdafx.h"

#include "SpriteManager.h"
#include "Sprite.h"
#include "DrawManager.h"

SpriteManager::SpriteManager(DrawManager *draw_manager){
	m_draw_manager = draw_manager;
};
SpriteManager::~SpriteManager(){
};

bool SpriteManager::Initialize(const std::string &directory){

	m_directory = directory;

	return true;
};

void SpriteManager::Cleanup(){

};

sf::Sprite* SpriteManager::Load(const std::string &filename, int x, int y, int width, int height){
	
	std::map<std::string,sf::Texture>::iterator it = m_axSprites.find(filename);
	if(it == m_axSprites.end()) 
	{
		if(!LoadImage(filename)) 
		{
			return nullptr;
		}
		it = m_axSprites.find(filename);
	}
	return new sf::Sprite(it->second, sf::IntRect(x, y, width, height) );
};

bool SpriteManager::LoadImage(const std::string &filename){

	std::string path = m_directory + filename;
	sf::Texture texture;
	if(!texture.loadFromFile(path.c_str() ) )
	{
		return false;
	}

	m_axSprites.insert(std::pair<std::string, sf::Texture>(filename,texture) );
	return true;
};