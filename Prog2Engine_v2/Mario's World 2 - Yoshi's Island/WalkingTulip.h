#pragma once
#include "Enemy.h"

class WalkingTulip: public Enemy
{
public:
	WalkingTulip(Point2f position);
	~WalkingTulip();
	void Animate(float elapsedSec) override;
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec) override;
private:
};

