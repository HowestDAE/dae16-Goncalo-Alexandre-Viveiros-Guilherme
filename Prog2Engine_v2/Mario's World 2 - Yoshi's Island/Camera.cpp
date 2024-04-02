#include "pch.h"
#include "Camera.h"
#include "Texture.h"


Camera::Camera(Point2f CamPos, Point2f YoshiStartPos):
	m_YoshiPosition(YoshiStartPos),m_CamPosition(CamPos), lastYoshiXPos{m_YoshiPosition.x}, lastYoshiYPos{m_YoshiPosition.y}
{

}

Camera::~Camera()
{
	
}

Point2f Camera::Pan(Point2f YoshiPos)
{

	if (YoshiPos.x > lastYoshiXPos + 4)
	{
		m_CamPosition.x -= 5;
		lastYoshiXPos = YoshiPos.x;
	}

	if (YoshiPos.x < lastYoshiXPos - 4)
	{
		m_CamPosition.x += 5;
		lastYoshiXPos = YoshiPos.x;
	}

	return m_CamPosition;
}


