#include "pch.h"
#include "Yoshi.h"
#include "Texture.h"

Yoshi::Yoshi(Point2f startpos):
	m_YoshiTxt{new Texture {"YoshiIdleSprites.png"}},
	m_Position{startpos},
	m_IsMarioOn{true},
	m_MarioTimer{10},
	xTxtPos{ 0 },
	yTxtPos{ 0 }
{

}

Yoshi::~Yoshi()
{
	delete m_YoshiTxt;
}

void Yoshi::Draw() 
{
	
	glPushMatrix();
	{
		m_YoshiTxt->Draw(Rectf(m_Position.x, m_Position.y, float(m_StdTxtWidth * 3), float(m_StdTxtHeight * 3)),
			Rectf(xTxtPos, yTxtPos, m_StdTxtWidth, m_StdTxtHeight));
	}
	glPopMatrix();

}

void Yoshi::Animation(float elapsedSec)
{	
	xTxtPos += 30;
	/*
	AnimState currentState = AnimState::Idle;

	while (currentState == AnimState::Idle)
	{
		xTxtPos += m_StdTxtWidth;
	}
	*/
}

void Yoshi::Update()
{
	//m_Position.y -= 3.8;
}
