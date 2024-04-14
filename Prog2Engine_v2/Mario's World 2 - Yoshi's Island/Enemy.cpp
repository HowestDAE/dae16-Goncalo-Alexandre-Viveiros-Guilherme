#include "pch.h"
#include "Enemy.h"


Enemy::Enemy(bool isEdible, bool isSquashable, const std::string& TexturePath, float txtHeight, float txtWidth, Point2f position):
Entity(TexturePath, txtHeight, txtWidth, position),
m_IsEdible(isEdible),
m_IsSquashable(isSquashable)
{
}

Enemy::~Enemy()
{
}

bool Enemy::GetIsEdible()
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

