#include "pch.h"
#include "Egg.h"

Egg::Egg(Point2f Pos):Entity("Eggs.png",16,14,Pos)
{
}

Egg::~Egg()
{
}

void Egg::Update(Point2f YoshiPos,int NumOfEggs, const std::vector< std::vector<Point2f>>& platforms, float elapsedSec)
{
	
	if (NumOfEggs < 2)
	{

		if (m_Position.x > YoshiPos.x + m_TxtWidth * 6)
		{
			m_VelocityX -= 1 * (m_Position.x - (YoshiPos.x +m_TxtWidth * 6));
		}

		if (m_Position.x < YoshiPos.x - m_TxtWidth * 3)
		{
			m_VelocityX += 1 *( YoshiPos.x - (m_Position.x - m_TxtWidth * 3));
		}
		

		if (m_Position.y != YoshiPos.y)
		{
			if (m_Position.y > YoshiPos.y)
			{
				m_VelocityY -= 1 * (m_Position.y - YoshiPos.y);
			}

			if (m_Position.y < YoshiPos.y - 64)
			{
				m_VelocityY += 200;
			}
		}
		
	}

	Entity::Update(platforms, elapsedSec);

}

void Egg::Animate(float elapsedSec)
{
	m_YTxtPos = 32;
	m_FrameTime += elapsedSec;

	if (m_FrameTime >= 0.4)
	{
		m_XTxtPos += m_TxtWidth + 1;
		m_FrameTime = 0;
	}

	if (m_XTxtPos < 17)
	{
		m_XTxtPos = 17;
	}


	if (m_XTxtPos > 17 + m_TxtWidth*2 + 1)
	{
		m_XTxtPos = 17;
	}
}
