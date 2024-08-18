#pragma once
#include "Entity.h"

class Enemy;

class Boulder final:public Entity
{
public:
	explicit Boulder(Point2f startPos);
	~Boulder() override = default;
	void Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Hitcheck(const std::vector<Enemy*> enemies) const;
	void Animate(float elapsedSec) override;
	void Reset() override;

private:
	bool m_IsFalling{false};
	float m_LastYPosition;

};

