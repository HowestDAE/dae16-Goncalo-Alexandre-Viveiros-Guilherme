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
#include "StateManager.h"
#include "SVGParser.h"
#include "utils.h"
#include "Yoshi.h"
#include "WingedClouds.h"

Level::Level(const std::string& imagePathLvlTxt, const std::string& backgroundTxt1,const std::string& backgroundTxt2,
	const std::string& backgroundTxt3,float levelStart, Point2f levelEnd,int levelNumber, StateManager* stateManager):
	m_LevelNumber(levelNumber),
	m_LevelStart(levelStart),
	m_LevelEnd(levelEnd),
	m_LvlTexture{new Texture{imagePathLvlTxt}},
	m_BgTexture(new Texture{backgroundTxt1}),
	m_BgTexture2(new Texture{ backgroundTxt2}),
	m_BgTexture3(new Texture{backgroundTxt3}),
	m_StateManager(stateManager)
{

	if (m_LevelNumber == 1)
	{

		SVGParser::GetVerticesFromSvgFile("ex4.svg", m_LvlVertices);

		//Add platforms for Lvl 1
		m_Platforms.push_back(new Platforms(Point2f(3620, 400), 48 ,16, 48, 16 * 2, "Platforms.png", 90));
		m_Platforms.push_back(new Platforms(Point2f(4930, 774), 48, 16, 48, 16 * 2, "Platforms.png", 90));

		
		//Add Winged Clouds for Lvl 1
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StairCloud, "GeneralSprites.png", Point2f(2256, 483)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StarCloud, "GeneralSprites.png", Point2f(4294, 425)) );
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::SunflowerCloud, "GeneralSprites.png", Point2f(4940, 350)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::FlowerCloud, "GeneralSprites.png", Point2f(4450, 743)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StarCloud, "GeneralSprites.png", Point2f(4560, 540)));
		m_LvlEntities.push_back(new WingedClouds(WingedClouds::Type::StarCloud, "GeneralSprites.png", Point2f(6262, 849)));

		//Adds the 5 flower locations
		m_LvlEntities.push_back(new Flower(Point2f(1537,455)));
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
		CoinManager(40, 40, 0, 3, 3,Point2f(652, 320));
		CoinManager(100, 40, 6, 3,3 ,Point2f(1730, 830));
		CoinManager(1200, 20, 7, 50,3, Point2f(1031, -556));
		for (int idx = 0; idx < 13; idx++)
		{
			m_LvlEntities.push_back(new Coin(false, Point2f(1985 + 30 * idx, 800 - 25 * idx)));
		}
	

		//Add Blocks
		m_LvlEntities.push_back(new Block(Point2f(1014, -675), Block::BlockType::EggBlock));
	}
	
}
Level::~Level()
{
	delete m_BgTexture;
	delete m_LvlTexture;
	delete m_BgTexture2;
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
		glScalef(62.f, 1, 0);
		m_BgTexture3->Draw(Point2f{ 0, -800 });
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-camPos.x / 1.3f, 0, 0);
		glScalef(1.8f, 1.8f, 0);
		m_BgTexture2->Draw(Point2f{ 80, -430});
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
		if (m_LvlEntities[idx]->GetIsActive() == true)
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
		m_BgTexture->Draw(Point2f{ m_BgFrameWidth,0}, Rectf{ m_BgFrameStart,m_BgFrameStart ,m_BgFrameWidth,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidth*2,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidth,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidth*3,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidth,m_BgFrameHeight });
		m_BgTexture->Draw(Point2f{ m_BgFrameWidth*4,0 }, Rectf{ m_BgFrameStart,m_BgFrameStart,m_BgFrameWidth,m_BgFrameHeight });
		
	}
	glPopMatrix();

}


void Level::Update(float elapsedSec, Yoshi* yoshiPlyr, const std::vector<Enemy*> enemies, SoundManager* soundManager, Camera* plyrCamera)
{

	if (m_StateManager->GetState() != StateManager::States::Pause)
	{
		for (int idx = 0; idx < m_Platforms.size(); idx++)
		{
			m_Platforms[idx]->Update(elapsedSec,yoshiPlyr->GetPosition(),yoshiPlyr->GetVelocity());

			
				if (yoshiPlyr->GetPosition().y > m_Platforms[idx]->GetCenterPosition().y - m_Platforms[idx]->GetRadius() - m_Platforms[idx]->GetPlatformHeight()
					&& yoshiPlyr->GetPosition().y < m_Platforms[idx]->GetCenterPosition().y + m_Platforms[idx]->GetRadius() + m_Platforms[idx]->GetPlatformHeight())
				{
					if (yoshiPlyr->GetPosition().x > m_Platforms[idx]->GetCenterPosition().x - m_Platforms[idx]->GetRadius() - m_Platforms[idx]->GetPlatformWidth()
						&& yoshiPlyr->GetPosition().x < m_Platforms[idx]->GetCenterPosition().x + m_Platforms[idx]->GetRadius() + m_Platforms[idx]->GetPlatformWidth())
					{
						if (yoshiPlyr->GetIsOnMovingPlatform() == true)
						{
							if (yoshiPlyr->GetVelocity().x == 0.f)
							{
								if (yoshiPlyr->GetIsJumping() == false || yoshiPlyr->GetIsHovering() == false)
								{
									if (yoshiPlyr->GetVelocity().y > -0.1)
									{
										yoshiPlyr->SetPosition(m_Platforms[idx]->GetCenterPosition() + Vector2f(cos(m_Platforms[idx]->GetAngle() + ((M_PI / 2) * m_Platforms[idx]->GetWhichPlatformIsYoshiOn())),
											sin(m_Platforms[idx]->GetAngle() + ((M_PI / 2) * m_Platforms[idx]->GetWhichPlatformIsYoshiOn()))) * m_Platforms[idx]->GetRadius());

										if (yoshiPlyr->GetIsFacingRight() == true)
										{
											yoshiPlyr->SetPosition(Point2f((yoshiPlyr->GetPosition().x) + m_Platforms[idx]->GetYoshiXPosDifference(),
												yoshiPlyr->GetPosition().y + m_Platforms[idx]->GetPlatformHeight()));
										}
										else
										{
											yoshiPlyr->SetPosition(Point2f((yoshiPlyr->GetPosition().x) + m_Platforms[idx]->GetYoshiXPosDifference(),
												yoshiPlyr->GetPosition().y + m_Platforms[idx]->GetPlatformHeight()));
										}


										break;
									}
									
								}
							
							}
						}
						
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
				if (wingedClouds->GetIsActive() == true)
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

								m_StateManager->SetState(StateManager::States::LevelPause);
								m_DrawEventStairs = true;
								m_LvlEntities[idx]->FlipIsActive();
								m_StateManager->SetState(StateManager::States::Gameplay);
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
								m_LvlEntities[idx]->FlipIsActive();
								break;
							}
						}

						if (wingedClouds->GetTypeOfCloud() == WingedClouds::Type::FlowerCloud)
						{
							m_LvlEntities.push_back(new Flower(wingedClouds->GetPosition()));

							m_LvlEntities[idx]->FlipIsActive();
							break;
						}

						if (wingedClouds->GetTypeOfCloud() == WingedClouds::Type::StarCloud)
						{
							for (int idx{ 0 }; idx < 5; idx++)
							{
								m_LvlEntities.push_back(new Star(wingedClouds->GetPosition()));
								m_LvlEntities.back()->AddVelocity(rand() % -30 + 60, (rand() % 90));
							}

							m_LvlEntities[idx]->FlipIsActive();
							break;
						}

					}
				}
			}
			if (m_LvlEntities[idx]->GetIsActive() == true)
			{
				m_LvlEntities[idx]->Update(m_LvlVertices, elapsedSec);
			}


		}

		Animate(elapsedSec);

		if (m_LevelNumber == 1)
		{
			if (m_IsUsingPipe == false)
			{
				WarpPipesCheck(true, yoshiPlyr, Point2f(2708, 348), 16, 16, Point2f(740, -520 + yoshiPlyr->GetHitBox().height));

				WarpPipesCheck(false, yoshiPlyr, Point2f(2521, -542), 16, 16, Point2f(3121, 260 - yoshiPlyr->GetHitBox().height));
			}

			else
			{
				WarpPipesUpdate(m_IsActivePipeDirectionDown,yoshiPlyr, m_ActivePipeDestinationPos, plyrCamera, elapsedSec);
			}
		}

	}

	Sound(soundManager);

	
}

void Level::Sound(SoundManager* soundManager)
{
	
	if (m_IsBGMusicOn == false)
	{
		soundManager->PlayBGMusic(SoundManager::LvlMusic::Level1);

		m_IsBGMusicOn = true;
	}

	if (m_PreviousState != StateManager::States::Gameplay)
	{
		soundManager->ResumeBGMusic();
	}

	m_PreviousState = m_StateManager->GetState();
}

void Level::PauseMusic(SoundManager* soundManager)
{
	soundManager->PauseBGMusic();
}

void Level::CoinManager(int coinRowSize, int coinColumnSize, int numberOfRedCoin, int spacingX,int spacingY,Point2f position)
{
	const int numberOfCoinsInRow = coinRowSize / (12 + spacingX);
	const int numberOfCoinsInColumn = coinColumnSize / (16 + spacingY);
	const int numberOfCoins = numberOfCoinsInRow * numberOfCoinsInColumn;

	if (numberOfCoins <= 0 || numberOfRedCoin > numberOfCoins) {
		std::cout << "The values provided can't make any coins or number of red coins exceeds total coins.\n";
		return;
	}
	// Create a vector to mark red coin positions
	std::vector<bool> isRedCoin(numberOfCoins, false);

	// Randomly mark the specified number of coins as red
	for (int i = 0; i < numberOfRedCoin; ++i) {
		int idx;
		do {idx = std::rand() % numberOfCoins;}

		while (isRedCoin[idx]);
		isRedCoin[idx] = true;
	}

	int idxCounter = 0;

	for (int col = 0; col < numberOfCoinsInColumn; ++col) 
	{
		for (int row = 0; row < numberOfCoinsInRow; ++row) 
		{
			bool isRed = isRedCoin[idxCounter];
			m_LvlEntities.push_back(new Coin(isRed, Point2f(position.x + (12 * 2 + spacingX) * row, position.y + (16 * 2 + spacingY) * col)));
			++idxCounter;
		}

	}

}

void Level::Animate(float elapsedSec) const
{
	for (int idx = 0; idx < m_LvlEntities.size(); idx++)
	{
		if (m_LvlEntities[idx]->GetIsActive() == true)
		{
			m_LvlEntities[idx]->Animate(elapsedSec);
		}
	}
}

void Level::WarpPipesCheck(bool isDownPipe, Yoshi* yoshiPlyr, Point2f pipePosition, int pipeWidth, int pipeHeight, Point2f pipeWarpDestination)
{
	
	if (utils::IsOverlapping(yoshiPlyr->GetHitBox(), Rectf(pipePosition.x, pipePosition.y, pipeWidth, pipeHeight)) == true)
	{
		if (isDownPipe == true)
		{
			if (yoshiPlyr->GetIsCrouching() == true)
			{
				m_IsUsingPipe = true;

				if (yoshiPlyr->GetIsUsingPipe() == false)
				{
					yoshiPlyr->FlipIsUsingPipe();
				}

			}
		}
			
		else
		{
			if (yoshiPlyr->GetIsJumping() == true || yoshiPlyr->GetIsHovering() == true)
			{			
				m_IsUsingPipe = true;

				if (yoshiPlyr->GetIsUsingPipe() == false)
				{
					yoshiPlyr->FlipIsUsingPipe();
				}

			}
		}

		m_ActivePipeDestinationPos = pipeWarpDestination;
		m_IsActivePipeDirectionDown = isDownPipe;
		
		
	}
}

void Level::WarpPipesUpdate(bool isDownPipe, Yoshi* yoshiPlyr, Point2f pipeWarpDestination, Camera* plyrCamera, float elapsedSec)
{
	if (m_PipeTiming < 0.1)
	{
		yoshiPlyr->SetVelocity(0, 0);
	}
	

	if (isDownPipe == true)
	{
		yoshiPlyr->SetPosition(Point2f(yoshiPlyr->GetPosition().x, yoshiPlyr->GetPosition().y - 0.1));
		m_PipeTiming += 0.1;
	}

	else
	{
		yoshiPlyr->SetPosition(Point2f(yoshiPlyr->GetPosition().x, yoshiPlyr->GetPosition().y + 0.2));
		m_PipeTiming += 0.1;
	}
	

	if (m_PipeTiming > yoshiPlyr->GetHitBox().height)
	{
		if (m_PipeTiming - yoshiPlyr->GetHitBox().height < 0.2)
		{
			yoshiPlyr->SetPosition(pipeWarpDestination);
			yoshiPlyr->SetVelocity(0, 0);
		}
		

		if (isDownPipe == true)
		{
			yoshiPlyr->SetPosition(Point2f(yoshiPlyr->GetPosition().x, yoshiPlyr->GetPosition().y - 0.1));
			m_PipeTiming += 0.1;
		}

		else
		{
			yoshiPlyr->SetPosition(Point2f(yoshiPlyr->GetPosition().x, yoshiPlyr->GetPosition().y + 2));
			m_PipeTiming += 2;
		}

		plyrCamera->CenterCamera(yoshiPlyr->GetPosition());
	}
	


	if (m_PipeTiming > yoshiPlyr->GetHitBox().height * 2)
	{
		yoshiPlyr->FlipIsUsingPipe();
		m_PipeTiming = 0;
		m_IsUsingPipe = false;
	}

}

void Level::LevelEndUpdate(Point2f yoshiPos)
{
	if (yoshiPos.x >= m_LevelEnd.x)
	{
		if (yoshiPos.y >= m_LevelEnd.y)
		{
			m_StateManager->SetState(StateManager::States::ResultsMenu);
		
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

std::vector<Entity*> Level::GetLevelEntities() 
{
	return m_LvlEntities;
}

void Level::Reset()
{
	for (int idx{ 0 }; idx < m_LvlEntities.size(); idx++)
	{
		m_LvlEntities[idx]->Reset();
	}
	m_DrawEventStairs    = false;
	m_DrawEventSunflower = false;
	m_IsBGMusicOn        = false;
}
