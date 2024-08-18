#pragma once
#include "Entity.h"

class SoundManager;
class Yoshi;
class Mario final : public Entity
{
public:
	explicit Mario(Yoshi* plyrYoshi);
	~Mario() override = default;

	void Draw() const override;
	void Update(const std::vector< std::vector<Point2f>>& platforms, SoundManager* soundManager, float elapsedSec);
	void Reset() override;

private:
	Yoshi* m_Yoshi;
	float m_XTxtPos2;
	float m_YTxtPos2;
	float m_TxtWidth2;
	float m_TxtHeight2;
	float m_Time{0};
	float m_CryTimer{ 0 };
	bool m_IsMarioOnYoshi{ true };

	void Animate(float elapsedSec) override;
};

