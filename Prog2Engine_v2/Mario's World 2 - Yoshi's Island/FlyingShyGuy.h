#pragma once
#include "Enemy.h"

class FlyingShyGuy final :public Enemy
{
public:
	FlyingShyGuy(Point2f pos,Point2f endPoint,bool isCyclic);
	~FlyingShyGuy() override;


	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Animate(float elapsedSec) override;
	void Reset() override;
private:
	bool m_IsCyclic;
	bool m_IsCycleDone { false };
	Point2f m_HoldPoint;
	Point2f m_StartPoint;
	Point2f m_EndPoint;
};

