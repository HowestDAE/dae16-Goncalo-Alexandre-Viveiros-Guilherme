#include "pch.h"
#include "EnemyManager.h"

#include "FlyingShyGuy.h"
#include "PiranhaPlant.h"
#include "PogoShyGuy.h"
#include "ShyGuy.h"
#include "WalkingTulip.h"


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
			m_Enemies[idx]->Draw();

		}
	}

	
}

void EnemyManager::Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec,Point2f yoshiPos)
{
	
	//Updates Enemies
	for (int idx{ 0 }; idx < m_Enemies.size(); idx++)
	{
		if (m_Enemies[idx]->GetIsAlive() == true)
		{

			if (auto piranhaPlant = dynamic_cast<::PiranhaPlant*>(m_Enemies[idx]))
			{
				piranhaPlant->Update(yoshiPos);
			}

			m_Enemies[idx]->Update(platforms, elapsedSec);
			m_Enemies[idx]->Animate(elapsedSec);
				

			
		}
		else
		{
			
		}
		
	}

	
}

void EnemyManager::SpawnEnemies(int levelNumber)
{
	if (levelNumber == 1)
	{
		m_Enemies.push_back(new ShyGuy(Point2f(550, 280)));
		m_Enemies.push_back(new PiranhaPlant(Point2f(1782, 300)));
		m_Enemies.push_back(new WalkingTulip(Point2f(800, 300)));
		m_Enemies.push_back(new PogoShyGuy(Point2f(500, 700)));
		m_Enemies.push_back(new FlyingShyGuy(Point2f(500, 500), Point2f(300, 300), true));
		
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

	m_Enemies.push_back(new ShyGuy(Point2f(yoshiPos.x + operand, yoshiPos.y + 100)));
}

