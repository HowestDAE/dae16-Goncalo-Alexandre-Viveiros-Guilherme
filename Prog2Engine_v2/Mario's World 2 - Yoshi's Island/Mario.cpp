#include "pch.h"
#include "Mario.h"

#include "Texture.h"
#include "Yoshi.h"

Mario::Mario(Yoshi* PlyrYoshi) :Entity("Mario_SpriteSheet.png", 14, 16, PlyrYoshi->GetPosition()), m_Yoshi(PlyrYoshi),
m_XTxtPos2(m_XTxtPos), m_YTxtPos2(m_YTxtPos2), m_TxtWidth2(m_TxtWidth), m_TxtHeight2(m_TxtHeight)
{
}

Mario::~Mario()
{
}

void Mario::Draw()
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

void Mario::Update(const std::vector< std::vector<Point2f>>& platforms, float elapsedSec)
{
	Entity::Update(platforms, elapsedSec);

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
		if (m_Yoshi->GetIsFacingRight() == true)
		{
			m_VelocityX = -300;
		}
		else
		{
			m_VelocityX = 300;
		}
		m_VelocityY = 500;
	}
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


