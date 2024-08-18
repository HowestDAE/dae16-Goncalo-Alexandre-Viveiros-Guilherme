#include "pch.h"
#include "Snatchers.h"

#include "Mario.h"

Snatchers::Snatchers(Point2f position): Enemy(false,false,"EnemiesVaried2.png",24,16,position)
{
}

void Snatchers::Snatch(Mario* babyMarioPointer)
{
	float distancex = m_Position.x - babyMarioPointer->GetPosition().x;
	float distancey = m_Position.y - babyMarioPointer->GetPosition().y;

	if (m_GrabbedMario == false)
	{
		if (m_Position.x < babyMarioPointer->GetPosition().x)
		{
			m_VelocityX = 280;
		}

		if (m_Position.x > babyMarioPointer->GetPosition().x)
		{
			m_VelocityX = -280;
		}

		if (m_Position.y < babyMarioPointer->GetPosition().y)
		{
			m_VelocityY = 280;
		}

		if (m_Position.y > babyMarioPointer->GetPosition().y)
		{
			m_VelocityY = -280;
		}
	}

	else
	{
		m_VelocityY = 130;
		m_VelocityX = 90;
	}

	if (distancex < 10)
	{
		if (distancey < 10)
		{
			m_GrabbedMario = true;
			babyMarioPointer->SetPosition(m_Position);
		}

		else
		{
			m_GrabbedMario = false;
		}

	}

	else
	{
		m_GrabbedMario = false;
	}

}


void Snatchers::Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	
}

void Snatchers::Animate(float elapsedSec)
{
	m_YTxtPos = 71;
	m_XTxtPos = 369;
}

bool Snatchers::GetGrabbedMario()
{
	return m_GrabbedMario;
}

void Snatchers::Reset()
{
	Enemy::Reset();

	m_GrabbedMario = false;
}
