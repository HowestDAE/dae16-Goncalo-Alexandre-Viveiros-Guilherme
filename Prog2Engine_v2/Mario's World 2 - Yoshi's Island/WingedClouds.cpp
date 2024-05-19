#include "pch.h"
#include "WingedClouds.h"

WingedClouds::WingedClouds(bool isLevelCloud, bool isStarCloud, bool isFlowerCloud, const std::string& texturePath,Point2f position):Entity(texturePath,30,42,position),
m_IsLevelCloud(isLevelCloud),
m_IsStarCloud(isStarCloud),
m_IsFlowerCloud(isFlowerCloud)
{
}

WingedClouds::~WingedClouds()
{

}

void WingedClouds::Update() const
{
	if (m_IsHit == true)
	{
		if (m_IsLevelCloud == true)
		{

			if (m_AreStructureSpawned == true)
			{
				delete this;
			}
		}

		else if (m_IsStarCloud == true)
		{
			//TODO make it spawn those stupid stars

			delete this;
		}

		else if (m_IsFlowerCloud == true)
		{
			//TODO make it spawn a flower

			delete this;
		}
	}
}

void WingedClouds::Animate(float elapsedSec)
{
	m_FrameTime += elapsedSec;

	m_YTxtPos = 312;

	if (m_XTxtPos > m_TxtWidth * 3)
	{
		m_XTxtPos = 0;
	}

	if (m_FrameTime > 0.2)
	{
		m_XTxtPos += m_TxtWidth;
		m_FrameTime = 0;
	}
}

void WingedClouds::SetIsHit()
{
	m_IsHit = true;
}
