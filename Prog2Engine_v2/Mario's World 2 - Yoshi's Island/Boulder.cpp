#include "pch.h"
#include "Boulder.h"

#include "Enemy.h"

Boulder::Boulder(Point2f startPos):Entity("Boulder.png",32,32,startPos),
m_LastYPosition{startPos.y}
{
}

void Boulder::Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	Entity::Update(platforms, elapsedSec);

	if (m_LastYPosition + 1 < m_Position.y || m_LastYPosition - 1  > m_Position.y)
	{
		m_VelocityX += 21 ;

		m_LastYPosition = m_Position.y;

	}

}

void Boulder::Hitcheck(const std::vector<Enemy*>& enemies) const
{
	for (int idx{0}; idx < enemies.size(); idx++)
	{
		if (m_VelocityX < 10 || m_VelocityX > 10)
		{
			if (utils::IsOverlapping(m_Hitbox, enemies[idx]->GetHitBox()) == true)
			{
				enemies[idx]->EnemyDeath();
			}
		}
		
	}
	
}

void Boulder::Animate(float elapsedSec)
{
	m_AngZ = 1;

	if (m_VelocityX > 0)
	{
		m_AngleDeg -= 100 * elapsedSec;
	}


	if (m_VelocityX < 0)
	{
		m_AngleDeg += 100 * elapsedSec;
	}
}

void Boulder::Reset()
{
	Entity::Reset();

	m_LastYPosition = m_Position.y;

}
