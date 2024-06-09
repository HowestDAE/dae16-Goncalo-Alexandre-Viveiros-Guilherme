#include "pch.h"
#include "Entity.h"
#include "Texture.h"

Entity::Entity(const std::string& texturePath, const float txtHeight, const float txtWidth, const Point2f position) :
	m_EntityTxt{ new Texture {texturePath} },
	m_Position{ position },
	m_TxtHeight{ txtHeight },
	m_TxtWidth{ txtWidth },
	m_ResetPosition(position)
{

}

Entity::~Entity()
{
	delete m_EntityTxt;
	m_EntityTxt = nullptr;
}

void Entity::Draw() const
{
	if (m_IsActive == true)
	{
		glPushMatrix();
		{
			// Translate to the origin of the entity
			glTranslatef(m_Position.x + m_TxtWidth, m_Position.y + m_TxtHeight, 0);

			// Apply rotation around the middle of the entity
			glRotatef(m_AngleDeg, m_AngX, m_AngY, m_AngZ);

			// Apply scaling based on the facing direction
			if (m_IsFacingRight == false) {
				glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);
			}
			else {
				glScalef(-m_ScaleX, m_ScaleY, m_ScaleZ);
			}

			// Translate back to the original position
			glTranslatef(-m_TxtWidth + m_TxtWidth, -m_TxtHeight, 0);


			// Draw Entity
			m_EntityTxt->Draw(Rectf(-m_TxtWidth, 0, float(m_TxtWidth * 2), float(m_TxtHeight * 2)),
				Rectf(m_XTxtPos, m_YTxtPos, m_TxtWidth, m_TxtHeight));


		}
		glPopMatrix();
	}


	
	//debugs floor collision
	//utils::SetColor(Color4f{ 1,0,0,1 });
	////left side
	//utils::DrawLine(Point2f{ m_Hitbox.left,m_Hitbox.bottom + m_TxtHeight },
	//	Point2f{ m_Hitbox.left,m_Hitbox.bottom - 1 });
	//utils::DrawLine(Point2f{ m_Hitbox.left + m_TxtWidth * 2,m_Hitbox.bottom + m_TxtHeight },
	//	Point2f{ m_Hitbox.left + m_TxtWidth * 2,m_Hitbox.bottom - 1 });
}

void Entity::Update(const std::vector< std::vector<Point2f>>& platforms, const float elapsedSec)
{
	if (m_IsActive == true)
	{
		//Update Hitbox
		m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));

		Collision(platforms, elapsedSec);

		//Adds Gravity to position
		m_Position.y += m_VelocityY * elapsedSec;
		//Adds Entity's horizontal speed to his position
		m_Position.x += m_VelocityX * elapsedSec;

		Animate(elapsedSec);
	}
	
}

void Entity::Collision(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
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


		//checks collision from the left side of Entity's feet
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left,m_Hitbox.bottom + m_TxtHeight * 2 },
			Point2f{ m_Hitbox.left,m_Hitbox.bottom - 2 }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsGrounded = true;
			m_TerminalVelocityTimer = 0;
			break;
		}

		//checks collision from the right side of Entity's feet
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth * 2,m_Hitbox.bottom + m_TxtHeight * 2 },
			Point2f{ m_Hitbox.left + m_TxtWidth * 2,m_Hitbox.bottom - 2 }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
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
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight*2 },
			Point2f{ m_Hitbox.left - 2,m_Hitbox.bottom + m_TxtHeight*2 }, hit_info))
		{
			m_Position.x = hit_info.intersectPoint.x + 1; //Teleports entity to the point of intersection with a small offset
		}

		//right side collision
		if (utils::Raycast(platforms[idx], Point2f{ m_Hitbox.left + m_TxtWidth,m_Hitbox.bottom + m_TxtHeight*2 },
			Point2f{ m_Hitbox.left + m_TxtWidth * 2 + 2,m_Hitbox.bottom + m_TxtHeight*2 }, hit_info))
		{
			m_Position.x = hit_info.intersectPoint.x - m_TxtWidth * 2 + 2;
		}

	}

#pragma region Friction and orientation

	//simulates ground friction 
	if (m_IsGrounded == true)
	{
		m_VelocityX -= (m_VelocityX * 5) * elapsedSec;
	}

	//simulates air friction
	else
	{
		m_VelocityX -= (m_VelocityX / 8) * elapsedSec;
	}

	//Stops movement once it falls below a certain range
	if (m_VelocityX < 10 && m_VelocityX > 0 || m_VelocityX > -10 && m_VelocityX < 0)
	{
		m_VelocityX = 0;
	}

	if (m_VelocityX < 0)
	{
		m_IsFacingRight = false;
	}

	else if (m_VelocityX > 0)
	{
		m_IsFacingRight = true;
	}


#pragma endregion

}

void Entity::Animate(float elapsedSec)
{
}

void Entity::FlipIsActive()
{
	m_IsActive = !m_IsActive;
}

void Entity::SetPosition(Point2f newPosition)
{
	m_Position = newPosition;
}

void Entity::AddVelocity(float velocityX, float velocityY)
{
	m_VelocityX += velocityX;
	m_VelocityY += velocityY;
}

Rectf Entity::GetHitBox() const
{
	return m_Hitbox;
}

Point2f Entity::GetPosition() const
{
	return m_Position;
}


bool Entity::GetIsFacingRight() const
{
	return m_IsFacingRight;
}



bool Entity::GetIsGrounded() const
{
	return m_IsGrounded;
}

bool Entity::GetIsActive() const
{
	return m_IsActive;
}

Point2f Entity::GetVelocity() const
{
	return Point2f(m_VelocityX, m_VelocityY);
}

void Entity::Reset()
{
	m_Position = m_ResetPosition;

	m_VelocityY              = 0 ;
	m_VelocityX              = 0 ;
	m_XTxtPos                = 0 ;
	m_YTxtPos                = 0 ;
	m_IsGrounded             = false;
	m_IsFacingRight          = true ;
	m_IsActive               = true ;
	m_FrameTime              = 0 ;
	m_TerminalVelocityTimer  = 0 ;
	m_Hitbox                 = Rectf (0, 0, 0, 0) ;
						   
	m_AngleDeg               = 0 ;
	m_AngX                   = 0 ;
	m_AngY                   = 0 ;
	m_AngZ                   = 0 ;
	m_ScaleX                 = 1 ;
	m_ScaleY                 = 1 ;
	m_ScaleZ                 = 1 ;
}
