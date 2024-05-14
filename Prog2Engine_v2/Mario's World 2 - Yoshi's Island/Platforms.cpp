#include "pch.h"
#include "Platforms.h"
#include "Texture.h"

Platforms::Platforms(Point2f position, float txtWidth, float txtHeight, float platformWidth, float platformHeight, const std::string& texturePath):
	m_PlatformTxt{ new Texture{ texturePath } },
	m_TxtHeight{ txtHeight },
	m_TxtWidth{ txtWidth },
	m_Position{ position },
	m_PlatformWidth(platformWidth),
	m_PlatformHeight(platformHeight)
{
	m_PlatformPos1.y = m_Position.y + m_Radius;
	m_PlatformPos1.x = m_Position.x;

	m_PlatformPos2.y = m_Position.y;
	m_PlatformPos2.x = m_Position.x + m_Radius;

	m_PlatformPos3.y = m_Position.y - m_Radius;
	m_PlatformPos3.x = m_Position.x;

	m_PlatformPos4.y = m_Position.y;
	m_PlatformPos4.x = m_Position.x - m_Radius;
}

Platforms::~Platforms()
{

}

void Platforms::Draw() const
{
	glPushMatrix();
	{

		glTranslatef(m_Position.x + m_TxtWidth, m_Position.y, 0);
		glRotatef(m_Angle, 0, 1, 0);
		// Draw Entity
		m_PlatformTxt->Draw(Rectf(0, 0, m_PlatformWidth, m_PlatformHeight),
			Rectf(0, 0, m_TxtWidth, m_TxtHeight));
	}
	glPopMatrix();
	
}

void Platforms::Update()
{
}
