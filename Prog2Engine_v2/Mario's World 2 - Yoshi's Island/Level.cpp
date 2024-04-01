#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "Camera.h"

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
	glPushMatrix();
	{
		glScalef(1.8, 1.8,0);
		m_BgTexture->Draw(Point2f{ 0,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidht,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidht,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidht,m_BgFrameHeight });
	}
	glPopMatrix();

}
