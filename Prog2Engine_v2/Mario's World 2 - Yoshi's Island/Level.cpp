#include "pch.h"
#include "Level.h"

#include <iostream>

#include "Block.h"
#include "Texture.h"
#include "Camera.h"
#include "Flowers.h"
#include "Coin.h"
#include "Boulder.h"
#include "Platforms.h"
#include "SoundManager.h"
#include "Star.h"
#include "SVGParser.h"
#include "utils.h"
#include "Yoshi.h"
#include "WingedClouds.h"

Level::Level(const std::string& imagePathLvlTxt, const std::string& backgroundTxt1, const std::string& backgroundTxt3,float levelStart, Point2f levelEnd,int levelNumber):
	m_LevelNumber(levelNumber),
	m_LevelStart(levelStart),
	m_LevelEnd(levelEnd),
	m_LvlTexture{new Texture{imagePathLvlTxt}},
	m_BgTexture(new Texture{backgroundTxt1}),
	m_BgTexture3(new Texture{backgroundTxt3})
{

	if (m_LevelNumber == 1)
	{

		SVGParser::GetVerticesFromSvgFile("ex4.svg", m_LvlVertices);

		//Add platforms for Lvl 1
		m_Platforms.push_back(new Platforms(Point2f(3620, 400), 48 ,16, 48, 16 * 2, "Platforms.png", 90));
		m_Platforms.push_back(new Platforms(Point2f(4930, 774), 48, 16, 48, 16 * 2, "Platforms.png", 90));

		
		//Add Winged Clouds for Lvl 1
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StairCloud, "GeneralSprites.png", Point2f(2256, 483)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StarCloud, "GeneralSprites.png", Point2f(4294, 325)) );
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::SunflowerCloud, "GeneralSprites.png", Point2f(4940, 294)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::FlowerCloud, "GeneralSprites.png", Point2f(4450, 743)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StarCloud, "GeneralSprites.png", Point2f(6292, 639)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StarCloud, "GeneralSprites.png", Point2f(4604, 520))); //TODO make it a invisible secret cloud

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
		m_LvlEntities.push_back(new Boulder(Point2f(5343, 858)));

		//Adds Coins
		CoinManager(40, 40, 0, 3, Point2f(652, 320));
		CoinManager(100, 40, 0, 3, Point2f(1730, 830));
		CoinManager(300, 20, 0, 3, Point2f(1031, -556));

		//Add Blocks
		m_LvlEntities.push_back(new Block(Point2f(1014, -675), Block::BlockType::EggBlock));
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

void Level::DrawLvl(Point2f camPos) const  
{
	glPushMatrix();
	{
		glPushMatrix();
		glTranslatef(-camPos.x / 1.4f, -camPos.y / 1.4f, 0);          //parallax scrolling
		DrawBackground();

		glPopMatrix();

		glPushMatrix();

		glScalef(1.959676875f, 1.9868859f, 0);
		glTranslatef(0, -430, 0);
		m_LvlTexture->Draw();
		glPopMatrix();

		DrawOthers();
	}


	
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
		m_SunflowerCloudTxt->Draw(Rectf(4900, 254, 56*2, 64*2), Rectf(0, 104, 56, 64));
		m_SunflowerCloudTxt->Draw(Rectf(4900, 254 + (64*2), 56*2, 64*2), Rectf(0, 104, 56, 64));
		m_SunflowerCloudTxt->Draw(Rectf(4900, 254 + (64*2) * 2, 56*2, 64*2), Rectf(0, 104, 56, 64));
		m_SunflowerCloudTxt->Draw(Rectf(4900 + 56/2, 254 + (64*2) * 3 -2, 32*2, 32*2), Rectf(0, 32, 32, 32));

		utils::SetColor(Color4f(1, 1, 1, 1));
		utils::DrawLine(4900, 290, 4960, 290, 1);
		utils::DrawLine(4900, 290 + (64 * 2), 4960, 290 + (64 * 2), 1);
		utils::DrawLine(4900, 290 + (64 * 2)*2, 4960, 290 + (64 * 2)*2, 1);


		utils::DrawLine(4960, 355, 5020, 355, 1);
		utils::DrawLine(4960, 355 + (64 * 2), 5020, 355 +(64 * 2), 1);
		utils::DrawLine(4960, 355 + (64 * 2) * 2, 5020, 355 + (64 * 2)*2, 1);

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
		glScalef(1.8f, 1.8f,0);
		m_BgTexture->Draw(Point2f{ 0,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidth,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidth,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidth,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidth*2,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidth,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidth*3,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidth,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidth*4,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidth,m_BgFrameHeight });
	}
	glPopMatrix();

}


void Level::Update(float elapsedSec,bool isPlayerPauseTrue, Yoshi*& yoshiPlyr, const std::vector<Enemy*>& enemies, SoundManager*& soundManager, Camera*& plyrCamera)
{
	if (isPlayerPauseTrue == false)
	{
		for (int idx = 0; idx < m_Platforms.size(); idx++)
		{
			m_Platforms[idx]->Update(elapsedSec,yoshiPlyr->GetPosition());

			if (yoshiPlyr->GetIsOnMovingPlatform() == true)
			{
				yoshiPlyr->SetPosition(m_Platforms[idx]->GetCenterPosition() + Vector2f(cos(m_Platforms[idx]->GetAngle()
					+ ((M_PI / 2) * m_Platforms[idx]->GetWhichPlatformIsYoshiOn())), 
					sin(m_Platforms[idx]->GetAngle() + ((M_PI / 2) * idx) + m_Platforms[idx]->GetPlatformHeight()) ) * m_Platforms[idx]->GetRadius());
					break;

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
				if (wingedClouds->GetIsHit() == true)
				{
					if (m_LevelNumber == 1)
					{
						if (wingedClouds->GetTypeOfCloud() == WingedClouds::Type::StairCloud)
						{
							//m_EventVertices1.push_back(Point2f(2300, 495));
							//m_EventVertices1.push_back(Point2f(2000, 790));
							m_LvlVertices.push_back(std::vector<Point2f>{Point2f(2300, 495), Point2f(2000, 790)});

							m_LevelPause = true;
							m_DrawEventStairs = true;
							delete m_LvlEntities[idx];
							m_LvlEntities[idx] = nullptr;
							m_LevelPause = false;
							break;
						}

						if (wingedClouds->GetTypeOfCloud() == WingedClouds::Type::SunflowerCloud)
						{
							m_LvlVertices.push_back(std::vector<Point2f>{Point2f(4900, 290), Point2f(4960, 290) });
							m_LvlVertices.push_back(std::vector<Point2f>{Point2f(4900, 290 + (64 * 2)), Point2f(4960, 290 + (64 * 2))});
							m_LvlVertices.push_back(std::vector<Point2f>{Point2f(4900, 290 + (64 * 2) * 2), Point2f(4960, 290 + (64 * 2) * 2)});
							m_LvlVertices.push_back(std::vector<Point2f>{Point2f(4960, 355), Point2f(5020, 355)});
							m_LvlVertices.push_back(std::vector<Point2f>{Point2f(4960, 355 + (64 * 2)), Point2f(5020, 355 + (64 * 2))});
							m_LvlVertices.push_back(std::vector<Point2f>{Point2f(4960, 355 + (64 * 2) * 2), Point2f(5020, 355 + (64 * 2) * 2)});
						
							m_DrawEventSunflower = true;
							delete m_LvlEntities[idx];
							m_LvlEntities[idx] = nullptr;
							break;
						}
					}

					if (wingedClouds->GetTypeOfCloud() == WingedClouds::Type::FlowerCloud)
					{
						m_LvlEntities.push_back(new Flower(wingedClouds->GetPosition()));

						delete m_LvlEntities[idx];
						m_LvlEntities[idx] = nullptr;
						break;
					}

					if (wingedClouds->GetTypeOfCloud() == WingedClouds::Type::StarCloud)
					{
						for (int idx{ 0 }; idx < 5; idx++)
						{
							m_LvlEntities.push_back(new Star(wingedClouds->GetPosition()));
							m_LvlEntities.back()->AddVelocity(rand() % -30 + 60, (rand() % 90));
						}
	
						delete m_LvlEntities[idx];
						m_LvlEntities[idx] = nullptr;
						break;
					}

				}
			}
		}
		if (m_LvlEntities[idx] != nullptr)
		{
			m_LvlEntities[idx]->Update(m_LvlVertices, elapsedSec);
		}
		
		
	}

	Animate(elapsedSec);

	if (m_IsBGMusicOn == false)
	{
		Sound(soundManager);

		m_IsBGMusicOn = true;
	}

	if (m_LevelNumber == 1)
	{
		WarpPipesUpdate(true, yoshiPlyr, Point2f(2708, 348), 16, 16, Point2f(740, -515), plyrCamera);
		WarpPipesUpdate(false, yoshiPlyr, Point2f(2521, -542), 16, 16, Point2f(3121, 230), plyrCamera);
	}

}

void Level::Sound(SoundManager*& soundManager)
{
	soundManager->PlayBGMusic(SoundManager::LvlMusic::Level1);
}

void Level::CoinManager(int coinRowSize, int coinColumnSize, int numberOfRedCoin, int spacing,Point2f position)
{
	const int numberOfCoinsInRow = coinRowSize / (12 + spacing);

	const int numberOfCoinsInColumn = coinColumnSize / (16 + spacing);

	const int numberOfCoins = numberOfCoinsInColumn + numberOfCoinsInRow;

	if (numberOfCoinsInRow > 0)
	{
		if (numberOfCoinsInColumn > 0)
		{
			for (int idx = 0; idx < numberOfCoinsInColumn; idx++)
			{
				for (int idx2 = 0; idx2 < numberOfCoinsInRow; idx2++)
				{
					m_LvlEntities.push_back(new Coin(false, Point2f(position.x + (12 * 2 + spacing) * idx2, position.y + (16 * 2 + spacing) * idx)));
				}
			}
			
		}
		else
		{
			std::cout << "The values provided cant make any coins";
		}
	}

	else
	{
		std::cout << "The values provided cant make any coins";
	}
	
}

void Level::Animate(float elapsedSec) const
{
	for (int idx = 0; idx < m_LvlEntities.size(); idx++)
	{
		if (m_LvlEntities[idx] != nullptr)
		{
			m_LvlEntities[idx]->Animate(elapsedSec);
		}
	}
}

void Level::WarpPipesUpdate(bool isDownPipe, Yoshi* &yoshiPlyr, Point2f pipePosition, int pipeWidth, int pipeHeight, Point2f pipeWarpDestination, Camera* &plyrCamera)
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
	std::vector<std::vector<Point2f>> temp;
	for (int idx{0};idx < m_Platforms.size(); idx++)
	{
		for (int idx2{ 0 }; idx2 < m_Platforms[idx]->GetPlatformVertices().size(); idx2++)
		{
			temp.push_back(m_Platforms[idx]->GetPlatformVertices()[idx2]);
		}
	
	}
	return temp;
}

std::vector<Entity*>& Level::GetLevelEntities() 
{
	return m_LvlEntities;
}


