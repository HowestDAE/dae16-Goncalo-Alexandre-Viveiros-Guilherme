#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "Camera.h"

Level::Level(const std::string& imagePath_lvlTxt, const std::string& backgroundTxt1, const std::string& backgroundTxt3):
	m_LvlTexture{ new Texture {imagePath_lvlTxt}},m_BgTexture(new Texture { backgroundTxt1 }),m_BgTexture3(new Texture{ backgroundTxt3 })
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
		glPushMatrix();
		glScalef(1, 0.2, 0);
		m_BgTexture3->Draw();
		glPopMatrix();
		glScalef(1.8, 1.8,0);
		m_BgTexture->Draw(Point2f{ 0,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidht,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidht,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidht,m_BgFrameHeight });
	}
	glPopMatrix();

}
