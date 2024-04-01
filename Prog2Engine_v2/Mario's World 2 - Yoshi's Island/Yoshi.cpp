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
	m_VelocityX{ 0 },
	m_CurrentTxtWidth{m_StdTxtWidth}
{
	
}

Yoshi::~Yoshi()
{
	delete m_YoshiTxt;
}

void Yoshi::Draw() const
{
	if (m_IsFacingRight == false)
	{
		m_YoshiTxt->Draw(Rectf(m_Position.x, m_Position.y, float(m_CurrentTxtWidth * 2), float(m_StdTxtHeight * 2)),
			Rectf(xTxtPos, yTxtPos, m_CurrentTxtWidth, m_StdTxtHeight));
	}

	if (m_IsFacingRight == true)
	{
		glPushMatrix();
		{
			glScalef(-1, 1, 1);
			glTranslatef(-m_StdTxtWidth * 3 + 9, 0, 0);
			m_YoshiTxt->Draw(Rectf(-m_Position.x, m_Position.y, float(m_CurrentTxtWidth * 2), float(m_StdTxtHeight * 2)),
				Rectf(xTxtPos, yTxtPos, m_CurrentTxtWidth, m_StdTxtHeight));
		}
		glPopMatrix();


	}

	/*
	//debugs floor collision
	utils::SetColor(Color4f{ 1,0,0,1 });
	utils::DrawLine(Point2f{ m_Position.x + m_StdTxtWidth - 3,m_Position.y + m_StdTxtHeight * 2 },
		Point2f{ m_Position.x + m_StdTxtWidth - 3, m_Position.y - 3 });

	utils::DrawLine(Point2f{ m_Position.x + m_StdTxtWidth * 2 - 3,m_Position.y + m_StdTxtHeight * 2 },
		Point2f{ m_Position.x + m_StdTxtWidth * 2 - 3, m_Position.y - 3 });

	//debugs wall code
	utils::SetColor(Color4f{ 0,1,0,1 });

	//utils::DrawLine(Point2f{ m_Position.x + m_StdTxtWidth + 20,m_Position.y + m_StdTxtHeight },
		//Point2f{m_Position.x + m_StdTxtWidth - 5, m_Position.y + m_StdTxtHeight});

	utils::DrawLine(Point2f{ m_Position.x + m_StdTxtWidth + 10,m_Position.y + m_StdTxtHeight },
		Point2f{ m_Position.x + m_StdTxtWidth + 30,m_Position.y + m_StdTxtHeight });
*/


}

void Yoshi::Animation(float elapsedSec)
{

	////////////////////////////////////
	// CHECK CURRENT ANIMATION STATE //
	//////////////////////////////////

	if (m_VelocityX == 0)
	{
		 currentState = AnimState::Idle;

	}

	if (m_VelocityX > 0 && m_VelocityX < 260 || m_VelocityX < 0 && m_VelocityX > -260)
	{
		 currentState = AnimState::Walking;
	}

	if (m_VelocityX > 260 || m_VelocityX < -260)
	{
		currentState = AnimState::Sprinting;
	}

	////////////////////////////////////
	// ANIMATIONS FOR CURRENT STATE  //
	//////////////////////////////////


	//Animations for Idle State
	if (currentState == AnimState::Idle)
	{
		m_CurrentTxtWidth = m_StdTxtWidth;
		yTxtPos = m_StdTxtHeight * 2;

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
		m_CurrentTxtWidth = m_StdTxtWidth;
		yTxtPos = m_StdTxtHeight;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.02)
		{
			xTxtPos += m_StdTxtWidth;
			m_FrameTime = 0;
		}

	}

	//Animation for Sprinting State
	if (currentState == AnimState::Sprinting)
	{
		m_CurrentTxtWidth = m_StdTxtWidth + 6;
		yTxtPos = 0;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.01)
		{
			xTxtPos += m_StdTxtWidth * 2;
			m_FrameTime = 0;
		}

		if (xTxtPos > 64)
		{
			xTxtPos = 0;
		}
	}
}

void Yoshi::Update(const std::vector< std::vector<Point2f>> &platforms, float elapsedSec)
{
	//collision and gravity
	m_Position.y += m_VelocityY * elapsedSec;

	utils::HitInfo hit_info;
	
	//Collisions
	for (int idx{0}; idx < platforms.size(); idx++)
	{
		//floor collision

		//checks collision from the left side of yoshis feet
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_StdTxtWidth - 3,m_Position.y + m_StdTxtHeight * 2 },
			Point2f{ m_Position.x + m_StdTxtWidth - 3, m_Position.y - 3 }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsYoshiGrounded = true;
		}

		//checks collision from the right side of yoshis feet
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_StdTxtWidth * 2 - 3,m_Position.y + m_StdTxtHeight * 2 },
			Point2f{ m_Position.x + m_StdTxtWidth * 2 - 3, m_Position.y - 3 }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsYoshiGrounded = true;
		}
		else
		{
			
				m_VelocityY = -380;
			
			
		}

		//Wall Collision

		//left side collision
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_StdTxtWidth + 20,m_Position.y + m_StdTxtHeight },
			Point2f{ m_Position.x + m_StdTxtWidth - 5, m_Position.y + m_StdTxtHeight }, hit_info))
		{
			m_VelocityX = -0.3;
			m_Position.x = hit_info.intersectPoint.x - m_StdTxtWidth + 7; //Teleports yoshi to the point of intersection with a small offset
			currentState = AnimState::Pushing;
		}

		//right side collision
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_StdTxtWidth + 10,m_Position.y + m_StdTxtHeight },
			Point2f{ m_Position.x + m_StdTxtWidth + 30,m_Position.y + m_StdTxtHeight }, hit_info))
		{
			m_VelocityX = 0.3;
			m_Position.x = hit_info.intersectPoint.x - m_StdTxtWidth * 2 - 3;
			currentState = AnimState::Pushing;
		}

	}

	//Adds Yoshi's horizontal speed to his position
	m_Position.x += m_VelocityX * elapsedSec ;

	//simulates friction whilst yoshi is grounded
	if (m_IsYoshiGrounded == true)
	{
		m_VelocityX -= (m_VelocityX * 3.3) * elapsedSec;
	}
	


	//Stops movement once it falls below a certain range
	if (m_VelocityX < 20 && m_VelocityX > 0 || m_VelocityX > -20 && m_VelocityX < 0)
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
		if (m_VelocityX != -330)
		{
			m_VelocityX -= 33;
		}
		
		break;
	case SDLK_RIGHT:
		if(m_VelocityX != 330)
		{
			m_VelocityX += 33;
		}
		break;
	case SDLK_UP:

		m_IsYoshiGrounded = false;
		m_VelocityY = 300;

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
