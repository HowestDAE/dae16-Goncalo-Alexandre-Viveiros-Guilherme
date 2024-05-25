#include "pch.h"
#include "Boulder.h"

#include "Enemy.h"

Boulder::Boulder(Point2f startPos):Entity("Boulder.png",32,32,startPos)
{
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

void Boulder::AddVelocity(bool isYoshiFacingRight)
{
	if (isYoshiFacingRight == true)
	{
		if (m_VelocityX < 80)
		{
			m_VelocityX += 2;
		}
		
	}

	else
	{
		if (m_VelocityX < 80)
		{
			m_VelocityX -= 2;
		}
	}
}
