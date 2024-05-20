#include "pch.h"
#include "EnemyManager.h"
#include "ShyGuy.h"

EnemyManager::EnemyManager(std::vector<Enemy*>& enemies)
{
	m_Enemies = enemies;
}

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

void EnemyManager::Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec)
{
	//Updates Shy Guys
	for (int idx{ 0 }; idx < m_Enemies.size(); idx++)
	{
		if (m_Enemies[idx]->GetIsAlive() == true)
		{
			m_Enemies[idx]->Update(platforms, elapsedSec);
			m_Enemies[idx]->Animate(elapsedSec);
		}
		else
		{
			
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

