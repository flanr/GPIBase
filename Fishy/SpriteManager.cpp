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
	return 0;

};

bool SpriteManager::LoadImage(const std::string &filename){

	return 0;
};