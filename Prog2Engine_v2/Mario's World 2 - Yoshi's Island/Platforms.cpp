#include "pch.h"
#include "Platforms.h"

#include <iostream>

#include "Texture.h"
#include "utils.h"
#include "Vector2f.h"

Platforms::Platforms(Point2f position, float txtWidth, float txtHeight, float platformWidth, float platformHeight, const std::string& texturePath, float radius) :
	m_Position{ position },
	m_TxtWidth{ txtWidth },
	m_TxtHeight{ txtHeight },
	m_PlatformWidth(platformWidth),
	m_PlatformHeight(platformHeight),
	m_PlatformTxt{ new Texture{ texturePath } },
	m_Radius{ radius }
{

	for (int idx = 0; idx < m_PlatformVertices.size(); idx++)
	{
		m_PlatformVertices[idx].push_back(m_Position);
		m_PlatformVertices[idx].push_back(m_Position);
	}

}

Platforms::~Platforms()
{
	delete m_PlatformTxt;
}

void Platforms::Draw() const
{
	for (int idx = 0; idx < m_PlatformPos.size(); idx++)
	{
		m_PlatformTxt->Draw(Rectf(m_PlatformPos[idx].x - m_PlatformWidth / 2, m_PlatformPos[idx].y, m_PlatformWidth, m_PlatformHeight),
			Rectf(0, 0, m_TxtWidth, m_TxtHeight));
	}

	for (int idx = 0; idx < m_PlatformPos.size(); idx++)
	{
		utils::DrawEllipse(m_PlatformPos[idx], 1, 1, 1);
	}

	
}

void Platforms::Update(float elapsedSec,Point2f yoshiPos,Point2f yoshiVelocity)
{

	m_Angle += 1 * elapsedSec;
	for (int idx = 0; idx < m_PlatformPos.size(); idx++)
	{
		m_PlatformPos[idx] = m_Position + Vector2f(cos(m_Angle + ((M_PI/2) *idx)), sin(m_Angle + ((M_PI / 2) * idx))) * m_Radius;
	}


	for (int idx = 0; idx < m_PlatformVertices.size(); idx++)
	{
		m_PlatformVertices[idx][0] = Point2f(m_PlatformPos[idx].x - (m_PlatformWidth / 2), (m_PlatformPos[idx].y + m_PlatformHeight));
	
		m_PlatformVertices[idx][1] = Point2f(m_PlatformPos[idx].x + (m_PlatformWidth / 2), (m_PlatformPos[idx].y + m_PlatformHeight));

	}
	for (int idx = 0; idx < m_PlatformPos.size(); idx++)
	{
		if (yoshiPos.x > m_PlatformPos[idx].x - (m_PlatformWidth / 2) - 54 //distance to yoshis right most edge
			&& yoshiPos.x < m_PlatformPos[idx].x + (m_PlatformWidth / 2))
		{

			if (yoshiPos.y < m_PlatformPos[idx].y + m_PlatformHeight + 1 && yoshiPos.y > m_PlatformPos[idx].y)
			{
				if (yoshiVelocity.x >= 0.1 || yoshiVelocity.x <= -0.1)
				{
					m_HasYoshiMovedRecently = true;
				}

				if (m_HasYoshiMovedRecently == true)
				{
					if (yoshiVelocity.x <= 0.1f || yoshiVelocity.x <= -0.1)
					{
						m_CalculateNewYoshiPos = true;
						m_HasYoshiMovedRecently = false;
						
					}
				}
				
				m_WhichPlatformIsYoshiOn = idx;
				if (m_CalculateNewYoshiPos == true)
				{
					m_YoshiXPosDifference = yoshiPos.x - m_PlatformPos[idx].x;
					m_CalculateNewYoshiPos = false;
				}

				break;
			}

		}


	}


}

std::vector<std::vector<Point2f>> Platforms::GetPlatformVertices()
{
	return m_PlatformVertices;
}

float Platforms::GetAngle() const
{
	return m_Angle;
}

Point2f Platforms::GetPlatformPosition() const
{
	return m_PlatformPos[m_WhichPlatformIsYoshiOn];
}

Point2f Platforms::GetCenterPosition() const
{
	return m_Position;
}

int Platforms::GetWhichPlatformIsYoshiOn() const
{
	return m_WhichPlatformIsYoshiOn;
}

float Platforms::GetPlatformHeight() const
{
	return m_PlatformHeight;
}

float Platforms::GetPlatformWidth() const
{
	return m_PlatformWidth;
}

float Platforms::GetRadius() const
{
	return m_Radius;
}

float Platforms::GetYoshiXPosDifference() const
{
	return m_YoshiXPosDifference;
}
