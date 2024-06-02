#include "pch.h"
#include "Mario.h"

#include "Texture.h"
#include "Yoshi.h"

Mario::Mario(Yoshi* &plyrYoshi) :Entity("Mario_SpriteSheet.png", 14, 16, plyrYoshi->GetPosition()), m_Yoshi(plyrYoshi),
m_XTxtPos2(m_XTxtPos), m_YTxtPos2(m_YTxtPos2), m_TxtWidth2(m_TxtWidth), m_TxtHeight2(m_TxtHeight)
{
}

Mario::~Mario()
{
}

void Mario::Draw() const
{
	glPushMatrix();
	{

		glTranslatef(m_Position.x + m_TxtWidth, m_Position.y, 0);
		glRotatef(m_AngleDeg, m_AngX, m_AngY, m_AngZ);
		if (m_IsFacingRight == false) {
			glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);
		}

		else if (m_IsFacingRight == true) {
			glScalef(-m_ScaleX, m_ScaleY, m_ScaleZ);
		}

		// Draw the Entity player
		m_EntityTxt->Draw(Rectf(-m_TxtWidth, 0, float(m_TxtWidth * 2), float(m_TxtHeight * 2)),
			Rectf(m_XTxtPos2, m_YTxtPos2, m_TxtWidth2, m_TxtHeight2));
		m_EntityTxt->Draw(Rectf(-m_TxtWidth + 4, 0 + m_TxtWidth2 + 3 , float(m_TxtWidth * 2), float(m_TxtHeight * 2)),
			Rectf(m_XTxtPos, m_YTxtPos, m_TxtWidth, m_TxtHeight));
	}
	glPopMatrix();
}

void Mario::Update(const std::vector< std::vector<Point2f>>& platforms, const float elapsedSec)
{
	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));

	if (m_Yoshi->GetIsMarioOn() == true)
	{
		m_IsFacingRight = m_Yoshi->GetIsFacingRight();
		m_Position = m_Yoshi->GetPosition();

		if (m_IsFacingRight == true)
		{
			m_Position.x -= 10;
		}

		else
		{
			m_Position.x += 30;
		}

		m_Position.y += 15;
	}

	else
	{
		m_Time += elapsedSec;

		if (m_Time < 0.7)
		{
			if (m_Yoshi->GetIsFacingRight() == true)
			{
				m_VelocityX = -1.5f;
			}
			else
			{
				m_VelocityX = 1.5f;
			}
			m_VelocityY += 1.5f;
		}
		else
		{
			float distanceX{ m_Yoshi->GetPosition().x - m_Position.x };
			float distanceY{ m_Yoshi->GetPosition().y - m_Position.y };

			if (distanceX < 2 && distanceX > -2)
			{
				distanceX = 0;
			}
			if (distanceY < 2 && distanceY > -2)
			{
				distanceY = 0;
			}

			if (m_Position.x < m_Yoshi->GetPosition().x)
			{
				m_VelocityX = 0.1f * distanceX;
			}

			else
			{
				m_VelocityX = 0.1f * distanceX;
			}

			if (m_Position.y < m_Yoshi->GetPosition().y)
			{
				m_VelocityY = 0.1f * distanceY;
			}

			else
			{
				m_VelocityY = 0.1f * distanceY;
			}
		}
	}


	//collision and gravity
	m_Position.y += m_VelocityY * elapsedSec;
	//Adds Entity's horizontal speed to his position
	m_Position.x += m_VelocityX * elapsedSec;

	Animate(elapsedSec);
}

void Mario::Animate(float elapsedSec)
{
	m_YTxtPos = 203;
	m_XTxtPos = 0;
	m_YTxtPos2 = 152;
	m_XTxtPos2 = 16;
	m_TxtWidth2 = 14;
	m_TxtHeight2 = 9;



}


