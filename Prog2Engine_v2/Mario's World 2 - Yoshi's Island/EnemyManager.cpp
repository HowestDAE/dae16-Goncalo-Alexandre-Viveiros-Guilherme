#include "pch.h"
#include "EnemyManager.h"

#include "Entity.h"
#include "FlyingShyGuy.h"
#include "Mario.h"
#include "PiranhaPlant.h"
#include "PogoShyGuy.h"
#include "ShyGuy.h"
#include "Snatchers.h"
#include "WalkingTulip.h"
#include "Yoshi.h"


EnemyManager::~EnemyManager()
{
	//deletes all Enemies
	for (int idx{ 0 }; idx < m_Enemies.size(); idx++)
	{
		delete m_Enemies[idx];
	}

}

void EnemyManager::Draw() const
{
	for (int idx{ 0 }; idx < m_Enemies.size(); idx++)
	{
		if (m_Enemies[idx]->GetIsActive() == true)
		{
			if (m_Enemies[idx]->GetIsSwallowed() == false)
			{

				if (m_Enemies[idx]->GetIsOnScreen() == true)
				{
					m_Enemies[idx]->Draw();
				}

				
			}

		}
		
	}

	
}

void EnemyManager::Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec,Yoshi*& yoshiplyr, std::vector<Entity*>& lvlEntities, SoundManager*& soundManager,Mario*& babyMarioPointer)
{
	
	//Updates Enemies
	for (int idx{ 0 }; idx < m_Enemies.size(); idx++)
	{
		if (m_Enemies[idx]->GetIsActive() == true)
		{
			if (m_Enemies[idx]->GetIsSwallowed() == false)
			{
				if (m_Enemies[idx]->GetIsOnScreen() == true)
				{
				if (const auto piranhaPlant = dynamic_cast<::PiranhaPlant*>(m_Enemies[idx]))
				{
					piranhaPlant->Update(elapsedSec,yoshiplyr->GetPosition(),soundManager);
				}
				
					m_Enemies[idx]->Update(platforms, elapsedSec);
					m_Enemies[idx]->Animate(elapsedSec);
				}
			}

			if (m_Enemies[idx]->GetIsSwallowed() == true)
			{
				if (yoshiplyr->GetIsEnemySpatOut() == true)
				{
					m_Enemies[idx]->SetIsSpat();
					yoshiplyr->EmptyMouth();
				}
			}


			if (m_Enemies[idx]->GetIsSpat() == true)
			{
				m_Enemies[idx]->EnemySpit(m_Enemies,lvlEntities,yoshiplyr);
			}
		}

		if (const auto snatchers = dynamic_cast<::Snatchers*>(m_Enemies[idx]))
		{
			if (yoshiplyr->GetMarioTimer() == 0)
			{
				snatchers->Snatch(babyMarioPointer);
				snatchers->Update(platforms,elapsedSec);

				if (snatchers->GetGrabbedMario() == true)
				{
					if (snatchers->GetIsOnScreen() == false)
					{
						m_YoshiLost = true;
					}
				}
			}
			else
			{
				snatchers->SetPosition(Point2f(babyMarioPointer->GetPosition().x + 600, babyMarioPointer->GetPosition().y + 500));
			}
		}
	}

	for (int idx{ 0 }; idx < m_Enemies.size(); idx++)
	{
		if (m_Enemies[idx]->GetPosition().x > yoshiplyr->GetPosition().x - 650 && m_Enemies[idx]->GetPosition().x < yoshiplyr->GetPosition().x + 650)
		{
			if (m_Enemies[idx]->GetPosition().y > yoshiplyr->GetPosition().y - 400 && m_Enemies[idx]->GetPosition().y < yoshiplyr->GetPosition().y + 400)
			{
				m_Enemies[idx]->SetIsOnScreenTrue();

			}
			else
			{
				m_Enemies[idx]->SetIsOnScreenFalse();
			}
		}
		else
		{
			m_Enemies[idx]->SetIsOnScreenFalse();
		}
	}

	//Spawn Points
	if (m_LevelNumber == 1)
	{
		SpawnZone(yoshiplyr->GetEggAmount(), yoshiplyr->GetPosition(), elapsedSec, Point2f(4284, 285));
	}
	
}


void EnemyManager::SpawnEnemies(int levelNumber)
{
	m_LevelNumber = levelNumber;
	m_ResetLevelNumber = levelNumber;
	m_Enemies.push_back(new Snatchers (Point2f(0, 2000)));
	if (levelNumber == 1)
	{
		m_Enemies.push_back(new ShyGuy(Point2f(912, 255),100));
		m_Enemies.push_back(new ShyGuy(Point2f(1100, 255),100));
		m_Enemies.push_back(new ShyGuy(Point2f(1340, 380),5));
		m_Enemies.push_back(new WalkingTulip(Point2f(1554, 315)));
		m_Enemies.push_back(new PiranhaPlant(Point2f(1785, 280),false));
		m_Enemies.push_back(new WalkingTulip(Point2f(2335, 349)));
		m_Enemies.push_back(new ShyGuy(Point2f(2249, 443), 5));
		m_Enemies.push_back(new PiranhaPlant(Point2f(2535, 252),false));
		m_Enemies.push_back(new PiranhaPlant(Point2f(2535, 310),true)); //TODO ADD FLIPPED
		m_Enemies.push_back(new FlyingShyGuy(Point2f(865, 1663), Point2f(900, 1443), false)); //TODO check if non cyclic works
		m_Enemies.push_back(new ShyGuy(Point2f(2889, 513), 100));
		m_Enemies.push_back(new FlyingShyGuy(Point2f(1240, -650), Point2f(1300, -650), true));
		m_Enemies.push_back(new ShyGuy(Point2f(1443, -758), 100));
		m_Enemies.push_back(new ShyGuy(Point2f(1879,-758), 100));
		m_Enemies.push_back(new FlyingShyGuy(Point2f(1800, -650), Point2f(1900, -650), true));
		m_Enemies.push_back(new PiranhaPlant(Point2f(3328, 480),false));
		m_Enemies.push_back(new PiranhaPlant(Point2f(3395, 338),false));
		m_Enemies.push_back(new PiranhaPlant(Point2f(3747, 406),false));
		//TODO add shy guy pipe spawn
		m_Enemies.push_back(new WalkingTulip(Point2f(4774, 254)));
		m_Enemies.push_back(new WalkingTulip(Point2f(5025, 255)));
		m_Enemies.push_back(new PiranhaPlant(Point2f(5052, 568), false));
		m_Enemies.push_back(new ShyGuy(Point2f(5437, 818), 100));
		m_Enemies.push_back(new ShyGuy(Point2f(5554, 765), 100));
		m_Enemies.push_back(new PiranhaPlant(Point2f(5764, 729), false));
		m_Enemies.push_back(new PiranhaPlant(Point2f(5764, 890),true)); //TODO ADD FLIPPED
		m_Enemies.push_back(new PogoShyGuy(Point2f(6271, 700)));
		m_Enemies.push_back(new PogoShyGuy(Point2f(6395, 672)));
		m_Enemies.push_back(new ShyGuy(Point2f(6612, 672), 100));
		m_Enemies.push_back(new ShyGuy(Point2f(6784, 671), 100));
		m_Enemies.push_back(new ShyGuy(Point2f(7000, 743), 100));

		
		
	}


}

void EnemyManager::SpawnZone(int yoshiEggAmount, Point2f yoshiPos, float elapsedSec, Point2f spawnZoneLocation)
{
	if (yoshiPos.x + 250 > spawnZoneLocation.x && yoshiPos.x - 250 < spawnZoneLocation.x )
	{
		if (yoshiPos.y + 100 > spawnZoneLocation.y && yoshiPos.y - 100 < spawnZoneLocation.y)
		{
			if (yoshiEggAmount < 6)
			{
				m_SpawnTimer += elapsedSec;

				if (m_SpawnTimer > 5)
				{
					m_Enemies.push_back(new ShyGuy(spawnZoneLocation, 100));
					m_SpawnTimer = 0;
				}
			}
		}
		else
		{
			m_SpawnTimer = 0;
		}
	}

	else
	{
		m_SpawnTimer = 0;
	}
}

std::vector<Enemy*>& EnemyManager::GetEnemyVector()
{
	return m_Enemies;
}

void EnemyManager::AddEnemy(Point2f yoshiPos, bool isYoshiFacingRight)
{
	float operand;
	if (isYoshiFacingRight == true)
	{
		operand = 100;
	}

	else
	{
		operand = -100;
	}

	m_Enemies.push_back(new ShyGuy(Point2f(yoshiPos.x + operand, yoshiPos.y + 100), 0));
}

bool EnemyManager::GetHasYoshiLost() const
{
	return m_YoshiLost;
}

void EnemyManager::Reset()
{
	for (int idx{0}; idx < m_Enemies.size(); idx++)
	{
		m_Enemies[idx]->Reset();
	}
	m_SpawnTimer  = 0;
	m_LevelNumber = m_ResetLevelNumber;
	m_YoshiLost  =  false;
}

