#pragma once
#include "Entity.h"

class Yoshi;

class Enemy: public Entity
{
public:
	Enemy(bool isEdible,bool isSquashable, const std::string& texturePath, float txtHeight, float txtWidth, Point2f position);
	~Enemy() override = default;

	void Animate(float elapsedSec) override;
	bool GetIsEdible() const;
	bool GetIsSquashable() const;
	void EnemyDeath();
	void EnemySwallowed();
	void EnemySpit(std::vector<Enemy*>& enemies, std::vector<Entity*>& lvlEntities,Yoshi*& yoshiplyr );
	void SetIsSpat();
	void SetIsOnScreenFalse();
	void SetIsOnScreenTrue();
	bool GetIsSwallowed() const;
	bool GetIsSpat() const;
	bool GetIsOnScreen() const;
	void Reset() override;

private:
	bool m_IsEdible;
	bool m_IsSquashable;
	bool m_IsSwallowed{false};
	bool m_IsSpat{ false };
	bool m_IsOnScreen{ false };

	bool m_ResetEdible;
	bool m_ResetSquashable;

};


