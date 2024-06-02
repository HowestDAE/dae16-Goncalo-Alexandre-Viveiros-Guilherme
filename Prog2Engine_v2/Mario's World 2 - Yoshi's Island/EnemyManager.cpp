#include "pch.h"
#include "EnemyManager.h"

#include "Entity.h"
#include "FlyingShyGuy.h"
#include "PiranhaPlant.h"
#include "PogoShyGuy.h"
#include "ShyGuy.h"
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
		if (m_Enemies[idx]->GetIsAlive() == true)
		{
			if (m_Enemies[idx]->GetIsSwallowed() == false)
			{

				if (m_Enemies[idx]->GetIsOnScreen() == true)
				{
					m_Enemies[idx]->Draw();
				}
				
				utils::DrawRect(m_Enemies[idx]->GetHitBox());
			}
			
			utils::DrawRect(m_Enemies[idx]->GetHitBox());
		}
		utils::DrawRect(m_Enemies[idx]->GetHitBox());
	}

	
}

void EnemyManager::Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec,Yoshi*& yoshiplyr, std::vector<Entity*>& lvlEntities)
{
	
	//Updates Enemies
	for (int idx{ 0 }; idx < m_Enemies.size(); idx++)
	{
		if (m_Enemies[idx]->GetIsAlive() == true)
		{
			if (m_Enemies[idx]->GetIsSwallowed() == false)
			{
				if (const auto piranhaPlant = dynamic_cast<::PiranhaPlant*>(m_Enemies[idx]))
				{
					piranhaPlant->Update(yoshiplyr->GetPosition());
				}
				if (m_Enemies[idx]->GetIsOnScreen() == true)
				{
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

		else
		{
			
		}
		
	}

	for (int idx{ 0 }; idx < m_Enemies.size(); idx++)
	{
		if (m_Enemies[idx]->GetPosition().x > yoshiplyr->GetPosition().x - 300 && m_Enemies[idx]->GetPosition().x < yoshiplyr->GetPosition().x + 800)
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
	
}

void EnemyManager::SpawnEnemies(int levelNumber)
{
	if (levelNumber == 1)
	{
		m_Enemies.push_back(new ShyGuy(Point2f(912, 255),100));
		m_Enemies.push_back(new ShyGuy(Point2f(1100, 255),100));
		m_Enemies.push_back(new ShyGuy(Point2f(1340, 380),10));
		m_Enemies.push_back(new WalkingTulip(Point2f(1554, 315)));
		m_Enemies.push_back(new PiranhaPlant(Point2f(1785, 280)));
		m_Enemies.push_back(new WalkingTulip(Point2f(2335, 349)));
		m_Enemies.push_back(new ShyGuy(Point2f(2249, 443), 10));
		m_Enemies.push_back(new PiranhaPlant(Point2f(2535, 252)));
		m_Enemies.push_back(new PiranhaPlant(Point2f(2535, 381))); //TODO ADD FLIPPED
		m_Enemies.push_back(new FlyingShyGuy(Point2f(865, 1663), Point2f(900, 1443), false)); //TODO check if non cyclic works
		m_Enemies.push_back(new ShyGuy(Point2f(2889, 513), 100));
		m_Enemies.push_back(new FlyingShyGuy(Point2f(1240, -650), Point2f(1300, -650), true));
		m_Enemies.push_back(new ShyGuy(Point2f(1443, -758), 100));
		m_Enemies.push_back(new ShyGuy(Point2f(1879,-758), 100));
		m_Enemies.push_back(new FlyingShyGuy(Point2f(1800, -650), Point2f(1900, -650), true));
		m_Enemies.push_back(new PiranhaPlant(Point2f(3328, 480)));
		m_Enemies.push_back(new PiranhaPlant(Point2f(3395, 338)));
		m_Enemies.push_back(new PiranhaPlant(Point2f(3747, 406)));
		//TODO add shy guy pipe spawn
		m_Enemies.push_back(new WalkingTulip(Point2f(4774, 254)));
		m_Enemies.push_back(new WalkingTulip(Point2f(5025, 255)));
		m_Enemies.push_back(new PiranhaPlant(Point2f(5052, 568)));
		m_Enemies.push_back(new ShyGuy(Point2f(5437, 818), 100));
		m_Enemies.push_back(new ShyGuy(Point2f(5554, 765), 100));
		m_Enemies.push_back(new PiranhaPlant(Point2f(5764, 729)));
		m_Enemies.push_back(new PiranhaPlant(Point2f(5764, 890))); //TODO ADD FLIPPED
		m_Enemies.push_back(new PogoShyGuy(Point2f(6271, 700)));
		m_Enemies.push_back(new PogoShyGuy(Point2f(6395, 672)));
		m_Enemies.push_back(new ShyGuy(Point2f(6612, 672), 100));
		m_Enemies.push_back(new ShyGuy(Point2f(6784, 671), 100));
		m_Enemies.push_back(new ShyGuy(Point2f(7000, 743), 100));

		
		
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

