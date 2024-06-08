#include "pch.h"
#include "WalkingTulip.h"

WalkingTulip::WalkingTulip(Point2f position):Enemy(true,true,"EnemiesVaried.png",29,20,position)
{
}

void WalkingTulip::Animate(float elapsedSec)
{
	m_FrameTime += elapsedSec;

	m_YTxtPos = 34;

	if (m_XTxtPos < 334 || m_XTxtPos > 474)
	{
		m_XTxtPos = 334;
	}

	if (m_FrameTime > 0.1)
	{
		m_XTxtPos += m_TxtWidth + 10;

		m_FrameTime = 0;
	}
}

void WalkingTulip::Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	Enemy::Update(platforms, elapsedSec);

	m_VelocityX = -30;
	m_VelocityY = 30;
}
