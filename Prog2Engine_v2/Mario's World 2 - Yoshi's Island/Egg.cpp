#include "pch.h"
#include "Egg.h"
#include "Texture.h"

Egg::Egg(const Point2f position):Entity("Eggs.png",16,14,position)
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

	if (m_IsBeingHeld == true && m_IsThrown == false)
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

			m_Timer = 0.26f;
		}
		if (yoshiDirection == true)
		{
			m_Position.x = (m_LastYoshiPosX - m_TxtWidth * 2.f) - (m_TxtWidth * 2.5f) * currentEgg;
			m_Position.y = m_LastYoshiPosY;
		}
		else
		{
			m_Position.x = (m_LastYoshiPosX + m_TxtWidth * 5) + (m_TxtWidth * 2.5f) * currentEgg;
			m_Position.y = m_LastYoshiPosY;
		}
	}

	if (m_IsThrown == true)
	{
		Entity::Update(platforms, elapsedSec);
	}


}

void Egg::Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	if (m_IsFallen == false)
	{
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


			//checks collision from the middle bottom of the egg
			if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight },
				Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom - 1 }, hit_info))
			{
				if (m_VelocityX < 0)
				{
					m_VelocityX = -hit_info.lambda * 2000;
				}
				else
				{
					m_VelocityX = hit_info.lambda * 2000;
				}
				m_VelocityY = hit_info.lambda * 2000;
				m_IsGrounded = true;
				m_TerminalVlcityTimer = 0;
				break;
			}

			//checks collision from the middle top of the egg
			if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight },
				Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight * 2 }, hit_info))
			{
				if (m_VelocityX < 0)
				{
					m_VelocityX = -hit_info.lambda * 2000;
				}
				else
				{
					m_VelocityX = hit_info.lambda * 2000;
				}
				m_VelocityY = -hit_info.lambda * 2000;

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
				m_VelocityX = hit_info.lambda * 2000;
				m_VelocityY = hit_info.lambda * 2000;
			}

			//right side collision
			if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight },
				Point2f{ m_Hitbox.left + m_TxtWidth * 2 + 2,m_Hitbox.bottom + m_TxtHeight }, hit_info))
			{
				m_VelocityX = -hit_info.lambda * 2000;
				m_VelocityY = hit_info.lambda * 2000;
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

	else
	{
		Entity::Collision(platforms, elapsedSec);
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

void Egg::PickUpEgg()
{
	m_IsFallen = false;
}

void Egg::DropEgg()
{
	m_IsFallen = true;
}

bool Egg::HoldEgg(const Rectf yoshiHitBox, const bool isYoshiFacingRight, bool isCalculatingAngle, float elapsedSec)
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
	

	

	if (isYoshiFacingRight == true)
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

Rectf Egg::GetHitbox()
{
	return m_Hitbox;
}

bool Egg::GetIsFallen()
{
	return m_IsFallen;
}
