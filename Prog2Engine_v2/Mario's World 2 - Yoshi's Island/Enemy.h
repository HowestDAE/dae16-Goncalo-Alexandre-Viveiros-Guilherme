#pragma once
#include "Entity.h"

class Enemy: public Entity
{
public:
	Enemy(bool isEdible,bool isSquashable, const std::string& TexturePath, float txtHeight, float txtWidth, Point2f position);
	virtual ~Enemy() override;
	bool GetIsEdible() const;
	bool GetIsSquashable();
	void EnemyDeath();
	bool GetIsAlive();
	bool GetIsDeathHandlingDone();
private:
	bool m_IsEdible;
	bool m_IsSquashable;

protected:
	bool m_IsAlive{ true };
	bool m_IsDeathHandlingDone{ false };
};

