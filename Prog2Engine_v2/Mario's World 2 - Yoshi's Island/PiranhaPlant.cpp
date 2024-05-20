#include "pch.h"
#include "PiranhaPlant.h"

#include "Texture.h"

PiranhaPlant::PiranhaPlant(Point2f position):Enemy(false,false,"EnemiesVaried.png",43,32,position)
{
}

PiranhaPlant::~PiranhaPlant()
{
}

void PiranhaPlant::Draw() const
{
	Entity::Draw();

	
	glPushMatrix();
	{
		glTranslatef(m_Position.x + m_TxtWidth, m_Position.y, 0);
		if (m_IsFacingRight == false) {
			glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);
		}

		else if (m_IsFacingRight == true) {
			glScalef(-m_ScaleX, m_ScaleY, m_ScaleZ);
		}

		// Draw Entity
		m_EntityTxt->Draw(Rectf(-m_TxtWidth2 - 4, 0 - m_TxtHeight2 * 2, float(m_TxtWidth2 * 2), float(m_TxtHeight2 * 2)),
			Rectf(m_XTxtPos2, m_YTxtPos2, m_TxtWidth2, m_TxtHeight2));
	}
	glPopMatrix();
}

void PiranhaPlant::Update(Point2f yoshiPos)
{
	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));

}

void PiranhaPlant::Animate(float elapsedSec)
{
	m_FrameTime += elapsedSec;
	m_YTxtPos = 127;
	m_YTxtPos2 = 141;
	m_XTxtPos2 = 19;

	if (m_XTxtPos < 20 || m_XTxtPos > 91)
	{
		m_XTxtPos = 20;
	}

	if (m_FrameTime > 0.3)
	{
		m_XTxtPos += m_TxtWidth + 8;

		m_FrameTime = 0;
	}
}
