#pragma once
#include "Entity.h"

class Flower final : public Entity
{
public:
	explicit Flower(Point2f position);
	~Flower() override = default;
	void Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;

private:

};

