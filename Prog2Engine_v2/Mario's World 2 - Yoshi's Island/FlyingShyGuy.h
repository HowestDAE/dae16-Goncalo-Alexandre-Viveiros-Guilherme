#pragma once
#include "Enemy.h"

class FlyingShyGuy:public Enemy
{
public:
	FlyingShyGuy(Point2f pos,Point2f endPoint,bool isCyclic);
	~FlyingShyGuy();
	void Update();
	void Animate(float elapsedSec) override;
private:
	bool m_IsCyclic;
	bool m_IsCycleDone{ false };
	Point2f m_StartPoint;
	Point2f m_EndPoint;
};

