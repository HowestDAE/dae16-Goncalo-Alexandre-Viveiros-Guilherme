#include "pch.h"
#include "FlyingShyGuy.h"

FlyingShyGuy::FlyingShyGuy(Point2f position, Point2f endPoint, bool isCyclic):
Enemy(true,true,"EnemiesVaried.png",27,16,position),
m_IsCyclic(isCyclic),
m_EndPoint(endPoint)
{
	m_StartPoint = m_Position;
}

FlyingShyGuy::~FlyingShyGuy()
{
}

void FlyingShyGuy::Update()
{
	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));

	if (m_IsCyclic == true)
	{
		if (m_Position.x < m_EndPoint.x)
		{
			m_VelocityX = 30;
		}
		else
		{
			m_VelocityX = -30;
		}

		if (m_Position.y < m_EndPoint.y)
		{
			m_VelocityY = 30;
		}
		else
		{
			m_VelocityY = -30;
		}

		if (m_Position.x - m_EndPoint.x < 10 || m_Position.x - m_EndPoint.x > -10)
		{
			m_Position.x = m_EndPoint.x;
		}

		if (m_Position.y - m_EndPoint.y < 10 || m_Position.y - m_EndPoint.y > -10)
		{
			m_Position.y = m_EndPoint.y;
		}

		if (m_Position.x == m_EndPoint.x && m_Position.y == m_EndPoint.y)
		{
			m_EndPoint = m_StartPoint;
		}
	}
}

void FlyingShyGuy::Animate(float elapsedSec)
{
	m_YTxtPos = 126;

	if (m_XTxtPos < 126 || m_XTxtPos > 202)
	{
		m_XTxtPos = 126;
	}

	if (m_FrameTime > 0.2)
	{
		m_XTxtPos += m_TxtWidth + 4;

		m_FrameTime = 0;
	}
}
