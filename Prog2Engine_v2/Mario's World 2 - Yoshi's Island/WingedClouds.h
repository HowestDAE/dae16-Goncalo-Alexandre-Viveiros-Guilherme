#pragma once
#include "Entity.h"

class WingedClouds:public Entity
{
public:
	WingedClouds(bool isLevelCloud,bool isStarCloud,bool isFlowerCloud, const std::string& texturePath,Point2f position);
	~WingedClouds();
	void Update() const;
	void Animate(float elapsedSec);
	void SetIsHit();
	
	
private:
	bool m_IsLevelCloud;
	bool m_IsStarCloud;
	bool m_IsFlowerCloud;
	bool m_IsHit;
	bool m_AreStructureSpawned;
};

