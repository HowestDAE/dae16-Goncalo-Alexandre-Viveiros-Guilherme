#pragma once
#include "Entity.h"

class Egg: public Entity
{
public:
	Egg(Point2f Pos);
	~Egg();
	void Update(Point2f YoshiPos, int NumOfEggs, const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	void Animate(float elapsedSec);
private:
	float m_FrameTime{ 0 };
};

