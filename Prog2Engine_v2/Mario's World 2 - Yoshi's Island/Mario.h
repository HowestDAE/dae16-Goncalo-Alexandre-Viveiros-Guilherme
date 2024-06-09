#pragma once
#include "Entity.h"

class Yoshi;
class Mario final : public Entity
{
public:
	explicit Mario(Yoshi* &plyrYoshi);
	~Mario() override;

	void Draw() const override;
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Reset() override;

private:
	Yoshi* m_Yoshi;
	float m_XTxtPos2;
	float m_YTxtPos2;
	float m_TxtWidth2;
	float m_TxtHeight2;
	float m_Time{0};

	void Animate(float elapsedSec) override;
};

