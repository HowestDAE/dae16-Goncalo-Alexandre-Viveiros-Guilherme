#include "pch.h"
#include "Enemy.h"
#include "Yoshi.h"
#include "WingedClouds.h"
#include "Flowers.h"
#include "Coin.h"


Enemy::Enemy(const bool isEdible, const bool isSquashable, const std::string& texturePath, const float txtHeight, const float txtWidth, const Point2f position) :
	Entity(texturePath, txtHeight, txtWidth, position),
	m_IsEdible(isEdible),
	m_IsSquashable(isSquashable),
	m_ResetEdible(isEdible),
	m_ResetSquashable(isSquashable)
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

void Enemy::EnemySpit(std::vector<Enemy*>& enemies, std::vector<Entity*>& lvlEntities, Yoshi*& yoshiplyr, float elapsedSec)
{
	if (m_IsSpat == true)
	{
		//shoots out enemy depending on yoshis state
		if (yoshiplyr->GetIsFacingRight() == true)
		{
			m_Position.x = yoshiplyr->GetPosition().x + yoshiplyr->GetHitBox().width + 2;
			m_Position.y = yoshiplyr->GetPosition().y + 20;

			m_VelocityX = 60.f;
			if (yoshiplyr->GetIsLookingUp())
			{
				m_VelocityY = 120.f;
				m_IsThrown = true;
			}

			else
			{
				m_IsRolling = true;
			}
		}

		else
		{
			m_Position.x = yoshiplyr->GetPosition().x - m_Hitbox.width;
			m_Position.y = yoshiplyr->GetPosition().y;

			m_VelocityX = -60.f;
			if (yoshiplyr->GetIsLookingUp())
			{
				m_VelocityY = 60.f;
				m_IsThrown = true;
			}
			else
			{
				m_IsRolling = true;
			}
		}

		m_IsSwallowed = false;

		m_IsSpat = false;
	}

	else
	{
		if (m_IsRolling == true)
		{
			m_ImmunityTimer += elapsedSec;
			
			m_AngZ = 1;

			if (yoshiplyr->GetIsFacingRight() == true)
			{
				m_VelocityX = 320;
				m_AngleDeg += -5;
			}

			else
			{
				m_VelocityX = -320;
				m_AngleDeg += 5;
			}


			if (m_IsOnScreen == false)
			{
				m_IsActive = false;
			}

			if (m_ImmunityTimer > 3)
			{
				m_IsRolling = false;
				EnemyDeath();
			}
		}


		if (m_IsThrown == true)
		{
			m_ImmunityTimer += elapsedSec;
			if (m_IsSpat == true)
			{
				if (m_ImmunityTimer > 2)
				{
					m_IsThrown = false;
					m_ImmunityTimer = 0;
				}
			}

			if (yoshiplyr->GetIsFacingRight() == true)
			{
				m_VelocityX = 320;
				
			}
			else
			{
				m_VelocityX = -320;
			}

			if (m_ImmunityTimer < 0.2)
			{
				m_VelocityY = 620;
			}
		}


		for (int idx{ 0 }; idx < lvlEntities.size(); idx++)
		{
			if (lvlEntities[idx]->GetIsActive() == true)
			{
				if (utils::IsOverlapping(m_Hitbox, lvlEntities[idx]->GetHitBox()))
				{
					if (const auto wingedClouds = dynamic_cast<::WingedClouds*>(lvlEntities[idx]))
					{
						wingedClouds->SetIsHit();
						EnemyDeath();
					}

					if (utils::IsOverlapping(m_Hitbox, lvlEntities[idx]->GetHitBox()))
					{
						if (const auto flowers = dynamic_cast<::Flower*>(lvlEntities[idx]))
						{
							lvlEntities[idx]->FlipIsActive();

							yoshiplyr->AddFlower();

							EnemyDeath();
							break;
						}

						if (const auto coins = dynamic_cast<::Coin*>(lvlEntities[idx]))
						{
							if (coins->GetIsRedCoin() == true)
							{
								yoshiplyr->AddRedCoin();
							}
							else
							{
								yoshiplyr->AddCoin();
							}
							lvlEntities[idx]->FlipIsActive();
							break;
						}

					}
				}
			}

			if (enemies[idx]->GetIsActive() == true)
			{
				for (int idx{ 0 }; idx < enemies.size(); idx++)
				{
					if (enemies[idx]->GetIsThrown() == false && enemies[idx]->GetIsRolling() == false)
					{
						if (utils::IsOverlapping(m_Hitbox, enemies[idx]->GetHitBox()))
						{
							enemies[idx]->EnemyDeath();
							EnemyDeath();
						}
					}

				}
			}
			

		}

	}
}

void Enemy::Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	Entity::Update(platforms, elapsedSec);
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

bool Enemy::GetIsRolling() const
{
	return m_IsRolling;
}

bool Enemy::GetIsThrown() const
{
	return m_IsThrown;
}

bool Enemy::GetIsOnScreen() const
{
	return m_IsOnScreen;
}


void Enemy::Reset()
{
	Entity::Reset();

	m_IsEdible     = m_ResetEdible;
	m_IsSquashable = m_ResetSquashable;
	m_IsSwallowed  = false;
	m_IsSpat       = false;
	m_IsOnScreen   = false;
}

