#include "pch.h"
#include "Level.h"
#include "Texture.h"

Level::Level(const std::string& imagePath_lvlTxt, const std::string& imagePath_backgroundTxt):
	m_LvlTexture{ new Texture {imagePath_lvlTxt}},m_BgTexture(new Texture { imagePath_backgroundTxt })
{
	
}
Level::~Level()
{
	delete m_BgTexture;
	delete m_LvlTexture;
}

void Level::DrawLvl() const  
{
	m_LvlTexture->Draw();
}

void Level::DrawBackground() const
{
	m_BgTexture->Draw();
}
