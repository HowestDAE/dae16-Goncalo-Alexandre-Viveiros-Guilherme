#include "pch.h"
#include "Enemy.h"


Enemy::Enemy(const bool isEdible, const bool isSquashable, const std::string& TexturePath, const float txtHeight, const float txtWidth, const Point2f position):
Entity(TexturePath, txtHeight, txtWidth, position),
m_IsEdible(isEdible),
m_IsSquashable(isSquashable)
{

}

Enemy::~Enemy()
{
}

bool Enemy::GetIsEdible() const
{
	return m_IsEdible;
}

bool Enemy::GetIsSquashable()
{
	return m_IsSquashable;
}

void Enemy::EnemyDeath()
{
	m_IsAlive = false;
}

