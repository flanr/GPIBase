// SpriteManager.cpp
#include "stdafx.h"

#include "SpriteManager.h"
#include "DrawManager.h"
#include "AnimatedSprite.h"

SpriteManager::SpriteManager(DrawManager *draw_manager){
	m_draw_manager = draw_manager;
};
SpriteManager::~SpriteManager(){
};

bool SpriteManager::Initialize(const std::string &directory){

	m_directory = directory;

	return true;
};

void SpriteManager::Cleanup()
{
	std::map<std::string, sf::Texture*>::iterator it = m_axSprites.begin();
	while(it != m_axSprites.end() )
	{
		delete it->second;
		it++;
	}
	m_axSprites.clear();
};

sf::Sprite* SpriteManager::Load(const std::string &filename, int x, int y, int width, int height){

	
	std::map<std::string,sf::Texture*>::iterator it = m_axSprites.find(filename);
	if(it == m_axSprites.end()) 
	{
		if(!LoadImage(filename) ) 
		{
			return nullptr;
		}
		it = m_axSprites.find(filename);
	}
	return new sf::Sprite(*it->second, sf::IntRect(x, y, width, height) );

}

AnimatedSprite* SpriteManager::LoadAnim(const std::string &p_sFilename)
{
	std::ifstream file;
	file.open(p_sFilename.c_str());
	if(!file.is_open())
	{
		return nullptr;
	}

	std::string row;
	file >> row;
	std::map<std::string,sf::Texture*>::iterator it = m_axSprites.find(row);
	if(it == m_axSprites.end()) 
	{
		if(!LoadImage(row)) 
		{
			file.close();
			return nullptr;
		}
		it = m_axSprites.find(row);
	}
	//Flytta allt nedan till egen funktion så man kan bestämma vilken 
	AnimatedSprite *pxSprite = new AnimatedSprite(it->second, 0, 0, 0, 0);

	while(!file.eof()) 
	{
		std::getline(file, row);
		if(row.length() == 0) 
		{ 
			continue; 
		}

		std::stringstream ss(row);

		sf::IntRect Rect;
		float fFrameDuration;

		ss >> fFrameDuration;
		ss >> Rect.left;
		ss >> Rect.top;
		ss >> Rect.width;
		ss >> Rect.height;

		pxSprite->SetFrameDuration(fFrameDuration);
		pxSprite->AddFrame(Rect);
	}
	file.close();
	return pxSprite;
}

bool SpriteManager::LoadImage(const std::string &filename){
	
	std::string &path = m_directory + filename;
	sf::Texture *texture = new sf::Texture;
	//texture->setSmooth(true);
	if(!texture->loadFromFile(path.c_str() ) )
	{
		return false;
	}
	
	m_axSprites.insert(std::pair<std::string, sf::Texture*>(filename, texture) );
	return true;
};