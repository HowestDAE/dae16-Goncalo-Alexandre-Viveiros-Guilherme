#pragma once
#include "Entity.h"

class Star final :public Entity
{
public:
	explicit Star(Point2f position);
	~Star() override = default;
	void Draw() const override;
	void Animate(float elapsedSec) override;
	void Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
};

