#include "pch.h"
#include "WingedClouds.h"

#include <iostream>

#include "Flowers.h"
#include "Texture.h"

WingedClouds::WingedClouds(Type typeOfCloud, const std::string& texturePath,Point2f position):Entity(texturePath,30,42,position),
                                                                                              m_TypeOfCloud(typeOfCloud)
{

}

WingedClouds::~WingedClouds()
{

}

void WingedClouds::Update()
{
	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));

	if (m_IsHit == true)
	{

		if (m_TypeOfCloud == Type::StarCloud)
		{
			//TODO make it spawn those stupid stars

		}

		else if (m_TypeOfCloud == Type::FlowerCloud)
		{
			CloudFlower = new Flower(m_Position);
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

bool WingedClouds::GetIsHit()
{
	return m_IsHit;
}


WingedClouds::Type WingedClouds::GetTypeOfCloud() const
{
	return m_TypeOfCloud;
}

Flower* WingedClouds::GetFlower() const
{
	return CloudFlower;
}

