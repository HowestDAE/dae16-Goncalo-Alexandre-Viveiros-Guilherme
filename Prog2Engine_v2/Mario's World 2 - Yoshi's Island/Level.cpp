#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "Camera.h"
#include "Platforms.h"
#include "SVGParser.h"

Level::Level(const std::string& imagePathLvlTxt, const std::string& backgroundTxt1, const std::string& backgroundTxt3):
	m_LvlTexture{ new Texture {imagePathLvlTxt}},m_BgTexture(new Texture { backgroundTxt1 }),m_BgTexture3(new Texture{ backgroundTxt3 })
{
	SVGParser::GetVerticesFromSvgFile("ex4.svg", m_LvlVertices);
	m_Platforms = new Platforms(Point2f(3620, 400), 48, 16, 48 * 2, 16 * 2, "Platforms.png", 90);
}
Level::~Level()
{
	delete m_BgTexture;
	delete m_LvlTexture;
	//delete m_BgTexture2;
	delete m_BgTexture3;
	delete m_Platforms;
}

void Level::DrawLvl() const  
{
	m_LvlTexture->Draw();
}

void Level::DrawPlatforms() const
{
	m_Platforms->Draw();
}

void Level::DrawBackground() const
{
	
	glPushMatrix();
	{
		glPushMatrix();
		glScalef(90, 2, 0);
		m_BgTexture3->Draw();
		glPopMatrix();
		glScalef(1.8, 1.8,0);
		m_BgTexture->Draw(Point2f{ 0,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidht,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidht,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidht,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidht*2,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidht,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidht*3,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidht,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidht*4,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidht,m_BgFrameHeight });
	}
	glPopMatrix();

}

void Level::Update(float elapsedSec)
{
	m_Platforms->Update();
}

std::vector<std::vector<Point2f>> Level::GetLevelVertices()
{
	return m_LvlVertices;
}

std::vector<std::vector<Point2f>> Level::GetPlatformVertices()
{
	return m_Platforms->GetPlatformVertices();
}

