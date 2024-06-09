#include "pch.h"
#include "UI.h"
#include "Texture.h"
#include "Yoshi.h"

UI::UI(const std::string& texturePath, float txtHeight, float txtWidth):
	m_UITexture(new Texture(texturePath))
{
	m_TxtWidth.push_back(txtWidth);
	m_TxtHeight.push_back(txtHeight);

	m_XTxtPos.push_back(0);
	m_XTxtPos.push_back(0);
	m_XTxtPos.push_back(0);

	m_YTxtPos.push_back(32);
	m_YTxtPos.push_back(0);
	m_YTxtPos.push_back(0);

	m_TxtWidth.push_back(15);
	m_TxtWidth.push_back(15);

	m_TxtHeight.push_back(15);
	m_TxtHeight.push_back(15);
}

UI::~UI()
{
	delete m_UITexture;
}

void UI::Draw(Point2f camPos) const
{
	glPushMatrix();
	{
		glTranslatef(-camPos.x + 550, -camPos.y + 420, 0);

		//Draws the Circle
		m_UITexture->Draw(Rectf(-m_TxtWidth[0], 0, float(m_TxtWidth[0] * 2), float(m_TxtHeight[0] * 2)), Rectf(m_XTxtPos[0], m_YTxtPos[0], m_TxtWidth[0], m_TxtHeight[0]));

		if (m_Number < 10)
		{
			m_UITexture->Draw(Rectf(-m_TxtWidth[1], m_TxtHeight[0] / 2, float(m_TxtWidth[1] * 2), float(m_TxtHeight[1] * 2)), Rectf(m_XTxtPos[1], m_YTxtPos[1], m_TxtWidth[1], m_TxtHeight[1]));
		}
		else
		{
			m_UITexture->Draw(Rectf(-m_TxtWidth[1] * 2 + 5, m_TxtHeight[0]/2, float(m_TxtWidth[1] * 2), float(m_TxtHeight[1] * 2)), Rectf(m_XTxtPos[1], m_YTxtPos[1], m_TxtWidth[1], m_TxtHeight[1]));
			m_UITexture->Draw(Rectf(0, m_TxtHeight[0]/2, float(m_TxtWidth[2] * 2), float(m_TxtHeight[2] * 2)), Rectf(m_XTxtPos[2], m_YTxtPos[2], m_TxtWidth[2], m_TxtHeight[2]));
		}

	}
	glPopMatrix();
}

void UI::Update(bool isMarioOn,int marioTimer)
{
	m_Number = marioTimer;

	if (m_Number < 10)
	{
		m_XTxtPos[1] = 15 * m_Number;
	}
	else
	{
		m_FirstDigit = m_Number / 10;
		m_SecondDigit = m_Number % 10;

		m_XTxtPos[1] = 15 * m_FirstDigit;
		m_XTxtPos[2] = 15 * m_SecondDigit;

	}


	if (isMarioOn == false) 
	{
		m_YTxtPos[1] = 50;
		m_YTxtPos[2] = 50;
	}	  
	else  
	{	  
		m_YTxtPos[1] = 68;
		m_YTxtPos[2] = 68;
	}
}

void UI::Reset()
{
	m_Number      = 10;
	m_FirstDigit  = 1 ;
	m_SecondDigit = 0 ;
}
