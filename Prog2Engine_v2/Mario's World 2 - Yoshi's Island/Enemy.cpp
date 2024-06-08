#include "pch.h"
#include "Enemy.h"
#include "Yoshi.h"


Enemy::Enemy(const bool isEdible, const bool isSquashable, const std::string& texturePath, const float txtHeight, const float txtWidth, const Point2f position):
Entity(texturePath, txtHeight, txtWidth, position),
m_IsEdible(isEdible),
m_IsSquashable(isSquashable)
{

}

void Enemy::Animate(float elapsedSec)
{
}

bool Enemy::GetIsEdible() const
{
	return m_IsEdible;
}

bool Enemy::GetIsSquashable() const
{
	return m_IsSquashable;
}

void Enemy::EnemyDeath()
{
	m_IsActive = false;
}

void Enemy::EnemySwallowed()
{
	m_IsSwallowed = true;
}

void Enemy::EnemySpit(std::vector<Enemy*>& enemies, std::vector<Entity*>& lvlEntities,Yoshi* &yoshiplyr)
{
	if (m_IsSpat == true)
	{
		if (m_IsSwallowed == true)
		{
			//shoots out enemy depending on yoshis state
			if (yoshiplyr->GetIsFacingRight() == true)
			{
				m_Position.x = yoshiplyr->GetPosition().x + yoshiplyr->GetHitBox().width + 2;
				m_Position.y = yoshiplyr->GetPosition().y;

				m_VelocityX = 300;
				if (yoshiplyr->GetIsLookingUp())
				{
					m_VelocityY = 300;
				}
			}

			else
			{
				m_Position.x = yoshiplyr->GetPosition().x - m_Hitbox.width;
				m_Position.y = yoshiplyr->GetPosition().y;

				m_VelocityX = -300;
				if (yoshiplyr->GetIsLookingUp())
				{
					m_VelocityY = 300;
				}
			}

			m_IsSwallowed = false;
		}
		
	}
	

}

void Enemy::SetIsSpat()
{
	m_IsSpat = true;
}

void Enemy::SetIsOnScreenFalse()
{
	m_IsOnScreen = false;
}

void Enemy::SetIsOnScreenTrue()
{
	m_IsOnScreen = true;
}

bool Enemy::GetIsSwallowed() const
{
	return m_IsSwallowed;
}

bool Enemy::GetIsSpat() const
{
	return m_IsSpat;
}

bool Enemy::GetIsOnScreen() const
{
	return m_IsOnScreen;
}
