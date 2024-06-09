#pragma once
#include "Entity.h"

class Flower;
class WingedClouds final :public Entity
{
public:
	enum class Type
	{
		StairCloud,
		SunflowerCloud,
		StarCloud,
		FlowerCloud
	};
	WingedClouds(Type typeOfCloud, const std::string& texturePath,Point2f position);
	~WingedClouds() override = default;

	void Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec) override;
	void Animate(float elapsedSec) override;
	void SetIsHit();
	bool GetIsHit() const;
	Type GetTypeOfCloud() const;
	void Reset() override;
	
private:
	Type m_TypeOfCloud;
	bool m_IsHit;

};

