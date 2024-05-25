#pragma once
#include "Entity.h"

class Enemy: public Entity
{
public:
	Enemy(bool isEdible,bool isSquashable, const std::string& texturePath, float txtHeight, float txtWidth, Point2f position);
	~Enemy() override = default;

	void virtual Animate(float elapsedSec);
	bool GetIsEdible() const;
	bool GetIsSquashable();
	void EnemyDeath();
	bool GetIsAlive();

private:
	bool m_IsEdible;
	bool m_IsSquashable;

protected:
	bool m_IsAlive{ true };
};

