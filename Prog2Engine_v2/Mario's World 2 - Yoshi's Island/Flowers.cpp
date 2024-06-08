#include "pch.h"
#include "Flowers.h"

Flower::Flower(Point2f position):Entity("Flowers.png",32,32,position)
{
	m_XTxtPos = 1;
	m_YTxtPos = 100;

	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));
}

void Flower::Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	
}

