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

	void Update();
	void Animate(float elapsedSec) override;
	void SetIsHit();
	bool GetIsHit() const;
	Type GetTypeOfCloud() const;
	Flower* GetFlower() const;
	
	
private:
	Type m_TypeOfCloud;
	bool m_IsHit;
	Flower* m_CloudFlower;
};

