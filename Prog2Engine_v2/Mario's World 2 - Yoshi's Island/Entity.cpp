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
	if (m_IsFacingRight == false)
	{
		m_EntityTxt->Draw(Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2)),
			Rectf(xTxtPos, yTxtPos, m_TxtWidth, m_TxtHeight));
	}

	if (m_IsFacingRight == true)
	{
		glPushMatrix();
		{
			glScalef(-1, 1, 1);
			glTranslatef(-m_TxtWidth * 3 + 9, 0, 0);
			m_EntityTxt->Draw(Rectf(-m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2)),
				Rectf(xTxtPos, yTxtPos, m_TxtWidth, m_TxtHeight));
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

void Entity::Update(const std::vector< std::vector<Point2f>>& platforms,float elapsedSec)
{
	//collision and gravity
	m_Position.y += m_VelocityY * elapsedSec;

	utils::HitInfo hit_info;

	//Collisions
	for (int idx{ 0 }; idx < platforms.size(); idx++)
	{
		//floor collision

		//checks collision from the left side of yoshis feet
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_TxtWidth - 3,m_Position.y + m_TxtHeight * 2 },
			Point2f{ m_Position.x + m_TxtWidth - 3, m_Position.y - 3 }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsGrounded = true;
		}

		//checks collision from the right side of yoshis feet
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_TxtWidth * 2 - 3,m_Position.y + m_TxtHeight * 2 },
			Point2f{ m_Position.x + m_TxtWidth * 2 - 3, m_Position.y - 3 }, hit_info))
		{
			m_VelocityY = 0;
			m_Position.y = hit_info.intersectPoint.y;
			m_IsGrounded = true;
		}
		else
		{

			m_VelocityY = -380;


		}

		//Wall Collision

		//left side collision
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_TxtWidth + 20,m_Position.y + m_TxtHeight },
			Point2f{ m_Position.x + m_TxtWidth - 5, m_Position.y + m_TxtHeight }, hit_info))
		{
			m_VelocityX = -0.3;
			m_Position.x = hit_info.intersectPoint.x - m_TxtWidth + 7; //Teleports yoshi to the point of intersection with a small offset
		}

		//right side collision
		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + m_TxtWidth + 10,m_Position.y + m_TxtHeight },
			Point2f{ m_Position.x + m_TxtWidth + 30,m_Position.y + m_TxtHeight }, hit_info))
		{
			m_VelocityX = 0.3;
			m_Position.x = hit_info.intersectPoint.x - m_TxtWidth * 2 - 3;
		}

	}

	//Adds Yoshi's horizontal speed to his position
	m_Position.x += m_VelocityX * elapsedSec;



	//simulates friction whilst yoshi is grounded
	if (m_IsGrounded == true)
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
