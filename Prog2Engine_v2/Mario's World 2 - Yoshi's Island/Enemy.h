#pragma once
#include "Entity.h"

class Yoshi;

class Enemy: public Entity
{
public:
	Enemy(bool isEdible,bool isSquashable, const std::string& texturePath, float txtHeight, float txtWidth, Point2f position);
	~Enemy() override = default;

	void virtual Animate(float elapsedSec);
	bool GetIsEdible() const;
	bool GetIsSquashable();
	void EnemyDeath();
	void EnemySwallowed();
	void EnemySpit(std::vector<Enemy*>& enemies, std::vector<Entity*>& lvlEntities,Yoshi*& yoshiplyr );
	void SetIsSpat();
	bool GetIsAlive() const;
	bool GetIsSwallowed() const;
	bool GetIsSpat() const;

private:
	bool m_IsEdible;
	bool m_IsSquashable;
	bool m_IsSwallowed{false};
	bool m_IsSpat{ false };

protected:
	bool m_IsAlive{ true };
};

