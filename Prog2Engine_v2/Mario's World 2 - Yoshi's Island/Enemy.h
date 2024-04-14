#pragma once
#include "Entity.h"

class Enemy: public Entity
{
public:
	Enemy(bool isEdible,bool isSquashable, const std::string& TexturePath, float txtHeight, float txtWidth, Point2f position);
	virtual ~Enemy();
	bool GetIsEdible();
	bool GetIsSquashable();
	void EnemyDeath();
private:
	bool m_IsEdible;
	bool m_IsSquashable;

protected:
	bool m_IsAlive{ true };
};

