#include "pch.h"
#include "Egg.h"
#include "Texture.h"

Egg::Egg(Point2f Pos):Entity("Eggs.png",16,14,Pos)
{
	m_PointerTxt = new Texture{ "Pointer for eggs.png" };
}

Egg::~Egg()
{
}

void Egg::Draw() const
{
	Entity::Draw();

	if (m_IsBeingHeld == true)
	{
		m_PointerTxt->Draw(Rectf(Points[0].x, Points[0].y, 16*2, 16*2),Rectf(0, 0, 16, 16));
	}
}

void Egg::Update(Point2f YoshiPos,bool YoshiDirection,int currentEgg, const std::vector< std::vector<Point2f>>& platforms, float elapsedSec)
{
	m_IsBeingHeld = false;

	m_FrameTime += elapsedSec;
	
	if (m_FrameTime > 0.3)
	{
		m_LastYoshiPosX = YoshiPos.x;
		m_LastYoshiPosY = YoshiPos.y;
	
		m_FrameTime = 0.26;
	}
	if (YoshiDirection == true)
	{
		m_Position.x = (m_LastYoshiPosX - m_TxtWidth * 2) - (m_TxtWidth * 2.5) * currentEgg ;
		m_Position.y = m_LastYoshiPosY;
	}
	else
	{
		m_Position.x = (m_LastYoshiPosX + m_TxtWidth * 5) + (m_TxtWidth * 2.5) * currentEgg;
		m_Position.y = m_LastYoshiPosY;
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

bool Egg::HoldEgg(Point2f yoshiPos, bool yoshiDirection,bool isCalculatingAngle,bool isThrown)
{

	m_IsBeingHeld = true;

	if (m_Angle < 180)
	{
		m_Angle += 0.1;
	}

	if (yoshiDirection == true)
	{
		m_Position.x = yoshiPos.x + m_TxtWidth * 3;
		m_Position.y = yoshiPos.y + m_TxtHeight * 2;
		Points[0] = m_Position + Vector2f(cos(m_Angle), sin(m_Angle)) * 60;
	}
	else
	{
		m_Position.x = yoshiPos.x;
		m_Position.y = yoshiPos.y + m_TxtHeight * 2;
	}

	return true;
	

}

void Egg::ThrowEgg(bool isHoldingEgg)
{

}
