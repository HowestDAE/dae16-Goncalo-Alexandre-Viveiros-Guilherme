#include "pch.h"
#include "EnemyManager.h"

#include "FlyingShyGuy.h"
#include "PiranhaPlant.h"
#include "PogoShyGuy.h"
#include "ShyGuy.h"
#include "WalkingTulip.h"


EnemyManager::~EnemyManager()
{
	//deletes all Shy Guys
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

			for (int idx = 0; idx < m_PiranhaPlant.size(); idx++)
			{
				m_PiranhaPlant[idx]->Update(yoshiPos);
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
		m_ShyGuy.push_back(new ShyGuy(Point2f(550, 280)));
		m_PiranhaPlant.push_back(new PiranhaPlant(Point2f(1782, 300)));
		m_WalkingTulip.push_back (new WalkingTulip(Point2f(800, 300)));
		m_PogoShyGuy.push_back (new PogoShyGuy(Point2f(500, 700)));
		m_FlyingShyGuy.push_back (new FlyingShyGuy(Point2f(500, 500), Point2f(300, 300), true));

		for (int idx = 0; idx < m_ShyGuy.size(); idx++)
		{
			m_Enemies.push_back(m_ShyGuy[idx]) ;
		}
		for (int idx = 0; idx < m_PiranhaPlant.size(); idx++)
		{
			m_Enemies.push_back(m_PiranhaPlant[idx]);
		}
		for (int idx = 0; idx < m_WalkingTulip.size(); idx++)
		{
			m_Enemies.push_back(m_WalkingTulip[idx]);
		}
		for (int idx = 0; idx < m_FlyingShyGuy.size(); idx++)
		{
			m_Enemies.push_back(m_FlyingShyGuy[idx]);
		}
		for (int idx = 0; idx < m_PogoShyGuy.size(); idx++)
		{
			m_Enemies.push_back(m_PogoShyGuy[idx]);
		}
		
	
	}


}

std::vector<Enemy*>& EnemyManager::GetEnemyVector()
{
	return m_Enemies;
}

void EnemyManager::AddEnemy(Point2f yoshiPos,bool isYoshiRight)
{
	float operand;
	if (isYoshiRight == true)
	{
		operand = 100;
	}

	else
	{
		operand = -100;
	}

	m_Enemies.push_back(new ShyGuy(Point2f(yoshiPos.x + operand, yoshiPos.y + 100)));
}

