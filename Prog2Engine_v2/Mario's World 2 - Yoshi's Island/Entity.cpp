#include "pch.h"
#include "Entity.h"
#include "Texture.h"
#include "utils.h"

Entity::Entity(const std::string& texturePath, const float txtHeight, const float txtWidth, const Point2f position):
 m_EntityTxt{ new Texture {texturePath} },
 m_TxtHeight{txtHeight},
 m_TxtWidth{txtWidth},
 m_Position {position}
{

}

Entity::~Entity()
{
	delete m_EntityTxt;
	m_EntityTxt = nullptr;
}

void Entity::Draw() const
{

	glPushMatrix();
	{
		utils::SetColor(Color4f(0, 1, 0, 1));
		utils::DrawPoint(m_Position, 3);

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

void Entity::Animate(float elapsedSec)
{
}

void Entity::SetPosition(Point2f newPosition)
{
	m_Position = newPosition;
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

Point2f Entity::GetVelocity() const
{
	return Point2f(m_VelocityX, m_VelocityY);
}
