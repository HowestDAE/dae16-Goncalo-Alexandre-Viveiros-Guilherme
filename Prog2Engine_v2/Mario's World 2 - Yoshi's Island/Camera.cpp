#include "pch.h"
#include "Camera.h"

#include <iostream>

#include "Texture.h"
#include "Yoshi.h"


Camera::Camera(const Point2f camPos, Point2f yoshiStartPos):
	m_CamPosition(camPos)
{

}

void Camera::Pan(Yoshi*& yoshiPlyr,float levelStart,float levelEnd)
{

	if (m_CamPosition.x <= levelStart || m_CamPosition.x <= -levelEnd)
	{
		if (yoshiPlyr->GetIsFacingRight() == true)
		{
			if (m_CamPosition.x >= -yoshiPlyr->GetPosition().x + 180)
			{
				m_CamPosition.x -= 0.05f * yoshiPlyr->GetVelocity().x / 5;
				if (yoshiPlyr->GetVelocity().x ==  0)
				{
					m_CamPosition.x -= 0.5f;
				}
			}
		}

		else
		{
			if (m_CamPosition.x <= -yoshiPlyr->GetPosition().x + 450)
			{
				m_CamPosition.x -= 0.05f * yoshiPlyr->GetVelocity().x / 5;
				if (yoshiPlyr->GetVelocity().x == 0)
				{
					m_CamPosition.x += 0.5f;
				}
			}

		}

		if (m_CamPosition.x > 0)
		{
			m_CamPosition.x = 0;
		}

		if (m_CamPosition.x < -7000)
		{
			m_CamPosition.x = -7000;
		}
	}


	
	//If yoshi is standing on a platform moves camera upwards
	if (yoshiPlyr->GetIsGrounded() == true)   
	{
		
		if (m_CamPosition.y > -yoshiPlyr->GetPosition().y + 150)
		{
			m_CamPosition.y -= 1.7f;
		}
		if (m_CamPosition.y < -yoshiPlyr->GetPosition().y + 150)
		{
			m_CamPosition.y += 1.7f;
		}
	}
	//If yoshi is falling pans camera towards him
	else
	{
	
		if (m_CamPosition.y < -yoshiPlyr->GetPosition().y + 150)
		{
			m_CamPosition.y += 1.7f;
		}
	}

}

void Camera::CenterCamera(Point2f yoshiPos)
{
	m_CamPosition = Point2f(-yoshiPos.x,-yoshiPos.y);
}

Point2f Camera::GetCamPos() const
{
	return m_CamPosition;
}


