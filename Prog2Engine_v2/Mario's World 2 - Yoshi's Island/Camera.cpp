#include "pch.h"
#include "Camera.h"

#include <iostream>

#include "Texture.h"


Camera::Camera(const Point2f camPos, Point2f yoshiStartPos):
	m_CamPosition(camPos)
{

}

Camera::~Camera()
{
	
}

void Camera::Pan(const Point2f yoshiPos, const bool isGrounded, const bool isFacingRight)
{

	if (m_CamPosition.x <= 0 || m_CamPosition.x <= -7000)
	{
		if (isFacingRight == true)
		{
			if (m_CamPosition.x >= -yoshiPos.x + 200)
			{
				m_CamPosition.x -= 5;
			}
		}

		else
		{
			if (m_CamPosition.x <= -yoshiPos.x + 500)
			{
				m_CamPosition.x += 5;
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
	if (isGrounded == true)   
	{
		//lastYoshiYPos = YoshiPos.y;
		if (m_CamPosition.y > -yoshiPos.y + 150)
		{
			m_CamPosition.y -= 5;
		}

	}
	//If yoshi is falling pans camera towards him
	else
	{
		//lastYoshiYPos = YoshiPos.y;
		if (m_CamPosition.y < -yoshiPos.y + 150)
		{
			m_CamPosition.y += 5;
		}
	}

}

Point2f Camera::GetCamPos() const
{
	return m_CamPosition;
}


