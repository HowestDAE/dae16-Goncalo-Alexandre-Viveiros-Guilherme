#include "pch.h"
#include "Mario.h"

#include "Yoshi.h"

Mario::Mario(Yoshi* PlyrYoshi):Entity("Mario_SpriteSheet.png",23,16,PlyrYoshi->GetPosition()),m_Yoshi(PlyrYoshi)
{
}

Mario::~Mario()
{
}

void Mario::Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec)
{
	Entity::Update(platforms, elapsedSec);

	if (m_Yoshi->GetIsMarioOn() == true)
	{
		m_IsFacingRight = m_Yoshi->GetIsFacingRight();
		m_Position = m_Yoshi->GetPosition();

		if (m_IsFacingRight == true)
		{
			m_Position.x += 10;
		}

		else
		{
			m_Position.x += 30;
		}

		m_Position.y += 15;
	}

	else
	{
		m_Position.x = 100;
	}
}

void Mario::Animate(float elapsedSec)
{
	m_YTxtPos = 135;
	m_XTxtPos = 0;
}


