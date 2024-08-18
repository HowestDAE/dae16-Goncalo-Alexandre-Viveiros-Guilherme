#pragma once
#include "Enemy.h"


class SoundManager;

class PiranhaPlant final :public Enemy
{
public:
	PiranhaPlant(Point2f position,bool isFlipped);
	~PiranhaPlant() override = default;

	void Draw()const override;
	void Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec) override;
	void CalculateAngle(Point2f yoshiPos);
	void Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Sound(SoundManager* soundManager);
	void Animate(float elapsedSec) override;
	void Reset() override;
private:
	bool m_IsFlipped;
	bool m_IsSFXReady {false};
	float m_SFXTimer {0};
	float m_XTxtPos2{ 0 };
	float m_YTxtPos2{ 0 };
	float m_TxtHeight2{ 12 };
	float m_TxtWidth2{ 16 };
};

