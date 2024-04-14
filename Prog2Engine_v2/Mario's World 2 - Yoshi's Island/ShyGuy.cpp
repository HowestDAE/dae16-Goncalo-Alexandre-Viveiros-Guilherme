#include "pch.h"
#include "ShyGuy.h"

ShyGuy::ShyGuy(Point2f startPos):Enemy(true,true,"EnemiesVaried2.png",19,16,startPos),m_StartPos(startPos)
{
}

ShyGuy::~ShyGuy()
{
}

void ShyGuy::Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{

	Entity::Update(platforms, elapsedSec);
	
	

	//makes the shy guy have a small patrol around a limited area from where he was placed

	m_PatrolClock += elapsedSec;

	if (m_PatrolClock > 3)
	{
		if (m_PatrolCycle == 0)
		{
			m_VelocityX = 30;

			if (m_Position.x >= m_StartPos.x + 100)
			{
				m_PatrolCycle = 1;
				m_PatrolClock = 0;
			}
		}
		
		if (m_PatrolCycle == 1)
		{
			m_VelocityX = -30;

			if (m_Position.x <= m_StartPos.x - 100)
			{
				m_PatrolCycle = 0;
				m_PatrolClock = 0;
			}
		}
	}


}

void ShyGuy::Animate()
{
	m_XTxtPos = 61;
	m_YTxtPos = 29;


}

void ShyGuy::DeathAnimation()
{
	if (m_IsAlive == false)
	{
		//TODO animation for death

		delete this;
	}
}




