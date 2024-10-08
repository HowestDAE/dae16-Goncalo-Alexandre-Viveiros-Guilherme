#include "pch.h"
#include "ShyGuy.h"

ShyGuy::ShyGuy(const Point2f startPos,float patrolRange):Enemy(true,true,"EnemiesVaried2.png",19,21,startPos),
m_PatrolRange(patrolRange),
m_StartPos(startPos)
{
}

void ShyGuy::Update(const std::vector<std::vector<Point2f>>& platforms, const float elapsedSec)
{

	Enemy::Update(platforms, elapsedSec);


	if (m_IsThrown == false || m_IsRolling == false)
	{
		//makes the shy guy have a small patrol around a limited area from where he was placed
		m_PatrolClock += elapsedSec;

		if (m_PatrolRange > 0)
		{
			if (m_PatrolClock > 3)
			{
				if (m_PatrolCycle == 0)
				{
					m_VelocityX = 30;

					if (m_Position.x > m_StartPos.x + m_PatrolRange)
					{
						m_PatrolCycle = 1;
						m_PatrolClock = 0;
						m_VelocityX = 0;
						m_XTxtPos = 61;
					}
				}
			}

			if (m_PatrolClock > 3)
			{
				if (m_PatrolCycle == 1)
				{
					m_VelocityX = -30;

					if (m_Position.x < m_StartPos.x - m_PatrolRange)
					{
						m_PatrolCycle = 0;
						m_PatrolClock = 0;
						m_VelocityX = 0;
						m_XTxtPos = 61;
					}
				}
			}
		}
	}
	
	


}

void ShyGuy::Animate(float elapsedSec)
{
	if (m_XTxtPos >= m_TxtWidth * 5 || m_XTxtPos <61)
	{
		m_XTxtPos = 61;
	}

	m_YTxtPos = 29;
	if (m_VelocityX > 0 || m_VelocityX < 0)
	{
		m_FrameTime += elapsedSec;

		if (m_FrameTime > 0.3)
		{
			m_XTxtPos += m_TxtWidth;
			m_FrameTime = 0;
		}
	}
	


}

void ShyGuy::Reset()
{
	Enemy::Reset();

	m_PatrolClock = 3;
	m_PatrolCycle = 0;
}





