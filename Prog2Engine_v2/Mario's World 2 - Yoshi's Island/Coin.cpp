#include "pch.h"
#include "Coin.h"

Coin::Coin(bool isRedCoin, Point2f position):Entity("GeneralSprites.png",16,12,position),
m_IsRedCoin(isRedCoin)
{
}

Coin::~Coin()
= default;

void Coin::Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	
}

void Coin::Animate(float elapsedSec)
{
	m_FrameTime += elapsedSec;

	if (m_IsRedCoin == false)
	{
		m_YTxtPos = 307;
	}

	else
	{
		m_YTxtPos = 307 + 4 + m_TxtHeight;
	}


	if (m_XTxtPos < 307)
	{
		m_XTxtPos = 307;
	}
	else if (m_XTxtPos > 307 + m_TxtWidth * 3 + 10)
	{
		m_XTxtPos = 307;
	}

	if (m_FrameTime > 0.2)
	{
		m_XTxtPos += m_TxtWidth + 10;
		m_FrameTime = 0;
	}
}

bool Coin::GetIsRedCoin()
{
	return m_IsRedCoin;
}


