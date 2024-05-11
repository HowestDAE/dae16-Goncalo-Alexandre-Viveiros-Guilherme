#pragma once
#include "Entity.h"

class Egg: public Entity
{
public:
	Egg(Point2f Pos);
	~Egg();
	void Draw() const;
	void Update(Point2f YoshiPos, bool YoshiDirection, int currentEgg, const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	void Animate(float elapsedSec);
	bool HoldEgg(Point2f YoshiPos, bool YoshiDirection, bool isCalculatingAngle, bool isThrown);
	void ThrowEgg(bool isHoldingEgg);

private:
	Texture* m_PointerTxt;
	float m_FrameTime{ 0 };
	float m_LastYoshiPosX{ 0 };
	float m_LastYoshiPosY{ 0 };
	std::vector<Point2f> Points{1};
	float m_Angle = 0;
	bool m_IsBeingHeld{false};
};

