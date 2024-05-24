#pragma once
#include "Entity.h"

class Egg final : public Entity
{
public:
	Egg(Point2f Pos);
	~Egg() override;

	void Draw() const;
	void Update(Point2f yoshiPos, bool yoshiDirection, int currentEgg, const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	void Animate(float elapsedSec);
	bool HoldEgg(Rectf yoshiHitBox, bool yoshiDirection, bool isCalculatingAngle,float elapsedSec);
	void ThrowEgg();
	bool GetIsThrown();
	Rectf GetHitbox();

private:
	Texture* m_PointerTxt;
	Rectf m_PointerRect{0, 0, 16, 16 };
	float m_Timer{ 0 };
	float m_EggTime{ 0 };
	bool m_IsPointerGoingUp {true};
	float m_LastYoshiPosX{ 0 };
	float m_LastYoshiPosY{ 0 };
	bool m_IsThrown{ false };
	std::vector<Point2f> Points{1};
	float m_Angle = 0;
	bool m_IsBeingHeld{false};
};

