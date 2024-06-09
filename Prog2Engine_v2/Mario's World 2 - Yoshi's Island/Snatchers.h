#pragma once
#include "Enemy.h"

class Mario;

class Snatchers final :public Enemy
{
public:
	explicit Snatchers(Point2f position);
	~Snatchers() override = default;
	void Snatch(Mario*& babyMarioPointer);
	void Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Animate(float elapsedSec) override;
	bool GetGrabbedMario();
	void Reset() override;

private:
	bool m_GrabbedMario {false};
};

