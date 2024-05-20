#pragma once
#include "Enemy.h"

class PogoShyGuy:public Enemy
{
public:
	PogoShyGuy(Point2f position);
	~PogoShyGuy();
	void Draw() const override;
	void Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
private:
	float m_Timer{0};
};

