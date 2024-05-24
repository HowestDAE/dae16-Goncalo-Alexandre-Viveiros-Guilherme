#include "pch.h"
#include "PogoShyGuy.h"

#include "Texture.h"

PogoShyGuy::PogoShyGuy(Point2f position):Enemy(true,true,"EnemiesVaried2.png", 19, 21,position)
{
}

void PogoShyGuy::Draw() const 
{
	glPushMatrix();
	{

		glTranslatef(m_Position.x + m_TxtWidth , m_Position.y, 0);
		glRotatef(m_AngleDeg, m_AngX, m_AngY, m_AngZ); 
		if (m_IsFacingRight == false) {
			glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);
		}

		else if (m_IsFacingRight == true) 
		{
			glScalef(-m_ScaleX, m_ScaleY, m_ScaleZ);
		}

		// Draw Entity
		m_EntityTxt->Draw(Rectf(-m_TxtWidth, 0, float(m_TxtWidth*1.8), float(m_TxtHeight*1.8)),
			Rectf(m_XTxtPos, m_YTxtPos, m_TxtWidth, m_TxtHeight));
	}
	glPopMatrix();
}

void PogoShyGuy::Update(const std::vector<std::vector<Point2f>>& platforms, float elapsedSec)
{
	Enemy::Update(platforms, elapsedSec);

	m_Timer += elapsedSec;

	if (m_Timer > 2)
	{
		if (m_IsGrounded == true)
		{
			m_VelocityX = -200;
			m_VelocityY = 400;
			m_Position.y += 2;
		}
		
		m_Timer = 0;
	}

	if (m_Timer > 0.5 && m_Timer < 1.5)
	{
		m_VelocityX = 0;
		m_VelocityY = 0;
	}


	m_XTxtPos = 61;
	m_YTxtPos = 29;



}
