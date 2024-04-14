#include "pch.h"
#include "Entity.h"
#include "Texture.h"
#include "utils.h"

Entity::Entity(const std::string& TexturePath,float txtHeight, float txtWidth,Point2f position):
 m_EntityTxt{ new Texture {TexturePath} },
 m_TxtHeight{txtHeight},
 m_TxtWidth{txtWidth},
 m_Position {position}
{

}

Entity::~Entity()
{
}

void Entity::Draw() const
{

	glPushMatrix();
	{

		glTranslatef(m_Position.x + m_TxtWidth , m_Position.y, 0);
		glRotatef(m_AngleDeg, m_AngX, m_AngY, m_AngZ); 
		if (m_IsFacingRight == false) {
			glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);
		}

		else if (m_IsFacingRight == true) {
			glScalef(-m_ScaleX, m_ScaleY, m_ScaleZ);
		}

		// Draw the Entity player
		m_EntityTxt->Draw(Rectf(-m_TxtWidth, 0, float(m_TxtWidth * 2), float(m_TxtHeight * 2)),
			Rectf(m_XTxtPos, m_YTxtPos, m_TxtWidth, m_TxtHeight));
	}
	glPopMatrix();

	/*
	//debugs floor collision
	utils::SetColor(Color4f{ 1,0,0,1 });
	utils::DrawLine(Point2f{ m_Position.x + m_TxtWidth - 3,m_Position.y + m_TxtHeight * 2 },
		Point2f{ m_Position.x + m_TxtWidth - 3, m_Position.y });

	utils::DrawLine(Point2f{ m_Position.x + m_TxtWidth * 2 - 3,m_Position.y + m_TxtHeight * 2 },
		Point2f{ m_Position.x + m_TxtWidth * 2 - 3, m_Position.y });

	//debugs wall code
	utils::SetColor(Color4f{ 0,1,0,1 });

	utils::DrawLine(Point2f{ m_Position.x + m_TxtWidth + 20,m_Position.y + m_TxtHeight },
		Point2f{m_Position.x + m_TxtWidth / 1.5f, m_Position.y + m_TxtHeight});

	utils::DrawLine(Point2f{ m_Position.x + m_TxtWidth + 10,m_Position.y + m_TxtHeight },
		Point2f{ m_Position.x + m_TxtWidth * 2,m_Position.y + m_TxtHeight });
		*/

}

void Entity::Update(const std::vector< std::vector<Point2f>>& platforms,float elapsedSec)
{
	//collision and gravity
	m_Position.y += m_VelocityY * elapsedSec;

	utils::HitInfo hit_info;

	//Collisions
	for (int idx{ 0 }; idx < platforms.size(); idx++)
	{
		//floor collision

		//checks collision from the left side of Entitys feet
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_TxtWidth - 3,m_Position.y + m_TxtHeight * 2 },
			Point2f{ m_Position.x + m_TxtWidth - 3, m_Position.y - 5}, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsGrounded = true;
		}

		//checks collision from the right side of Entitys feet
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_TxtWidth * 2 - 3,m_Position.y + m_TxtHeight * 2 },
			Point2f{ m_Position.x + m_TxtWidth * 2 - 3, m_Position.y -5}, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsGrounded = true;
		}

		//Gravity
		else
		{
			m_IsGrounded = false;

			if (m_VelocityY != -380)
			{
				m_VelocityY -= 38;

				if (m_VelocityY < -380)
				{
					m_VelocityY = -342;
				}
			}
			


		}

		//Wall Collision

		//left side collision
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_TxtWidth + 20,m_Position.y + m_TxtHeight },
			Point2f{ m_Position.x + m_TxtWidth / 1.5f, m_Position.y + m_TxtHeight }, hit_info))
		{
			m_VelocityX = -0.3;
			m_Position.x = hit_info.intersectPoint.x - m_TxtWidth + (m_TxtWidth/2.1); //Teleports entity to the point of intersection with a small offset
		}

		//right side collision
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_TxtWidth + 10,m_Position.y + m_TxtHeight },
			Point2f{ m_Position.x + m_TxtWidth * 2,m_Position.y + m_TxtHeight }, hit_info))
		{
			m_VelocityX = 0.3;
			m_Position.x = hit_info.intersectPoint.x - m_TxtWidth * 2 - (m_TxtWidth / 9);
		}

	}

	//Adds Entity's horizontal speed to his position
	m_Position.x += m_VelocityX * elapsedSec;



	//simulates ground friction 
	if (m_IsGrounded == true)
	{
		m_VelocityX -= (m_VelocityX * 3.3) * elapsedSec;
	}

	//simulates air friction
	else
	{
		m_VelocityX -= (m_VelocityX) * elapsedSec;
	}

	//Stops movement once it falls below a certain range
	if (m_VelocityX < 20 && m_VelocityX > 0 || m_VelocityX > -20 && m_VelocityX < 0)
	{
		m_VelocityX = 0;
	}


	//Check if Entity is facing right
	if (m_VelocityX < 0)
	{
		m_IsFacingRight = false;
	}

	else if (m_VelocityX > 0)
	{
		m_IsFacingRight = true;
	}



	//Update Hitbox

	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));
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
