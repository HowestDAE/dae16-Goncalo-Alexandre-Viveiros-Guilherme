#pragma once
#include "Enemy.h"

class ShyGuy:public Enemy
{
public:
	ShyGuy(Point2f startPos);
	~ShyGuy();
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	void Animate();
	void DeathAnimation() const;
private:
	float m_PatrolClock{ 0 };
	int m_PatrolCycle{ 0 };
	Point2f m_StartPos;
};

