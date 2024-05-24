#pragma once
#include "Enemy.h"


class PiranhaPlant final :public Enemy
{
public:
	PiranhaPlant(Point2f position);
	~PiranhaPlant() override = default;

	void Draw()const override;
	void Update(Point2f yoshiPos);
	void Animate(float elapsedSec) override;
private:
	float m_XTxtPos2{ 0 };
	float m_YTxtPos2{ 0 };
	float m_TxtHeight2{ 12 };
	float m_TxtWidth2{ 16 };
};

