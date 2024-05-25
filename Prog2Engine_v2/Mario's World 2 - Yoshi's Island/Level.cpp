#include "pch.h"
#include "Level.h"

#include <iostream>

#include "Texture.h"
#include "Camera.h"
#include "Flowers.h"
#include "Boulder.h"
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

	if (m_LevelNumber == 1)
	{

		SVGParser::GetVerticesFromSvgFile("ex4.svg", m_LvlVertices);

		//Add platforms for Lvl 1
		m_Platforms.push_back(new Platforms(Point2f(3620, 400), 48 ,16, 48 * 2, 16 * 2, "Platforms.png", 90));
		m_Platforms.push_back(new Platforms(Point2f(4930, 774), 48, 16, 48, 16 * 2, "Platforms.png", 90));

		//Add Winged Clouds for Lvl 1
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StairCloud, "GeneralSprites.png", Point2f(2256, 483)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StarCloud, "GeneralSprites.png", Point2f(4294, 325)) );
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::SunflowerCloud, "GeneralSprites.png", Point2f(4940, 294)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::FlowerCloud, "GeneralSprites.png", Point2f(4450, 743)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StarCloud, "GeneralSprites.png", Point2f(6292, 639)));

		//Adds the 5 flower locations
		m_LvlEntities.push_back(new Flower(Point2f(1537,355)));
		m_LvlEntities.push_back(new Flower(Point2f(1598,800)));
		m_LvlEntities.push_back(new Flower(Point2f(2950,260)));
		m_LvlEntities.push_back(new Flower(Point2f(3365,252)));
		//last flower is a winged cloud

		m_StairCloudTxt = new Texture("Stairs.png");
		m_SunflowerCloudTxt = new Texture("Sunflower.png");

		//Adds Boulders
		m_LvlEntities.push_back(new Boulder(Point2f(1315, -758)));
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
	for (int idx = 0; idx < m_LvlEntities.size(); idx++)
	{
		delete  m_LvlEntities[idx];
	}
	delete m_StairCloudTxt;
	delete m_SunflowerCloudTxt;

}

void Level::DrawLvl() const  
{
	m_LvlTexture->Draw();
}

void Level::DrawOthers() const
{
	if (!m_Platforms.empty())
	{
		for (int idx = 0; idx < m_Platforms.size(); idx++)
		{
			m_Platforms[idx]->Draw();
		}
	}

	for (int idx = 0; idx < m_LvlEntities.size(); idx++)
	{
		if (m_LvlEntities[idx] != nullptr)
		{
			m_LvlEntities[idx]->Draw();
		}
	}

	if (m_DrawEventStairs == true)
	{
		m_StairCloudTxt->Draw(Rectf(2175, 480, 125, 125), Rectf(0, 0, 70, 64));
		m_StairCloudTxt->Draw(Rectf(2175 - 120, 480 + 125, 125, 125), Rectf(0, 0, 70, 64));
		m_StairCloudTxt->Draw(Rectf(2175 - 230, 480 + 125*2, 125, 62.5), Rectf(0, 0, 70, 32));
	}

	if (m_DrawEventSunflower == true)
	{
	
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


void Level::Update(float elapsedSec,bool isPlayerPauseTrue, Yoshi*& yoshiPlyr, const std::vector<Enemy*>& enemies)
{
	if (isPlayerPauseTrue == false)
	{
		for (int idx = 0; idx < m_Platforms.size(); idx++)
		{
			m_Platforms[idx]->Update(elapsedSec,yoshiPlyr->GetPosition());

			if (yoshiPlyr->GetIsOnMovingPlatform() == true)
			{
				yoshiPlyr->SetPosition(m_Platforms[idx]->GetPlatformPosition());
			}
		}
	}

	for (int idx = 0; idx < m_LvlEntities.size(); idx++)
	{
		if (const auto boulders = dynamic_cast<::Boulder*>(m_LvlEntities[idx]))
		{
			boulders->Update(m_LvlVertices, elapsedSec);
			boulders->Hitcheck(enemies);
		}
	}

	for (int idx = 0; idx < m_LvlEntities.size(); idx++)
	{
		if (auto wingedClouds = dynamic_cast<::WingedClouds*>(m_LvlEntities[idx]))
		{
			if (wingedClouds != nullptr)
			{
				wingedClouds->Update();

				if (wingedClouds->GetIsHit() == true)
				{
					if (m_LevelNumber == 1)
					{
						if (idx == 0)
						{
							std::vector<Point2f> stairs{ 0 };
							stairs.push_back(Point2f(2300, 495));
							stairs.push_back(Point2f(2000, 790));
							m_LvlVertices.push_back(stairs);
							m_LevelPause = true;
							m_DrawEventStairs = true;
							m_LvlEntities[idx] = nullptr;
							delete m_LvlEntities[idx];
							m_LevelPause = false;
							break;
						}

						if (idx == 2)
						{
							//TODO spawn sunflower
							std::vector<Point2f> sunflower{ 0 };
							m_DrawEventSunflower = true;
							m_LvlEntities[idx] = nullptr;
							delete m_LvlEntities[idx];
							break;
						}
					}

					if (wingedClouds->GetTypeOfCloud() == WingedClouds::Type::FlowerCloud)
					{
						m_LvlEntities.push_back(wingedClouds->GetFlower());

						m_LvlEntities[idx] = nullptr;
						delete m_LvlEntities[idx];
						break;
					}

				}
			}
		}
		
	}


	

}

void Level::Animate(float elapsedSec) const
{
	for (int idx = 0; idx < m_LvlEntities.size(); idx++)
	{
		if (const auto wingedClouds = dynamic_cast<::WingedClouds*>(m_LvlEntities[idx]))
		{
			if (wingedClouds != nullptr)
			{
				wingedClouds->Animate(elapsedSec);
			}
		}
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
			m_LevelPause = true;
			std::cout << "YOU WON!!!!";
		}
	}
}

float Level::GetLevelStart() const
{
	return m_LevelStart;
}

bool Level::GetLevelPause() const
{
	return m_LevelPause;
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

std::vector<Entity*>& Level::GetLevelEntities() 
{
	return m_LvlEntities;
}


