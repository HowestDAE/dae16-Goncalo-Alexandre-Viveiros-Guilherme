#include "pch.h"
#include "Yoshi.h"
#include "Texture.h"
#include "utils.h"

Yoshi::Yoshi(Point2f startpos) :
	m_IsMarioOn{ true },
	m_MarioTimer{ 10 },
	m_YoshiTxt{ new Texture {"Yoshi_SpriteSheet.png"} },
	m_Position{ startpos },
	m_VelocityY{ -0.0 },
	m_VelocityX{ 0 }
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
		//if (m_IsFacingRight == false)
		//{
			m_YoshiTxt->Draw(Rectf(m_Position.x, m_Position.y, float(m_StdTxtWidth * 2), float(m_StdTxtHeight * 2)),
				Rectf(xTxtPos, yTxtPos, m_StdTxtWidth, m_StdTxtHeight));
		//}

		//else
		//{
		//	glTranslatef(xTxtPos, 0, 0);
		//	glRotatef(-180, 0, 1, 0);
		//	glTranslatef(-xTxtPos, 0, 0);
		//	m_YoshiTxt->Draw(Rectf(m_Position.x, m_Position.y, float(m_StdTxtWidth * 2), float(m_StdTxtHeight * 2)),
		//		Rectf(xTxtPos, yTxtPos, m_StdTxtWidth, m_StdTxtHeight));
		//}
			utils::SetColor(Color4f{ 1,0,0,1 });
			utils::DrawLine(Point2f{ m_Position.x,m_Position.y + m_StdTxtHeight }, Point2f{ m_Position.x, m_Position.y - 3 });
		
	}
	glPopMatrix();

}

void Yoshi::Animation(float elapsedSec)
{	

	//Checks to see current Animation State
	if (m_VelocityX == 0)
	{
		 currentState = AnimState::Idle;

	}

	if (m_VelocityX > 0 || m_VelocityX < 0)
	{
		 currentState = AnimState::Walking;
	}


	//Animations for Idle State
	if (currentState == AnimState::Idle)
	{

		yTxtPos = 0;

		float m_IdleSpriteChange{ 0 };

		m_IdleSpriteChange += elapsedSec;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.13)
		{
			xTxtPos += m_StdTxtWidth;
			m_FrameTime = 0;

			if (xTxtPos >= 210)
			{
				xTxtPos = 0;
			}
		}

		if(m_IdleSpriteChange == 6)
		{

			m_IdleSpriteChange = 0;
		}

	}

	if (currentState == AnimState::Walking)
	{
		yTxtPos = 32;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.02)
		{
			xTxtPos += m_StdTxtWidth;
			m_FrameTime = 0;
		}

	}
	
	
}

void Yoshi::Update(const std::vector< std::vector<Point2f>> &platforms)
{
	//collision and gravity
	m_Position.y += m_VelocityY;

	utils::HitInfo hit_info;
	

	for (int idx{0}; idx < platforms.size(); idx++)
	{
		if (utils::Raycast(platforms[idx], Point2f{m_Position.x,m_Position.y + m_StdTxtHeight}, Point2f{m_Position.x, m_Position.y - 3}, hit_info))
		{
			m_VelocityY = 0;
		}
		else
		{
			//m_VelocityY = -0.8f;
		}
	}


	//Adds Yoshi's speed to his position and simulates friction
	m_Position.x += m_VelocityX;
	m_VelocityX *= 0.94f;


	//Stops movement once it falls below a certain range
	if (m_VelocityX < 0.2 && m_VelocityX > 0 || m_VelocityX > -0.2 && m_VelocityX < 0)
	{
		m_VelocityX = 0;
	}


	//Check if Yoshi is facing right
	if (m_VelocityX < 0)
	{
		m_IsFacingRight = false;
	}

	else if (m_VelocityX > 0)
	{
		m_IsFacingRight = true;
	}

}
