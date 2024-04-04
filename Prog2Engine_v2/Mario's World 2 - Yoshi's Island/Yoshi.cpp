#include "pch.h"
#include "Yoshi.h"

#include <iostream>

#include "Texture.h"
#include "utils.h"

Yoshi::Yoshi(Point2f startPos):
Entity("Yoshi_SpriteSheet.png",32,36,startPos),
	m_IsMarioOn{ true },
	m_MarioTimer{ 10 },
	lastYPos{ m_Position.y },
	lastXPos{ m_Position.x }
{
	
}

Yoshi::~Yoshi()
{

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
		//m_CurrentTxtWidth = m_StdTxtWidth;
		yTxtPos = m_TxtHeight * 2;

		float m_IdleSpriteChange{ 0 };

		m_IdleSpriteChange += elapsedSec;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.13)
		{
			xTxtPos += m_TxtWidth;
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
		//m_CurrentTxtWidth = m_StdTxtWidth;
		yTxtPos = m_TxtHeight;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.02)
		{
			xTxtPos += m_TxtWidth;
			m_FrameTime = 0;
		}

	}

	//Animation for Sprinting State
	if (currentState == AnimState::Sprinting)
	{
		//m_CurrentTxtWidth = m_StdTxtWidth + 6;
		yTxtPos = 0;
		m_FrameTime += elapsedSec;

		if (m_FrameTime >= 0.01)
		{
			xTxtPos += m_TxtWidth;
			m_FrameTime = 0;
		}

		if (xTxtPos > 36)
		{
			xTxtPos = 0;
		}
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

		m_VelocityY = 700;

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

void Yoshi::Debug()
{

	if (lastXPos != m_Position.x)
	{
		std::cout << "Yoshi's X position: " << m_Position.x << std::endl;
	}

	if (lastYPos != m_Position.y)
	{
		std::cout << "Yoshi's Y position: " << m_Position.y << std::endl;
	}
	
}


bool Yoshi::GetIsGrounded() const
{
	return m_IsGrounded;
}

bool Yoshi::GetIsFacingRight() const
{
	return m_IsFacingRight;
}
