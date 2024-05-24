#pragma once
#include "Enemy.h"

class ShyGuy final :public Enemy
{
public:
	explicit ShyGuy(Point2f startPos);
	~ShyGuy() override = default;


	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Animate(float elapsedSec) override;
	
private:
	float m_PatrolClock{ 0 };
	int m_PatrolCycle{ 0 };
	Point2f m_StartPos;
	float lastYPosition{};
};

