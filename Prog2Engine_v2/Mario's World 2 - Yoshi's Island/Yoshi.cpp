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

void Yoshi::Draw() const
{
	
	m_YoshiTxt->Draw(Rectf(m_Position.x, m_Position.y, float(m_StdTxtWidth * 2), float(m_StdTxtHeight * 2)),
		Rectf(xTxtPos, yTxtPos, m_StdTxtWidth, m_StdTxtHeight));
	
	utils::SetColor(Color4f{ 1,0,0,1 });
	utils::DrawLine(Point2f{ m_Position.x,m_Position.y + m_StdTxtHeight }, Point2f{ m_Position.x, m_Position.y - 3 });


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

	//Animation for Walking state
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
	
	//Collisions
	for (int idx{0}; idx < platforms.size(); idx++)
	{
		//floor collision
		if (utils::Raycast(platforms[idx], Point2f{m_Position.x,m_Position.y + m_StdTxtHeight * 2}, 
			Point2f{m_Position.x, m_Position.y - 3}, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
		}

		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_StdTxtWidth * 2,m_Position.y + m_StdTxtHeight * 2 },
			Point2f{ m_Position.x + m_StdTxtWidth * 2, m_Position.y - 3 }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
		}
		else
		{
			m_VelocityY = -9.8f;
		}

		//Wall Collision

		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x,m_Position.y + m_StdTxtHeight},
			Point2f{ m_Position.x + m_StdTxtWidth * 2,m_Position.y + m_StdTxtHeight }, hit_info))
		{
			m_VelocityX = 0;
			m_Position.x = hit_info.intersectPoint.x;
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

void Yoshi::Controls(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		m_VelocityX = -5;
		break;
	case SDLK_RIGHT:
		m_VelocityX = 5;
		break;
	case SDLK_UP:
		m_VelocityY = 11;
		break;
	case SDLK_DOWN:

		break;
	case SDLK_1:
		m_Position.y = 200;
		break;
	}
}

Point2f Yoshi::GetYoshiPos() const
{
	return m_Position;
}
