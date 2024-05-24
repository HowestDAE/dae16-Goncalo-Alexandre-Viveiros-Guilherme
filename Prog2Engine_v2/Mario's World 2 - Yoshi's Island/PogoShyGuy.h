#pragma once
#include "Enemy.h"

class PogoShyGuy final :public Enemy
{
public:
	explicit PogoShyGuy(Point2f position);
	~PogoShyGuy() override = default;


	void Draw() const override;
	void Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
private:
	float m_Timer{0};
};

