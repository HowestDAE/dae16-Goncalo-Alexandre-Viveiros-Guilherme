#pragma once
#include "Entity.h"

class Stars:public Entity
{
public:
	explicit Stars(Point2f position);
	~Stars() override = default;
	void Draw() const override;
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Animate(float elapsedSec) override;
};

