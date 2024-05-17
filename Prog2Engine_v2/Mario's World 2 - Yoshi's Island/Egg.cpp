#include "pch.h"
#include "Egg.h"
#include "Texture.h"

Egg::Egg(const Point2f Pos):Entity("Eggs.png",16,14,Pos)
{
	m_PointerTxt = new Texture{ "Pointer for eggs.png" };
}

Egg::~Egg()
{
	delete m_PointerTxt;
}

void Egg::Draw() const
{
	Entity::Draw();

	if (m_IsBeingHeld == true)
	{
		m_PointerTxt->Draw(Rectf(Points[0].x, Points[0].y, 16*2, 16*2),m_PointerRect);
	}
}

void Egg::Update(const Point2f yoshiPos, const bool yoshiDirection, const int currentEgg, const std::vector< std::vector<Point2f>>& platforms, const float elapsedSec)
{
	if (m_IsThrown == false)
	{
		m_IsBeingHeld = false;

		m_Timer += elapsedSec;

		if (m_Timer > 0.3)
		{
			m_LastYoshiPosX = yoshiPos.x;
			m_LastYoshiPosY = yoshiPos.y;

			m_Timer = 0.26;
		}
		if (yoshiDirection == true)
		{
			m_Position.x = (m_LastYoshiPosX - m_TxtWidth * 2) - (m_TxtWidth * 2.5) * currentEgg;
			m_Position.y = m_LastYoshiPosY;
		}
		else
		{
			m_Position.x = (m_LastYoshiPosX + m_TxtWidth * 5) + (m_TxtWidth * 2.5) * currentEgg;
			m_Position.y = m_LastYoshiPosY;
		}
	}

	if (m_IsThrown == true)
	{

		Entity::Update(platforms, elapsedSec);
	}
	
	
	
}

void Egg::Animate(const float elapsedSec)
{
	m_YTxtPos = 32;
	m_FrameTime += elapsedSec;

	if (m_FrameTime >= 0.4)
	{
		m_XTxtPos += m_TxtWidth + 1;
		m_FrameTime = 0;

		m_PointerRect.left += 16 + 5;
	}

	if (m_PointerRect.left > 16 + 5)
	{
		m_PointerRect.left = 0;
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

bool Egg::HoldEgg(const Rectf yoshiHitBox, const bool yoshiDirection,bool isCalculatingAngle,float elapsedSec)
{
	
	m_IsBeingHeld = true;
	if (isCalculatingAngle == true)
	{
		if (m_IsPointerGoingUp == true)
		{
			m_EggTime += elapsedSec;

			if (m_EggTime >= 1)
			{
				m_IsPointerGoingUp = false;
			}
		}
		else
		{
			m_EggTime -= elapsedSec;

			if (m_EggTime <= 0)
			{
				m_IsPointerGoingUp = true;
			}
		}
	}
	

	

	if (yoshiDirection == true)
	{
		m_Angle = utils::lerp(-1, 1.4, m_EggTime);
		m_Position.x = yoshiHitBox.left + m_TxtWidth * 3;
		m_Position.y = yoshiHitBox.bottom + m_TxtHeight * 2;
		Points[0] =  Point2f(yoshiHitBox.left + yoshiHitBox.width/2,yoshiHitBox.bottom + yoshiHitBox.height/2) + Vector2f(cos(m_Angle), sin(m_Angle)) * 90;
	}
	else
	{
		m_Angle = utils::lerp(4, 1.8, m_EggTime);
		m_Position.x = yoshiHitBox.left;
		m_Position.y = yoshiHitBox.bottom + m_TxtHeight * 2;
		Points[0] = Point2f(yoshiHitBox.left + yoshiHitBox.width / 2, yoshiHitBox.bottom + yoshiHitBox.height / 2) + Vector2f(cos(m_Angle), sin(m_Angle)) * 110;
	}

	return true;
	

}

void Egg::ThrowEgg()
{
	m_IsThrown = true;
	m_VelocityX = cos(m_Angle) * 2000;
	m_VelocityY = sin(m_Angle) * 2000;

}

bool Egg::GetIsThrown()
{
	return m_IsThrown;
}
