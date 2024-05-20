#pragma once
#include "Entity.h"

class Flower;
class WingedClouds:public Entity
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
	~WingedClouds();
	void Update();
	void Animate(float elapsedSec);
	void SetIsHit();
	bool GetIsHit();
	Type GetTypeOfCloud() const;
	Flower* GetFlower() const;
	
	
private:
	Type m_TypeOfCloud;
	bool m_IsHit;
	Flower* CloudFlower;
};

