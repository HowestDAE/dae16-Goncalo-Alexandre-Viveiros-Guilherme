#pragma once
#include "Entity.h"

class Egg final : public Entity
{
public:
	explicit Egg(Point2f position);
	~Egg() override;

	void Draw() const override;
	void Update(Point2f yoshiPos, bool yoshiDirection, int currentEgg, const std::vector< std::vector<Point2f>>& platforms, float elapsedSec);
	void Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Animate(float elapsedSec) override;
	void PickUpEgg();
	void DropEgg();
	bool HoldEgg(Rectf yoshiHitBox, bool isYoshiFacingRight, bool isCalculatingAngle, float elapsedSec);
	void ThrowEgg();
	bool GetIsThrown();
	Rectf GetHitbox();
	bool GetIsFallen();


private:
	Texture* m_PointerTxt;
	Rectf m_PointerRect{0, 0, 16, 16 };
	bool m_IsFallen{ false };
	float m_EggTime{ 0 };
	int m_EggBounces{ 0 };
	bool m_IsPointerGoingUp {true};
	float m_LastYoshiPosX{ 0 };
	float m_LastYoshiPosY{ 0 };
	float m_DistanceX{ 0 };
	float m_DistanceY{ 0 };
	bool m_IsThrown{ false };
	std::vector<Point2f> Points{1};
	float m_Angle = 0;
	bool m_IsBeingHeld{false};
};

