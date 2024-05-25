#include "pch.h"
#include "WingedClouds.h"

#include <iostream>

#include "Flowers.h"
#include "Texture.h"

WingedClouds::WingedClouds(Type typeOfCloud, const std::string& texturePath,Point2f position):Entity(texturePath,30,42,position),
                                                                                              m_TypeOfCloud(typeOfCloud)
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
			m_CloudFlower = new Flower(m_Position);
		}
	}
}

void WingedClouds::Animate(float elapsedSec)
{
	m_ScaleX = -1;

	m_FrameTime += elapsedSec;

	m_YTxtPos = 312;

	if (m_XTxtPos > m_TxtWidth * 3)
	{
		m_XTxtPos = 0;
	}

	if (m_FrameTime > 0.2)
	{
		m_XTxtPos += m_TxtWidth + 2;
		m_FrameTime = 0;
	}
}

void WingedClouds::SetIsHit()
{
	m_IsHit = true;
}

bool WingedClouds::GetIsHit() const
{
	return m_IsHit;
}


WingedClouds::Type WingedClouds::GetTypeOfCloud() const
{
	return m_TypeOfCloud;
}

Flower* WingedClouds::GetFlower() const
{
	if (m_TypeOfCloud == Type::FlowerCloud)
	{
		return m_CloudFlower;
	}

	throw std::invalid_argument("Cloud must be of Flower type");
	
}

