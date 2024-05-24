#pragma once
#include "Enemy.h"

class WalkingTulip final : public Enemy
{
public:
	explicit WalkingTulip(Point2f position);
	~WalkingTulip() override = default;


	void Animate(float elapsedSec) override;
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec) override;
private:
};

