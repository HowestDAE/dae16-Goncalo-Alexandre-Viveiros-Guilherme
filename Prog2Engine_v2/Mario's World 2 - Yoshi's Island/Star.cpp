#include "pch.h"
#include "Star.h"

Star::Star(Point2f position):Entity("GeneralSprites.png",17,19,position)
{
}

void Star::Draw() const
{
	Entity::Draw();
}

void Star::Animate(float elapsedSec)
{
	m_FrameTime += elapsedSec;

	m_YTxtPos = 74;

	if (m_XTxtPos < 121)
	{
		m_XTxtPos = 121;
	}

	if (m_XTxtPos > 162)
	{
		m_XTxtPos = 121;
	}

	if (m_FrameTime > 0.5)
	{
		m_XTxtPos += m_TxtWidth + 5;

		m_FrameTime = 0;
	}
}

void Star::Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	utils::HitInfo hit_info;

	if (m_TerminalVelocityTimer > 1)
	{
		m_TerminalVelocityTimer = 1;
	}
	else
	{
		m_TerminalVelocityTimer += elapsedSec;
	}


	if (m_TerminalVelocityTimer > 1)
	{
		m_TerminalVelocityTimer = 1;
	}
	else
	{
		m_TerminalVelocityTimer += elapsedSec;
	}

	//Floor Collisions
	for (int idx{ 0 }; idx < platforms.size(); idx++)
	{


		//checks collision from the middle bottom of the star
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight },
			Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom - 1 }, hit_info))
		{
			if (m_VelocityX < 0)
			{
				m_VelocityX = -hit_info.lambda * 200;
			}
			else
			{
				m_VelocityX = hit_info.lambda * 200;
			}
			m_VelocityY = hit_info.lambda * 200;
			m_IsGrounded = true;
			m_TerminalVelocityTimer = 0;
			break;
		}

		//checks collision from the middle top of the star
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight },
			Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight * 2 }, hit_info))
		{
			if (m_VelocityX < 0)
			{
				m_VelocityX = -hit_info.lambda * 200;
			}
			else
			{
				m_VelocityX = hit_info.lambda * 200;
			}
			m_VelocityY = -hit_info.lambda * 200;

			m_IsGrounded = true;
			m_TerminalVelocityTimer = 0;
			break;
		}

		//Gravity
		if (idx == 0) //to prevent gravity from getting looped 12 times
		{
			m_IsGrounded = false;

			if (m_VelocityY > -480.f)
			{
				m_VelocityY -= 48.f * m_TerminalVelocityTimer;
			}

			if (m_VelocityY < -480.f)
			{
				m_VelocityY += 48.f;
			}

		}


	}

	//Wall Collision
	for (int idx{ 0 }; idx < platforms.size(); idx++)
	{
		//Wall Collision

	//left side collision
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight },
			Point2f{ m_Hitbox.left - 2,m_Hitbox.bottom + m_TxtHeight }, hit_info))
		{
			m_VelocityX = hit_info.lambda * 200;
			m_VelocityY = hit_info.lambda * 200;
		}

		//right side collision
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight },
			Point2f{ m_Hitbox.left + m_TxtWidth * 2 + 2,m_Hitbox.bottom + m_TxtHeight }, hit_info))
		{
			m_VelocityX = -hit_info.lambda * 200;
			m_VelocityY = hit_info.lambda * 200;
		}

	}

	//checks if entity is facing right or left
	if (m_VelocityX < 0)
	{
		m_IsFacingRight = false;
	}

	else if (m_VelocityX > 0)
	{
		m_IsFacingRight = true;
	}

	//collision and gravity
	m_Position.y += m_VelocityY * elapsedSec;
	//Adds Entity's horizontal speed to his position
	m_Position.x += m_VelocityX * elapsedSec;

}	
