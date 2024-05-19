#include "pch.h"
#include "Level.h"

#include <iostream>

#include "Texture.h"
#include "Camera.h"
#include "Platforms.h"
#include "SVGParser.h"
#include "utils.h"
#include "Yoshi.h"
#include "WingedClouds.h"

Level::Level(const std::string& imagePathLvlTxt, const std::string& backgroundTxt1, const std::string& backgroundTxt3, float levelStart, Point2f levelEnd,int levelNumber):
	m_LevelNumber(levelNumber),
	m_LvlTexture{ new Texture {imagePathLvlTxt} },
	m_BgTexture(new Texture{ backgroundTxt1 }),
	m_BgTexture3(new Texture{ backgroundTxt3 }),
	m_LevelStart(levelStart),
	m_LevelEnd(levelEnd)
{
	SVGParser::GetVerticesFromSvgFile("ex4.svg", m_LvlVertices);
	if (m_LevelNumber == 1)
	{
		//Add platforms for Lvl 1
		m_Platforms.push_back(new Platforms(Point2f(3620, 400), 48, 16, 48, 16 * 2, "Platforms.png", 90));
		m_Platforms.push_back(new Platforms(Point2f(5299, 743), 48, 16, 48, 16 * 2, "Platforms.png", 90));

		//Add Winged Clouds for Lvl 1
		m_WingedClouds.push_back(new WingedClouds(true, false, false, "GeneralSprites.png", Point2f(2256, 483)));
		m_WingedClouds.push_back(new WingedClouds(false, true, false, "GeneralSprites.png", Point2f(4294, 325)) );
		m_WingedClouds.push_back(new WingedClouds(true, false, false, "GeneralSprites.png", Point2f(4940, 294)));
		m_WingedClouds.push_back(new WingedClouds(false, false, true, "GeneralSprites.png", Point2f(4450, 743)));
		m_WingedClouds.push_back(new WingedClouds(false, false, true, "GeneralSprites.png", Point2f(6292, 639)));
	}
	
}
Level::~Level()
{
	delete m_BgTexture;
	delete m_LvlTexture;
	//delete m_BgTexture2;
	delete m_BgTexture3;
	for (int idx = 0; idx  < m_Platforms.size(); idx ++)
	{
		delete m_Platforms[idx];
	}
	for (int idx = 0; idx < m_WingedClouds.size(); idx++)
	{
		delete m_WingedClouds[idx];
	}
}

void Level::DrawLvl() const  
{
	m_LvlTexture->Draw();
}

void Level::DrawOthers() const
{
	for (int idx = 0; idx < m_Platforms.size(); idx++)
	{
		m_Platforms[idx]->Draw();
	}
	for (int idx = 0; idx < m_WingedClouds.size(); idx++)
	{
		m_WingedClouds[idx]->Draw();
	}
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

void Level::Update(float elapsedSec) const
{
	for (int idx = 0; idx < m_Platforms.size(); idx++)
	{
		m_Platforms[idx]->Update();
	}

	for (int idx = 0; idx < m_WingedClouds.size(); idx++)
	{
		m_WingedClouds[idx]->Update();
	}
}

void Level::Animate(float elapsedSec)
{
	for (int idx = 0; idx < m_WingedClouds.size(); idx++)
	{
		m_WingedClouds[idx]->Animate(elapsedSec);
	}
}

void Level::WarpPipesUpdate(bool isDownPipe, Yoshi* &yoshiPlyr, Point2f pipePosition, float pipeWidth, float pipeHeight, Point2f pipeWarpDestination,Camera* &plyrCamera)
{
	if (utils::IsOverlapping(yoshiPlyr->GetHitBox(), Rectf(pipePosition.x, pipePosition.y, pipeWidth, pipeHeight)) == true)
	{
		if (isDownPipe == true)
		{
			if (yoshiPlyr->GetIsCrouching() == true)
			{			
				yoshiPlyr->SetPosition(pipeWarpDestination);

				plyrCamera->CenterCamera(yoshiPlyr->GetPosition());
			}
		}

		else
		{
			if (yoshiPlyr->GetIsJumping() == true || yoshiPlyr->GetIsHovering() == true)
			{			
				yoshiPlyr->SetPosition(pipeWarpDestination);

				plyrCamera->CenterCamera(yoshiPlyr->GetPosition());
			}
		}
	}

}

void Level::LevelEndUpdate(Point2f yoshiPos)
{
	if (yoshiPos.x >= m_LevelEnd.x)
	{
		if (yoshiPos.y >= m_LevelEnd.y)
		{
			std::cout << "YOU WON!!!!";
		}
	}
}

float Level::GetLevelStart() const
{
	return m_LevelStart;
}

Point2f Level::GetLevelEnd() const
{
	return m_LevelEnd;
}


std::vector<std::vector<Point2f>> Level::GetLevelVertices()
{
	return m_LvlVertices;
}

std::vector<std::vector<Point2f>> Level::GetPlatformVertices() const
{
	for (int idx = 0; idx < m_Platforms.size(); idx++)
	{
		return m_Platforms[idx]->GetPlatformVertices();
	}

}

std::vector<WingedClouds*>& Level::GetWingedClouds()
{
	return m_WingedClouds;
}

