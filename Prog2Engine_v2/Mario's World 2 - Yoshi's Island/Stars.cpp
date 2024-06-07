#include "pch.h"
#include "Stars.h"

Stars::Stars(Point2f position):Entity("GeneralSprite.png",17,19,position)
{
}

void Stars::Draw() const
{
	Entity::Draw();
}

void Stars::Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	//Update Hitbox

	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));

	utils::HitInfo hit_info;

	if (m_TerminalVlcityTimer > 1)
	{
		m_TerminalVlcityTimer = 1;
	}
	else
	{
		m_TerminalVlcityTimer += elapsedSec;
	}


	if (m_TerminalVlcityTimer > 1)
	{
		m_TerminalVlcityTimer = 1;
	}
	else
	{
		m_TerminalVlcityTimer += elapsedSec;
	}

	//Floor Collisions
	for (int idx{ 0 }; idx < platforms.size(); idx++)
	{


		//checks collision from the left side of Entity's feet
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left,m_Hitbox.bottom + m_TxtHeight * 2 },
			Point2f{ m_Hitbox.left,m_Hitbox.bottom - 1 }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsGrounded = true;
			m_TerminalVlcityTimer = 0;
			break;
		}

		//checks collision from the right side of Entity's feet
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth * 2,m_Hitbox.bottom + m_TxtHeight * 2 },
			Point2f{ m_Hitbox.left + m_TxtWidth * 2,m_Hitbox.bottom - 1 }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsGrounded = true;
			m_TerminalVlcityTimer = 0;
			break;
		}

		//Gravity
		if (idx == 0) //to prevent gravity from getting looped 12 times
		{
			m_IsGrounded = false;

			if (m_VelocityY > -480.f)
			{
				m_VelocityY -= 48.f * m_TerminalVlcityTimer;
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
			m_Position.x = hit_info.intersectPoint.x + 1; //Teleports entity to the point of intersection with a small offset
		}

		//right side collision
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight },
			Point2f{ m_Hitbox.left + m_TxtWidth * 2 + 2,m_Hitbox.bottom + m_TxtHeight }, hit_info))
		{
			m_Position.x = hit_info.intersectPoint.x - m_TxtWidth * 2 + 2;
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

	//Update Hitbox

	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));
}

void Stars::Animate(float elapsedSec)
{
	Entity::Animate(elapsedSec);
}
